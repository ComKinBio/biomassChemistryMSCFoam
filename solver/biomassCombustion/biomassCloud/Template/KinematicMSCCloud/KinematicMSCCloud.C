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

#include "KinematicMSCCloud.H"
#include "MSCModel.H"


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::setModels()
{
    MSCModel_.reset
    (
        MSCModel<KinematicMSCCloud<CloudType>>::New
        (
            this->subModelProperties(),
            *this
        ).ptr()
    );
}


template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::cloudReset(KinematicMSCCloud<CloudType>& c)
{
    CloudType::cloudReset(c);

    MSCModel_.reset(c.MSCModel_.ptr());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::KinematicMSCCloud<CloudType>::KinematicMSCCloud
(
    const word& cloudName,
    const volScalarField& rho,
    const volVectorField& U,
    const volScalarField& mu,
    const dimensionedVector& g,
    bool readFields
)
:
    CloudType
    (
        cloudName,
        rho,
        U,
        mu,
        g,
        false
    ),
    kinematicMSCCloud(),
    cloudCopyPtr_(nullptr),
    USmoothed_(false),
    ESmoothed_(false),
    rhoSmoothed_(false),
    constProps_(this->particleProperties()),
    MSCModel_(nullptr)
{
    if (this->solution().active())
    {
        setModels();

        if (readFields)
        {
            parcelType::readFields(*this);
        }
    }
}


template<class CloudType>
Foam::KinematicMSCCloud<CloudType>::KinematicMSCCloud
(
    KinematicMSCCloud<CloudType>& c,
    const word& name
)
:
    CloudType(c, name),
    kinematicMSCCloud(),
    cloudCopyPtr_(nullptr),
    USmoothed_(false),
    ESmoothed_(false),
    rhoSmoothed_(false),
    constProps_(c.constProps_),
    MSCModel_(c.MSCModel_->clone())
{}


template<class CloudType>
Foam::KinematicMSCCloud<CloudType>::KinematicMSCCloud
(
    const fvMesh& mesh,
    const word& name,
    const KinematicMSCCloud<CloudType>& c
)
:
    CloudType(mesh, name, c),
    kinematicMSCCloud(),
    cloudCopyPtr_(nullptr),
    USmoothed_(false),
    ESmoothed_(false),
    rhoSmoothed_(false),
    constProps_(),
    MSCModel_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::KinematicMSCCloud<CloudType>::~KinematicMSCCloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::storeState()
{
    cloudCopyPtr_.reset
    (
        static_cast<KinematicMSCCloud<CloudType>*>
        (
            clone(this->name() + "Copy").ptr()
        )
    );
}


template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::restoreState()
{
    cloudReset(cloudCopyPtr_());
    cloudCopyPtr_.clear();
}


template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::resetSourceTerms()
{
    CloudType::resetSourceTerms();
    
    USmoothed_ = false,
    ESmoothed_ = false,
    rhoSmoothed_ = false;
}


template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::evolve()
{
    if (this->solution().canEvolve())
    {
        typename parcelType::trackingData td(*this);

        this->solve(*this, td);        
    }
}


template<class CloudType>
void Foam::KinematicMSCCloud<CloudType>::info()
{
    CloudType::info();

    this->MSC().info(Info);
}


// ************************************************************************* //
