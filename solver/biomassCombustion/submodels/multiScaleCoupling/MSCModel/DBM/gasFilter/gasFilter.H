/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
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
    Foam::gasFilter

Description

    filter method for particle gas terms

SourceFiles
    gasFilter.H
    gasFilter.C

\*---------------------------------------------------------------------------*/

#ifndef gasFilter_H
#define gasFilter_H

#include "fvCFD.H"
#include "simpleControl.H"
#include "error.H"
#include "demandDrivenEntry.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class coarserGrid Declaration
\*---------------------------------------------------------------------------*/

class gasFilter
{  
    //*******************************access and information read from settings*********************************//
   
    //- Gas Mesh class
    const fvMesh& mesh_;

    //- Diffusion time class
    mutable Time diffusionRunTime_;
    
    //- Diffusion control class
    fvMesh diffusionMesh_;
    
    //- Diffusion Mesh class
    mutable simpleControl simple_;
    
    //- Diffusion tensor direction
    tensor smoothDirection_;
    
    //- Diffusion tensor
    dimensionedTensor DT;
    
    //- Diffusion start time
    dimensionedScalar startTime;
    label startTimeIndex;
    
    
    //- Phase diffusion band width
    scalar diffusionBandWidth_;
        
    //- Diffusion number of time steps
    label diffusionSteps_;
    
    //- Diffusion time and time step for different gas terms
    scalar diffusionTime_;
    scalar diffusionDeltaT_;
    
    
    //*******************************variables in grid calculation*********************************//      
        

    public:
  
    // Constructors

        //- Construct from fine mesh and input settings
        gasFilter
        (
            const fvMesh& mesh,
            const dimensionedTensor& DT,
            const scalar diffusionBandWidth,
            const label diffusionSteps
        );


    //- Destructor
    ~gasFilter()
    {}

    // Member Functions
    
        //- Return const access to the Phase diffusion band width
        inline scalar diffusionBandWidth() const;
        
        //- Return const access to the Diffusion number of time steps
        inline label diffusionSteps() const;
        
        //- Return const access to the Phase diffusion diffusionTime
        inline scalar diffusionTime() const;
        
        //- Return const access to the Diffusion time steps
        inline scalar diffusionDeltaT() const;
        
        
        
        //- Return access to the Phase diffusion band width
        inline scalar& diffusionBandWidth();
        
        //- Return access to the Diffusion number of time steps
        inline label& diffusionSteps();
        
        //- Return access to the Phase diffusion diffusionTime
        inline scalar& diffusionTime();
        
        //- Return access to the Diffusion time steps
        inline scalar& diffusionDeltaT();
        
        //- Return the filtered field from the given volScalarField F
        tmp<volScalarField> filteredField(const volScalarField& F) const;
        
        tmp<volVectorField> filteredField(const volVectorField& F) const;
        
        //- Return the filtered field from the given volScalarField F and alpha field
        tmp<volScalarField> filteredField(const volScalarField& alpha, const volScalarField& F) const;
        
        tmp<volVectorField> filteredField(const volScalarField& alpha, const volVectorField& F) const;
        
        //- Return the diffused field obtained from the given volScalarField s
        tmp<volScalarField::Internal> filteredField(const volScalarField::Internal& s) const;

        //- Return the diffused field obtained from the given volVectorField s
        tmp<volVectorField::Internal> filteredField(const volVectorField::Internal& s) const;
        
    

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

}// End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif

// ************************************************************************* //
