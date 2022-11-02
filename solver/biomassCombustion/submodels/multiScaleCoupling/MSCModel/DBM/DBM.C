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

\*---------------------------------------------------------------------------*/

#include "DBM.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::DBM<CloudType>::DBM
(
    const dictionary& dict,
    CloudType& cloud
)
:
    MSCModel<CloudType>(dict, cloud, typeName),
    DT_
    (
        "DT", 
        dimensionSet(0, 2, -1, 0, 0), 
        this->coeffDict().lookupOrDefault
        (
            "smoothDirection",
            tensor(1.0, 0, 0, 0, 1.0, 0, 0, 0, 1.0)
        )
    ),
    diffusionBandWidth_(readScalar(this->coeffDict().lookup("bandWidth"))),
    diffusionSteps_(this->coeffDict().lookupOrDefault("diffusionSteps", 3)),
    diffusion_(nullptr)
{
    diffusion_.reset
    (
        new gasFilter
        (
            this->mesh(),
            DT_,
            diffusionBandWidth_,
            diffusionSteps_
        )
    );
}


template<class CloudType>
Foam::DBM<CloudType>::DBM(const DBM<CloudType>& mscm)
:
    MSCModel<CloudType>(mscm),
    DT_(mscm.DT_),
    diffusionBandWidth_(mscm.diffusionBandWidth_),
    diffusionSteps_(mscm.diffusionSteps_),
    diffusion_(mscm.diffusion_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::DBM<CloudType>::~DBM()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::DBM<CloudType>::sample
(
    const volScalarField& vf
) const
{
    tmp<Foam::volScalarField> tvf(diffusion_->filteredField(vf));
    return tvf;
//     return diffusion_->filteredField(vf);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::DBM<CloudType>::sample
(
    const volVectorField& vf
) const
{
    return diffusion_->filteredField(vf);
}


template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::DBM<CloudType>::smooth
(
    const volScalarField& vf
) const
{
    return diffusion_->filteredField(vf);
}



template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::DBM<CloudType>::smooth
(
    const volVectorField& vf
) const
{
   return diffusion_->filteredField(vf);
}


template<class CloudType>
Foam::tmp<Foam::volScalarField::Internal> 
Foam::DBM<CloudType>::smooth
(
    const volScalarField::Internal& vfi
) const
{
    return diffusion_->filteredField(vfi);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField::Internal> 
Foam::DBM<CloudType>::smooth
(
    const volVectorField::Internal& vfi
) const
{
   return diffusion_->filteredField(vfi);
}


// ************************************************************************* //
