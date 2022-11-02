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

#include "virtualTGM.H"

#include "coarserGrid.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::virtualTGM<CloudType>::virtualTGM
(
    const dictionary& dict,
    CloudType& cloud
)
:
    MSCModel<CloudType>(dict, cloud, typeName),
    coarseGridOrigin_(vector(this->coeffDict().lookup("gridOrigin"))),
    coarseGridVertex_(vector(this->coeffDict().lookup("gridVertex"))),
    coarseGridSize_(vector(this->coeffDict().lookup("coarseGridSize"))),
    coarserGrid_(nullptr)
{
    Info<< "create virtualTGM method..." << endl;
    
    coarserGrid_.reset
    (
        new coarserGrid
        (
            this->mesh(),
            coarseGridOrigin_,
            coarseGridVertex_,
            coarseGridSize_
        )
    );
}


template<class CloudType>
Foam::virtualTGM<CloudType>::virtualTGM(const virtualTGM<CloudType>& mscm)
:
    MSCModel<CloudType>(mscm),
    coarseGridOrigin_(mscm.coarseGridOrigin_),
    coarseGridVertex_(mscm.coarseGridVertex_),
    coarseGridSize_(mscm.coarseGridSize_),
    coarserGrid_(mscm.coarserGrid_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::virtualTGM<CloudType>::~virtualTGM()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::virtualTGM<CloudType>::sample
(
    const volScalarField& vf
) const
{
    return coarserGrid_->averagedField(vf);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::virtualTGM<CloudType>::sample
(
    const volVectorField& vf
) const
{
    return coarserGrid_->averagedField(vf);
}


template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::virtualTGM<CloudType>::smooth
(
    const volScalarField& vf
) const
{
    return coarserGrid_->averagedSourceField(vf);
}



template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::virtualTGM<CloudType>::smooth
(
    const volVectorField& vf
) const
{
    tmp<volVectorField> averagedFieldTmp
    (
        vf
    );
    
    return averagedFieldTmp;
}


template<class CloudType>
Foam::tmp<Foam::volScalarField::Internal> 
Foam::virtualTGM<CloudType>::smooth
(
    const volScalarField::Internal& vfi
) const
{
    return coarserGrid_->averagedSource(vfi);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField::Internal> 
Foam::virtualTGM<CloudType>::smooth
(
    const volVectorField::Internal& vfi
) const
{
    return coarserGrid_->averagedSource(vfi);
}


// ************************************************************************* //
