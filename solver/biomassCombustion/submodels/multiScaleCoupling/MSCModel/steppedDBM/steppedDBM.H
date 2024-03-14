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
    Foam::steppedDBM

Description
    The diffusion based method, not finished, can not be used now TODO

\*---------------------------------------------------------------------------*/

#ifndef steppedDBM_H
#define steppedDBM_H

#include "MSCModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class steppedDBM Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class steppedDBM
:
    public MSCModel<CloudType>
{

public:

    //- Runtime type information
    TypeName("steppedDBM");


    // Constructors

        //- Construct from dictionary
        steppedDBM(const dictionary& dict, CloudType& cloud);

        //- Construct copy
        steppedDBM(const steppedDBM<CloudType>& mscm);

        //- Construct and return a clone
        virtual autoPtr<MSCModel<CloudType>> clone() const
        {
            return autoPtr<MSCModel<CloudType>>
            (
                new steppedDBM<CloudType>(*this)
            );
        }


    //- Destructor
    virtual ~steppedDBM();


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
    #include "steppedDBM.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
