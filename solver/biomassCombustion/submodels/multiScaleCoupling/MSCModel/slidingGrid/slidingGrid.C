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

#include "slidingGrid.H"

#include "movingAverage/movingAverage.H"
#include "distributeSource/distributeSource.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::slidingGrid<CloudType>::slidingGrid
(
    const dictionary& dict,
    CloudType& cloud
)
:
    MSCModel<CloudType>(dict, cloud, typeName),
    length_(readScalar(this->coeffDict().lookup("length"))),
    width_(this->coeffDict().lookupOrDefault("width", length_)),
    height_(this->coeffDict().lookupOrDefault("height", length_)),
    box_(width_, length_, height_),
    movingBoxAvger_(nullptr),
    distSource_(nullptr),
    alphaWeightedSmoothing_(this->coeffDict().lookupOrDefault("alphaWeighted", false))
{
    
    Info<< "create movingAverage and distributeSource method..." << endl;
    
    movingBoxAvger_.reset
    (
        new movingAverage
        (
            this->mesh(),
            box_
        )
    );
    
    distSource_.reset
    (
        new distributeSource
        (
            this->mesh(),
            box_
        )
    );
}


template<class CloudType>
Foam::slidingGrid<CloudType>::slidingGrid(const slidingGrid<CloudType>& mscm)
:
    MSCModel<CloudType>(mscm),
    length_(mscm.length_),
    width_(mscm.width_),
    height_(mscm.height_),
    box_(mscm.box_),
    movingBoxAvger_(mscm.movingBoxAvger_),
    distSource_(mscm.distSource_),
    alphaWeightedSmoothing_(mscm.alphaWeightedSmoothing_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::slidingGrid<CloudType>::~slidingGrid()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::slidingGrid<CloudType>::sample
(
    const volScalarField& vf
) const
{
    if (alphaWeightedSmoothing_)
    {
        const volScalarField& alphac =
            this->mesh().template lookupObject<volScalarField>("alpha.air");
            
        const volScalarField alphacVf = alphac*vf;
        
        tmp<volScalarField> averageVf = movingBoxAvger_->average(alphacVf);
        
        tmp<volScalarField> averageAlphac = movingBoxAvger_->average(alphac);
        
        volScalarField& averageVfRef = averageVf.ref();
        
        volScalarField& averageAlphacRef = averageAlphac.ref();
        
        averageVfRef = averageVfRef/averageAlphacRef;
        
        return averageVf;
    }
    else
    {
        return movingBoxAvger_->average(vf);
    }
}


template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::slidingGrid<CloudType>::sample
(
    const volVectorField& vf
) const
{    
    if (alphaWeightedSmoothing_)
    {
        const volScalarField& alphac =
            this->mesh().template lookupObject<volScalarField>("alpha.air");
            
        const volVectorField alphacVf = alphac*vf;
        
        tmp<volVectorField> averageVf = movingBoxAvger_->average(alphacVf);
        
        tmp<volScalarField> averageAlphac = movingBoxAvger_->average(alphac);
        
        volVectorField& averageVfRef = averageVf.ref();
        
        volScalarField& averageAlphacRef = averageAlphac.ref();
        
        averageVfRef = averageVfRef/averageAlphacRef;       
        return averageVf;
    }
    else
    {
        return movingBoxAvger_->average(vf);
    }
}


template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::slidingGrid<CloudType>::smooth
(
    const volScalarField& vf
) const
{
    return distSource_->distribute(vf);
}



template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::slidingGrid<CloudType>::smooth
(
    const volVectorField& vf
) const
{    
    return distSource_->distribute(vf);
}


template<class CloudType>
Foam::tmp<Foam::volScalarField::Internal> 
Foam::slidingGrid<CloudType>::smooth
(
    const volScalarField::Internal& vfi
) const
{
    return distSource_->distribute(vfi);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField::Internal> 
Foam::slidingGrid<CloudType>::smooth
(
    const volVectorField::Internal& vfi
) const
{
    return distSource_->distribute(vfi);
}


// ************************************************************************* //
