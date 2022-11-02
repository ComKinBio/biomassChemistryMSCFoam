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
    Foam::DBM

Description
    The diffusion based method

\*---------------------------------------------------------------------------*/

#ifndef DBM_H
#define DBM_H

#include "MSCModel.H"
#include "fvCFD.H"
#include "simpleControl.H"
#include "error.H"
#include "gasFilter.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class DBM Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class DBM
:
    public MSCModel<CloudType>
{

    // Protected Data
    const dimensionedTensor DT_;
    
    const scalar diffusionBandWidth_;
    
    const label diffusionSteps_;
    
    //- diffusion calculater    
    autoPtr<gasFilter> diffusion_;
    
public:

    //- Runtime type information
    TypeName("DBM");


    // Constructors

        //- Construct from dictionary
        DBM(const dictionary& dict, CloudType& cloud);

        //- Construct copy
        DBM(const DBM<CloudType>& mscm);

        //- Construct and return a clone
        virtual autoPtr<MSCModel<CloudType>> clone() const
        {
            return autoPtr<MSCModel<CloudType>>
            (
                new DBM<CloudType>(*this)
            );
        }


    //- Destructor
    virtual ~DBM();


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
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "DBM.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
