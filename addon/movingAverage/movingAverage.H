/*---------------------------------------------------------------------------*\
    888b     d888                                  d8888                   
    8888b   d8888                                 d88888                   
    88888b.d88888                                d88P888                   
    888Y88888P888  .d88b.  888  888  .d88b.     d88P 888 888  888  .d88b.  
    888 Y888P 888 d88""88b 888  888 d8P  Y8b   d88P  888 888  888 d8P  Y8b 
    888  Y8P  888 888  888 Y88  88P 88888888  d88P   888 Y88  88P 88888888 
    888   "   888 Y88..88P  Y8bd8P  Y8b.     d8888888888  Y8bd8P  Y8b.     
    888       888  "Y88P"    Y88P    "Y8888 d88P     888   Y88P    "Y8888  
-------------------------------------------------------------------------------                                                                                                                                                    
License
    This file is part of movingAverage.

    movingAverage is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    movingAverage is distributed in the hope that it will be useful, but 
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with  movingAverage.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::movingAverage

Description
    Average a field with a given averaging volume 
    see also: Foam::movingLESCellManager
    
Usage
    Constrtuct with a aveSpace
    movingAverage fa(mesh,aveSpace);
    
    // Average any field with:
    tmp<fieldType> averagedFieldTmp = fa.average(field);
    // The type of field, e.g volScalarField, volVectorField etc. is automatically
    // deducted from the input type
    
    
SourceFiles
    movingLESCellManager.C

Author
    Jan Wilhelm Gärtner <jan.gaertner@outlook.de> Copyright (C) 2021>

\*---------------------------------------------------------------------------*/

#ifndef movingAverage_H 
#define movingAverage_H

#include "movingLESCellManager/movingLESCellManager.H"
#include "aveSpace/aveSpace/aveSpace.H"
#include "regIOobject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                  Class movingAverage Declaration
\*---------------------------------------------------------------------------*/
class movingAverage
:
    public regIOobject
{

    private:
    //- Private Data

        movingLESCellManager manager_;
        
        const fvMesh& mesh_;

    //- Private member functions
        template<class Type>
        void collectData
        (
            const GeometricField<Type, fvPatchField, volMesh>& vf,
            List<List<Type>>& haloCells
        ) const;

    public:

    // Constructor
       
        movingAverage(const fvMesh& mesh, const aveSpace& box);

        //- Disallow default bitwise copy construct
        movingAverage(const movingLESCellManager&) = delete;

        //- Disallow default bitwise assignment
        movingAverage& operator=(const movingLESCellManager&) = delete;

  // Member Functions

    // Access

        //- Floating LES cell manager
        inline const movingLESCellManager& manager() const
        {
            return manager_;
        }

    // Calculations

        //- Average a field with the floating LES cell
        //  returns again a volField with the averaged values
        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh>> average
        (
            const GeometricField<Type, fvPatchField, volMesh>& vf
        ) const;
        
        //- reload average function with tmp type input
        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh>> average
        (
            const tmp<GeometricField<Type, fvPatchField, volMesh>>& vf
        ) const;
        
        //- reload average function with Internal field
        template<class Type>
        tmp<DimensionedField<Type, volMesh>> average
        (
            const DimensionedField<Type, volMesh>& f
        ) const;

    // Write Data
        
        //- Write data inherited from regIOobject
        bool writeData(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void Foam::movingAverage::collectData
(
    const GeometricField<Type, fvPatchField, volMesh>& vf,
    List<List<Type>>& haloCells
) const
{
 // Distribute data to neighbour processors

    haloCells.setSize(manager_.cellsToSendToProcessors().size());
    
    forAll(haloCells, procI)
    {
        haloCells[procI].setSize(manager_.cellsToSendToProcessors()[procI].size());
        
        forAll(haloCells[procI], haloCellID)
        {
            haloCells[procI][haloCellID] =
                vf.internalField()[manager_.cellsToSendToProcessors()[procI][haloCellID]];
        }
    }

    PstreamBuffers pBufs(Pstream::commsTypes::nonBlocking);

    // Distribute data
    forAll(manager_.sendProcList(), procI)
    {
        if (manager_.sendProcList()[procI] != -1)
        {
            UOPstream toBuffer(manager_.sendProcList()[procI], pBufs);
            toBuffer << haloCells[procI];
        }
    }

    pBufs.finishedSends();

    // Collect data

    forAll(manager_.receiveProcList(), procI)
    {
        haloCells[procI].clear();
        if (manager_.receiveProcList()[procI] != -1)
        {
            UIPstream fromBuffer(manager_.receiveProcList()[procI], pBufs);
            fromBuffer >> haloCells[procI];
        }
    }
}


template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::fvPatchField, Foam::volMesh>> 
Foam::movingAverage::average
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    using volFieldType = GeometricField<Type, fvPatchField, volMesh>;
    
    // Create temporary to store the averaged results in 
    tmp<volFieldType> averagedFieldTmp
    (
        new volFieldType 
        (
            IOobject
            (
                "averagedField",
                mesh_.time().timeName(),
                mesh_,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            vf
        )
    );

    // Create reference to field 
    auto& averagedField = averagedFieldTmp.ref();    
    
    List<List<Type>> haloCells;
    
    // First collect halo data
    collectData(vf,haloCells);
    
    // Use a std::unordered_map as data storage for temporary sum values
    // of oNodes to avoid unnecessary recalculation
    std::unordered_map<size_t,Type> dataBuffer;
    
    forAll(vf,cellID)
    {
        // Average over this cellID
        const compactCellList& localStencilID = manager_.stencilsID()[cellID];

        // Calculate the sum of field with the local cellIDs 
        Type sum = Foam::sum(vf,localStencilID,&dataBuffer);
        
        label nEntries = localStencilID.size();

        // check if the cell requires parallel handling:
        if (manager_.hasProcesorContribution(cellID))
        {
            // get processors to look up from
            const labelList procList = manager_.cellToProcMap()[cellID];
            for (auto procI : procList)
            {
                const List<Type>& haloCellsOfProcessorI = haloCells[procI];
                const labelList& haloCellIDList = manager_.haloCellIDLists()[cellID][procI];
                for (label haloCellID : haloCellIDList)
                {
                    sum += haloCellsOfProcessorI[haloCellID];
                }
                nEntries += haloCellIDList.size();
            }
        }
        averagedField[cellID] = sum/nEntries;
    }
    
    return averagedFieldTmp;
}


template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::fvPatchField, Foam::volMesh>> 
Foam::movingAverage::average
(
    const tmp<GeometricField<Type, fvPatchField, volMesh>>& vf
) const
{
    tmp<GeometricField<Type, fvPatchField, volMesh>> tvf(average(vf()));
    vf.clear();
    return tvf;
}


template<class Type>
Foam::tmp<Foam::DimensionedField<Type, volMesh>> 
Foam::movingAverage::average
(
    const DimensionedField<Type, volMesh>& f
) const
{
    
    using volFieldType = GeometricField<Type, fvPatchField, volMesh>;
    using Internal = DimensionedField<Type, volMesh>;
    
    tmp<Internal> tf
    (
        Internal::New
        (
            "averagedInternalField",
            mesh_,
            dimensioned<Type>(f.dimensions(), Zero)
        )
    );
    
    Internal& Intf = tf.ref();
    
    tmp<volFieldType> tvf
    (
        new volFieldType 
        (
            IOobject
            (
                "tvf",
                mesh_.time().timeName(),
                mesh_,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh_,
            dimensioned<Type>(f.dimensions(), Zero)
        )
    );
    
    Internal& Intvf = tvf.ref();
    
    Intvf = f;
    
    tmp<GeometricField<Type, fvPatchField, volMesh>> tvf2(average(tvf));
    
    Internal& Intvf2 = tvf2.ref();
    
    Intf = Intvf2;
    
    tvf2.clear();
    
    return tf;
}

    

#endif

// ************************************************************************* //
