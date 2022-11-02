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
    along with movingAverage.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::distributeSource

Description
    Average a field with a floating LES box
    see also: Foam::movingLESCellManager
    
Usage
    Constrtuct with a LESbox
    distributeSource distSource(mesh,LESbox);
    
    // Average any field with:
    tmp<fieldType> averagedFieldTmp = distSource.distribute(field);
    // The type of field, e.g volScalarField, volVectorField etc. is automatically
    // deducted from the input type
    
    
SourceFiles
    distributeSource.C

Author
    Jan Wilhelm Gärtner <jan.gaertner@outlook.de> Copyright (C) 2022

\*---------------------------------------------------------------------------*/

#ifndef distributeSource_H 
#define distributeSource_H

#include "movingLESCellManager/movingLESCellManager.H"
#include "regIOobject.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                  Class distributeSource Declaration
\*---------------------------------------------------------------------------*/
class distributeSource
:
    public regIOobject
{

    private:
    //- Private Data

        //- Reference to the manager
        movingLESCellManager manager_;
        
        //- Store the halo cell volumes
        List<List<scalar>> haloCellVolumes_;
        
        //- Store the total volume of all local and halo cells for each
        //  averaging space
        List<scalar> totalCellVolume_;
        
        const fvMesh& mesh_;

    //- Private member functions
        template<class Type>
        void collectData
        (
            const DimensionedField<Type, volMesh>& vf,
            List<List<Type>>& haloCells
        ) const;

    public:

    // Constructor
       
        distributeSource(const fvMesh& mesh, const aveSpace& box);

        //- Disallow default bitwise copy construct
        distributeSource(const movingLESCellManager&) = delete;

        //- Disallow default bitwise assignment
        distributeSource& operator=(const movingLESCellManager&) = delete;

  // Member Functions

    // Access

        //- Floating LES cell manager
        inline const movingLESCellManager& manager() const
        {
            return manager_;
        }

    // Calculations

        //- Distribute the cell values to the given cells in the defined 
        //- LES box returns again a volField with the distributed values
        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh>> distribute
        (
            const GeometricField<Type, fvPatchField, volMesh>& vf
        ) const;
        
        //- reload distribute function with tmp type input
        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh>> distribute
        (
            const tmp<GeometricField<Type, fvPatchField, volMesh>>& vf
        ) const;
        
        //- reload distribute function with Internal type
        template<class Type>
        tmp<DimensionedField<Type, volMesh>> distribute
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
void Foam::distributeSource::collectData
(
    const DimensionedField<Type, volMesh>& vf,
    List<List<Type>>& haloCells
) const
{
    // Distribute data to neighbour processors

    haloCells.setSize(manager_.cellsToSendToProcessors().size());

    PstreamBuffers pBufs(Pstream::commsTypes::nonBlocking);

    // Distribute data
    forAll(manager_.sendProcList(), procI)
    {
        if (manager_.sendProcList()[procI] != -1)
        {
            List<Type> tempList;
            tempList.setSize(manager_.cellsToSendToProcessors()[procI].size());
            
            forAll(tempList, cellI)
            {
                tempList[cellI] =
                    vf[manager_.cellsToSendToProcessors()[procI][cellI]];
            }
            
            UOPstream toBuffer(manager_.sendProcList()[procI], pBufs);
            toBuffer << tempList;
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
Foam::distributeSource::distribute
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    using volFieldType = GeometricField<Type, fvPatchField, volMesh>;
    
    // Create temporary to store the averaged results in 
    tmp<volFieldType> distributedFieldTmp
    (
        new volFieldType 
        (
            IOobject
            (
                "distributedField",
                mesh_.time().timeName(),
                mesh_,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh_,
            dimensioned<Type>(vf.dimensions(), Zero)
        )
    );

    // Create reference to field 
    auto& distributedField = distributedFieldTmp.ref();    
    
    List<List<Type>> haloCells(haloCellVolumes_.size());
    
    // Set the haloCells to zero for adding the distributed source
    // further down stream
    forAll(haloCells,i)
    {
        haloCells[i].resize(haloCellVolumes_[i].size(),pTraits<Type>::zero);
    }
    
    const auto& V = mesh_.V();
    
    
    forAll(vf,cellID)
    {
        // local cellID of this cellID for distribution
        const compactCellList& localStencilID = manager_.stencilsID()[cellID];
        
        // Take a copy for easier handling
        const Type& source = vf[cellID];

        // Loop over all cellIDs in the localStencilID list
        for (label cellI : localStencilID)
        {
            distributedField[cellI] += source*V[cellI]/totalCellVolume_[cellID];
        }
        
        // check if the cell requires parallel handling:
        if (manager_.hasProcesorContribution(cellID))
        {
            // get processors to look up from
            const labelList procList = manager_.cellToProcMap()[cellID];
            for (auto procI : procList)
            {
                List<Type>& haloCellsOfProcessorI = haloCells[procI];
                const labelList& haloCellID = manager_.haloCellIDLists()[cellID][procI];
                forAll(haloCellID,k)
                {
                    haloCellsOfProcessorI[haloCellID[k]] 
                        += source
                           *(
                                haloCellVolumes_[procI][haloCellID[k]]
                              / totalCellVolume_[cellID]
                            );
                }
            }
        }
    }
    
    if(Pstream::parRun())
    {
        // Now send the haloCells back to their processors
        PstreamBuffers pBufs(Pstream::commsTypes::nonBlocking);

        // Distribute data
        forAll(manager_.receiveProcList(), procI)
        {
            if (manager_.receiveProcList()[procI] != -1)
            {
                UOPstream toBuffer(manager_.receiveProcList()[procI], pBufs);
                toBuffer << haloCells[procI];
            }
        }

        pBufs.finishedSends();

        // Collect data

        forAll(manager_.sendProcList(), procI)
        {
            haloCells[procI].clear();
            if (manager_.sendProcList()[procI] != -1)
            {
                UIPstream fromBuffer(manager_.sendProcList()[procI], pBufs);
                fromBuffer >> haloCells[procI];
            }
        }
        
        forAll(haloCells, procI)
        {       
            forAll(haloCells[procI], cellI)
            {
                distributedField[manager_.cellsToSendToProcessors()[procI][cellI]]
                   += haloCells[procI][cellI];
            }
        }
    }
    return distributedFieldTmp;
}


template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::fvPatchField, Foam::volMesh>> 
Foam::distributeSource::distribute
(
    const tmp<GeometricField<Type, fvPatchField, volMesh>>& vf
) const
{
    tmp<GeometricField<Type, fvPatchField, volMesh>> tvf(distribute(vf()));
    vf.clear();
    return tvf;
}


template<class Type>
Foam::tmp<Foam::DimensionedField<Type, volMesh>> 
Foam::distributeSource::distribute
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
            "distributedInternalField",
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
    
    tmp<GeometricField<Type, fvPatchField, volMesh>> tvf2(distribute(tvf));
    
    Internal& Intvf2 = tvf2.ref();
    
    Intf = Intvf2;
    
    tvf2.clear();
    
    return tf;
}

#endif

// ************************************************************************* //
