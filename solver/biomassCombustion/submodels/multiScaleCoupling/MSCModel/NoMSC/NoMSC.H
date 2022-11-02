/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
    Foam::NoMSC

Description
    Dummy multi scale coupling model for 'none'

\*---------------------------------------------------------------------------*/

#ifndef NoMSC_H
#define NoMSC_H

#include "MSCModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class NoMSC Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class NoMSC
:
    public MSCModel<CloudType>
{
public:

    //- Runtime type information
    TypeName("none");


    // Constructors

        //- Construct from dictionary
        NoMSC(const dictionary&, CloudType& owner);

        //- Construct copy
        NoMSC(const NoMSC<CloudType>& mscm);

        //- Construct and return a clone
        virtual autoPtr<MSCModel<CloudType>> clone() const
        {
            return autoPtr<MSCModel<CloudType>>
            (
                new NoMSC<CloudType>(*this)
            );
        }


    //- Destructor
    virtual ~NoMSC();


    // Member Functions

        
        // Field calculation
        
            //- Avarging calculation of the gas field
            virtual tmp<volScalarField> sample
            (
                const volScalarField& vf
            ) const;
            
            
            virtual tmp<volVectorField> sample
            (
                const volVectorField& vf
            ) const;
            
            
            //- Redistribution of particle data, vol field data
            virtual tmp<volScalarField> smooth
            (
                const volScalarField& vf
            ) const;
            
            
            virtual tmp<volVectorField> smooth
            (
                const volVectorField& vf
            ) const;
            
            
            //- Redistribution of particle data, vol field data
            virtual tmp<volScalarField::Internal> smooth
            (
                const volScalarField::Internal& vfi
            ) const;
            
            
            virtual tmp<volVectorField::Internal> smooth
            (
                const volVectorField::Internal& vfi
            ) const;
            
            template<class Type>
            tmp<GeometricField<Type, fvPatchField, volMesh>> 
            same
            (
                const GeometricField<Type, fvPatchField, volMesh>& vf
            ) const;
            
            
            template<class Type>
            tmp<DimensionedField<Type, volMesh>> 
            same
            (
                const DimensionedField<Type, volMesh>& f
            ) const;
            
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "NoMSC.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
