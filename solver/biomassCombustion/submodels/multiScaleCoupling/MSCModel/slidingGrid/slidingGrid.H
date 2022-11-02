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
    Foam::slidingGrid

Description
    The diffusion based method

\*---------------------------------------------------------------------------*/

#ifndef slidingGrid_H
#define slidingGrid_H

#include "MSCModel.H"

#include "aveSpace/aveBox/aveBox.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    
// Forward declaration of classes

class movingAverage;

class distributeSource;

/*---------------------------------------------------------------------------*\
                         Class slidingGrid Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class slidingGrid
:
    public MSCModel<CloudType>
{
    
    // Protected Data
    
        //- avgSpace size
        const scalar length_;
        const scalar width_;    
        const scalar height_;
        
        //- avgBox object
        const aveBox box_;
        
        //- movingAverage calculator    
        autoPtr<movingAverage> movingBoxAvger_;
        
        //- distributeSource calculator    
        autoPtr<distributeSource> distSource_;
        
        //- Using alphaWeighted sample
        const Switch alphaWeightedSmoothing_;
        

public:

    //- Runtime type information
    TypeName("slidingGrid");


    // Constructors

        //- Construct from dictionary
        slidingGrid(const dictionary& dict, CloudType& cloud);

        //- Construct copy
        slidingGrid(const slidingGrid<CloudType>& mscm);

        //- Construct and return a clone
        virtual autoPtr<MSCModel<CloudType>> clone() const
        {
            return autoPtr<MSCModel<CloudType>>
            (
                new slidingGrid<CloudType>(*this)
            );
        }


    //- Destructor
    virtual ~slidingGrid();


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
    #include "slidingGrid.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
