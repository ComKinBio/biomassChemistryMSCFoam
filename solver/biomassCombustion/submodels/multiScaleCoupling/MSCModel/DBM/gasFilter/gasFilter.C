/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2014 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include "gasFilter.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
Foam::gasFilter::gasFilter
(
    const fvMesh& mesh,
    const dimensionedTensor& DT,
    const scalar diffusionBandWidth,
    const label diffusionSteps
)
:       
    mesh_(mesh),
    diffusionRunTime_
    (
        "controlDiffDict",
        mesh.time().rootPath(),
        mesh.time().caseName()
    ),
    diffusionMesh_
    (
        IOobject
        (
            fvMesh::defaultRegion,
            diffusionRunTime_.timeName(),
            diffusionRunTime_,
            IOobject::MUST_READ
        )
    ),
    simple_(diffusionMesh_),
    DT(DT),
    startTime(diffusionRunTime_.startTime()),
    startTimeIndex(diffusionRunTime_.startTimeIndex()),
    diffusionBandWidth_(diffusionBandWidth),
    diffusionSteps_(diffusionSteps),
    diffusionTime_(0),
    diffusionDeltaT_(0)
{
    //- initialization information output    
    // determine the time and time step in diffusion procedure
    diffusionTime_ = pow(diffusionBandWidth_, 2)/4;
    diffusionDeltaT_ = diffusionTime_/diffusionSteps_;

}
    
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
// const access
inline Foam::scalar
Foam::gasFilter::diffusionBandWidth() const
{
    return diffusionBandWidth_;
}


inline Foam::label
Foam::gasFilter::diffusionSteps() const
{
    return diffusionSteps_;
}


inline Foam::scalar
Foam::gasFilter::diffusionDeltaT() const
{
    return diffusionDeltaT_;
}


inline Foam::scalar
Foam::gasFilter::diffusionTime() const
{
    return diffusionTime_;
}


// access to diffusion settings
inline Foam::scalar&
Foam::gasFilter::diffusionBandWidth()
{
    return diffusionBandWidth_;
}


inline Foam::label&
Foam::gasFilter::diffusionSteps()
{
    return diffusionSteps_;
}


inline Foam::scalar&
Foam::gasFilter::diffusionDeltaT()
{
    return diffusionDeltaT_;
}


inline Foam::scalar&
Foam::gasFilter::diffusionTime()
{
    return diffusionTime_;
}


// Return the filtered field from the given volScalarField F
tmp<volScalarField>
Foam::gasFilter::filteredField(const volScalarField& F) const
{
        
    diffusionRunTime_.setEndTime(diffusionTime_);
    diffusionRunTime_.setDeltaT(diffusionDeltaT_);
    
    tmp<volScalarField> tF
    (
        volScalarField::New
        (
            "tF",
            mesh_,
            F.dimensions()
        )
    );

    volScalarField& S = tF.ref();
    
    S = F;
    
    scalarField& iS = S;
    
    volScalarField diffWorkField
    (
        IOobject
        (
            "tempGasDiffScalar",
            diffusionRunTime_.timeName(),
            diffusionMesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        diffusionMesh_,
        dimensionedScalar
        (
            "zero",
            S.dimensions(),
            scalar(0.0)
        ),
        zeroGradientFvPatchScalarField::typeName
        
    );

    
    scalarField& diffWorkFieldInterFeildRef = diffWorkField.ref();
    
    diffWorkFieldInterFeildRef = iS;
    
    while (simple_.loop(diffusionRunTime_))
    {
        if (diffusionRunTime_.timeIndex() == 1)
        {
            while (simple_.correctNonOrthogonal())
            {
                solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField,"gasFilterDiffusion"));
            }
        }
        else
        {
            solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField,"gasFilterDiffusion"));
        }
    }
    
    iS = diffWorkFieldInterFeildRef;
    
    S.correctBoundaryConditions();
    
    diffusionRunTime_.setTime(startTime, startTimeIndex);
    
    return tF;
}


tmp<volVectorField>
Foam::gasFilter::filteredField(const volVectorField& F) const
{
    diffusionRunTime_.setEndTime(diffusionTime_);
    diffusionRunTime_.setDeltaT(diffusionDeltaT_);
    
    tmp<volVectorField> tF
    (
        volVectorField::New
        (
            "tF",
            mesh_,
            F.dimensions()
        )
    );

    volVectorField& S = tF.ref();
    
    S = F;
    
    vectorField& iS = S;
    
    volVectorField diffWorkField
    (
        IOobject
        (
            "tempGasDiffScalar",
            diffusionRunTime_.timeName(),
            diffusionMesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        diffusionMesh_,
        dimensionedVector
        (
            "zero",
            S.dimensions(),
            vector::zero
        ),
        zeroGradientFvPatchVectorField::typeName
            
    );

    
    vectorField& diffWorkFieldInterFeildRef = diffWorkField.ref();
    
    diffWorkFieldInterFeildRef = iS;
    
    while (simple_.loop(diffusionRunTime_))
    {
        if (diffusionRunTime_.timeIndex() == 1)
        {
            while (simple_.correctNonOrthogonal())
            {
                solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField,"gasFilterDiffusion"));
            }
        }
        else
        {
            solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField,"gasFilterDiffusion"));
        }
    }
    
    iS = diffWorkFieldInterFeildRef;
    
    S.correctBoundaryConditions();
    
    diffusionRunTime_.setTime(startTime, startTimeIndex);
    
    return tF;
}


tmp<volScalarField>
Foam::gasFilter::filteredField
(
    const volScalarField& alpha,
    const volScalarField& F
) const
{
    diffusionRunTime_.setEndTime(diffusionTime_);
    diffusionRunTime_.setDeltaT(diffusionDeltaT_);
    
    tmp<volScalarField> tF
    (
        volScalarField::New
        (
            "tF",
            mesh_,
            F.dimensions()
        )
    );

    volScalarField& S = tF.ref();
    
    S = F;
    
    scalarField& iS = S;
    
    volScalarField diffWorkField
    (
        IOobject
        (
            "tempGasDiffScalar",
            diffusionRunTime_.timeName(),
            diffusionMesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        diffusionMesh_,
        dimensionedScalar
        (
            "zero",
            S.dimensions(),
            scalar(0.0)
        ),
        zeroGradientFvPatchScalarField::typeName
        
    );

    
    scalarField& diffWorkFieldInterFeildRef = diffWorkField.ref();
    
    diffWorkFieldInterFeildRef = iS;
    
    while (simple_.loop(diffusionRunTime_))
    {
        if (diffusionRunTime_.timeIndex() == 1)
        {
            while (simple_.correctNonOrthogonal())
            {
                solve(fvm::ddt(diffWorkField) - fvm::laplacian(fvc::interpolate(alpha)*DT, diffWorkField,"gasFilterDiffusion"));
            }
        }
        else
        {
            solve(fvm::ddt(diffWorkField) - fvm::laplacian(fvc::interpolate(alpha)*DT, diffWorkField,"gasFilterDiffusion"));
        }
    }
    
    iS = diffWorkFieldInterFeildRef;
    
    S.correctBoundaryConditions();
    
    diffusionRunTime_.setTime(startTime, startTimeIndex);
    
    return tF;
}


tmp<volVectorField>
Foam::gasFilter::filteredField
(
    const volScalarField& alpha,
    const volVectorField& F
) const
{
    diffusionRunTime_.setEndTime(diffusionTime_);
    diffusionRunTime_.setDeltaT(diffusionDeltaT_);
    
    tmp<volVectorField> tF
    (
        volVectorField::New
        (
            "tF",
            mesh_,
            F.dimensions()
        )
    );

    volVectorField& S = tF.ref();
    
    S = F;
    
    vectorField& iS = S;
    
    volVectorField diffWorkField
    (
        IOobject
        (
            "tempGasDiffScalar",
            diffusionRunTime_.timeName(),
            diffusionMesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        diffusionMesh_,
        dimensionedVector
        (
            "zero",
            S.dimensions(),
            vector::zero
        ),
        zeroGradientFvPatchVectorField::typeName
            
    );

    
    vectorField& diffWorkFieldInterFeildRef = diffWorkField.ref();
    
    diffWorkFieldInterFeildRef = iS;
    
    while (simple_.loop(diffusionRunTime_))
    {
        if (diffusionRunTime_.timeIndex() == 1)
        {
            while (simple_.correctNonOrthogonal())
            {
                solve(fvm::ddt(diffWorkField) - fvm::laplacian(fvc::interpolate(alpha)*DT, diffWorkField,"gasFilterDiffusion"));
            }
        }
        else
        {
            solve(fvm::ddt(diffWorkField) - fvm::laplacian(fvc::interpolate(alpha)*DT, diffWorkField,"gasFilterDiffusion"));
        }
    }
    
    iS = diffWorkFieldInterFeildRef;
    
    S.correctBoundaryConditions();
    
    diffusionRunTime_.setTime(startTime, startTimeIndex);
    
    return tF;
}


Foam::tmp<Foam::volScalarField::Internal> 
Foam::gasFilter::filteredField
(
    const volScalarField::Internal& s
) const
{    
    diffusionRunTime_.setEndTime(diffusionTime_);
    diffusionRunTime_.setDeltaT(diffusionDeltaT_);
    
    tmp<volScalarField::Internal> tS
    (
        volScalarField::Internal::New
        (
            "tS",
            mesh_,
            dimensionedScalar(s.dimensions(), 0.0)
        )
    );

    scalarField& S = tS.ref();
    
    S = s;
    
    volScalarField diffWorkField
    (
        IOobject
        (
            "tempDiffScalar",
            diffusionRunTime_.timeName(),
            diffusionMesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        diffusionMesh_,
        dimensionedScalar
        (
            "zero",
            s.dimensions(),
            scalar(0.0)
        ),
        zeroGradientFvPatchScalarField::typeName
        
    );

    
    scalarField& diffWorkFieldInterFeildRef = diffWorkField.ref();
    
    diffWorkFieldInterFeildRef = S;
    
    while (diffusionRunTime_.loop())
    {
        if (diffusionRunTime_.timeIndex() == 1)
        {
            while (simple_.correctNonOrthogonal())
            {
                solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField));
            }
        }
        else
        {
            solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField));
        }
    }

    
    S = diffWorkField.internalField();
    
    diffusionRunTime_.setTime(startTime, startTimeIndex);

    return tS;
}

Foam::tmp<Foam::volVectorField::Internal> 
Foam::gasFilter::filteredField
(
    const volVectorField::Internal& s
) const
{
    
    diffusionRunTime_.setEndTime(diffusionTime_);
    diffusionRunTime_.setDeltaT(diffusionDeltaT_);
    
    tmp<volVectorField::Internal> tS
    (
        volVectorField::Internal::New
        (
            "tS",
            mesh_,
            dimensionedVector(s.dimensions(), vector::zero)
        )
    );

    vectorField& S = tS.ref();
    
    S = s;
    
    volVectorField diffWorkField
    (
        IOobject
        (
            "tempDiffVector",
            diffusionRunTime_.timeName(),
            diffusionMesh_,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        diffusionMesh_,
        dimensionedVector
        (
            "zero",
            s.dimensions(),
            vector::zero
        ),
        zeroGradientFvPatchVectorField::typeName
        
    );

    
    vectorField& diffWorkFieldInterFeildRef = diffWorkField.ref();
    
    diffWorkFieldInterFeildRef = S;
    
    while (diffusionRunTime_.loop())
    {
        if (diffusionRunTime_.timeIndex() == 1)
        {
            while (simple_.correctNonOrthogonal())
            {
                solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField));
            }
        }
        else
        {
            solve(fvm::ddt(diffWorkField) - fvm::laplacian(DT, diffWorkField));
        }
    }
    
    S = diffWorkField.internalField();
    
    diffusionRunTime_.setTime(startTime, startTimeIndex);

    return tS;
}





// ************************************************************************* //
