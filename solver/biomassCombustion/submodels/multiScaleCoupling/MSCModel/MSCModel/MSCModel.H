/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::MSCModel

Description
    Templated multi scale coupling model class

SourceFiles
    MSCModel.C
    MSCModelNew.C

\*---------------------------------------------------------------------------*/

#ifndef MSCModel_H
#define MSCModel_H

#include "IOdictionary.H"
#include "autoPtr.H"
#include "runTimeSelectionTables.H"
#include "CloudSubModelBase.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class MSCModel Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class MSCModel
:
    public CloudSubModelBase<CloudType>
{
    // Private Data

        //- Apply Bird's correction to the htc
//         const Switch BirdCorrection_;
    
        //- Reference to the mesh database
        const fvMesh& mesh_;


public:

    //- Runtime type information
    TypeName("MSCModel");

    //- Declare runtime constructor selection table
    declareRunTimeSelectionTable
    (
        autoPtr,
        MSCModel,
        dictionary,
        (
            const dictionary& dict,
            CloudType& owner
        ),
        (dict, owner)
    );


    // Constructors

        //- Construct null from owner
        MSCModel(CloudType& owner);

        //- Construct from dictionary
        MSCModel
        (
            const dictionary& dict,
            CloudType& owner,
            const word& type
        );

        //- Construct copy
        MSCModel(const MSCModel<CloudType>& mscm);

        //- Construct and return a clone
        virtual autoPtr<MSCModel<CloudType>> clone() const = 0;


    //- Destructor
    virtual ~MSCModel();


    //- Selector
    static autoPtr<MSCModel<CloudType>> New
    (
        const dictionary& dict,
        CloudType& owner
    );


    // Member Functions

        // Access

            //- Return the Bird htc correction flag
//             const Switch& BirdCorrection() const;
    
            //- Return the mesh database
            inline const fvMesh& mesh() const;

        // Field calculation
        
            //- Avarging calculation of the gas field
            virtual tmp<volScalarField> sample
            (
                const volScalarField& vf
            ) const = 0;
            
            
            virtual tmp<volVectorField> sample
            (
                const volVectorField& vf
            ) const = 0;
            
            
            //- Redistribution of particle data, vol field data
            virtual tmp<volScalarField> smooth
            (
                const volScalarField& vf
            ) const = 0;
            
            
            virtual tmp<volVectorField> smooth
            (
                const volVectorField& vf
            ) const = 0;
            
            
            //- Redistribution of particle data, vol field data
            virtual tmp<volScalarField::Internal> smooth
            (
                const volScalarField::Internal& vfi
            ) const = 0;
            
            
            virtual tmp<volVectorField::Internal> smooth
            (
                const volVectorField::Internal& vfi
            ) const = 0;
            
    
        // I-O

            //- Write injection info to stream
            virtual void info(Ostream& os);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// add a inline function here
template<class CloudType>
inline const Foam::fvMesh& Foam::MSCModel<CloudType>::mesh() const
{
    return mesh_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeMSCModel(CloudType)                                                \
                                                                               \
    typedef Foam::CloudType::kinematicMSCCloudType kinematicMSCCloudType;      \
    defineNamedTemplateTypeNameAndDebug                                        \
    (                                                                          \
        Foam::MSCModel<kinematicMSCCloudType>,                                 \
        0                                                                      \
    );                                                                         \
    namespace Foam                                                             \
    {                                                                          \
        defineTemplateRunTimeSelectionTable                                    \
        (                                                                      \
            MSCModel<kinematicMSCCloudType>,                                   \
            dictionary                                                         \
        );                                                                     \
    }


#define makeMSCModelType(SS, CloudType)                                        \
                                                                               \
    typedef Foam::CloudType::kinematicMSCCloudType kinematicMSCCloudType;      \
    defineNamedTemplateTypeNameAndDebug(Foam::SS<kinematicMSCCloudType>, 0);   \
                                                                               \
    Foam::MSCModel<kinematicMSCCloudType>::                                    \
        adddictionaryConstructorToTable<Foam::SS<kinematicMSCCloudType>>       \
            add##SS##CloudType##kinematicMSCCloudType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "MSCModel.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
