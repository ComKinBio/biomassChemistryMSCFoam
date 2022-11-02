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

#include "physicoChemicalConstants.H"

using namespace Foam::constant;

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
inline const Foam::KinematicMSCCloud<CloudType>&
Foam::KinematicMSCCloud<CloudType>::cloudCopy() const
{
    return cloudCopyPtr_();
}


template<class CloudType>
inline const typename CloudType::particleType::constantProperties&
Foam::KinematicMSCCloud<CloudType>::constProps() const
{
    return constProps_;
}


template<class CloudType>
inline typename CloudType::particleType::constantProperties&
Foam::KinematicMSCCloud<CloudType>::constProps()
{
    return constProps_;
}


template<class CloudType>
inline const bool& 
Foam::KinematicMSCCloud<CloudType>::USmoothed() const
{
    return USmoothed_;
}


template<class CloudType>
inline bool& Foam::KinematicMSCCloud<CloudType>::USmoothed()
{
    return USmoothed_;
}


template<class CloudType>
inline const bool& 
Foam::KinematicMSCCloud<CloudType>::ESmoothed() const
{
    return ESmoothed_;
}


template<class CloudType>
inline bool& Foam::KinematicMSCCloud<CloudType>::ESmoothed()
{
    return ESmoothed_;
}


template<class CloudType>
inline const bool& 
Foam::KinematicMSCCloud<CloudType>::rhoSmoothed() const
{
    return rhoSmoothed_;
}


template<class CloudType>
inline bool& Foam::KinematicMSCCloud<CloudType>::rhoSmoothed()
{
    return rhoSmoothed_;
}


template<class CloudType>
inline const Foam::MSCModel<Foam::KinematicMSCCloud<CloudType>>&
Foam::KinematicMSCCloud<CloudType>::MSC() const
{
    return MSCModel_;
}


template<class CloudType>
inline Foam::MSCModel<Foam::KinematicMSCCloud<CloudType>>&
Foam::KinematicMSCCloud<CloudType>::MSC()
{
    return MSCModel_();
}


template<class CloudType>
inline Foam::tmp<Foam::fvVectorMatrix>
Foam::KinematicMSCCloud<CloudType>::SU(volVectorField& U)
{    
Info <<"Before MSC sum of Ucoeff: "<<endl;

    scalar sumUcoeff = 0.0;
    scalar UcoeffMax = 0.0;
    forAll(this->UCoeff(), u)
    {
        if (this->UCoeff()[u] > UcoeffMax)
        {
            UcoeffMax = this->UCoeff()[u];
        }
        sumUcoeff += this->UCoeff()[u];
    }
Info <<sumUcoeff<<endl;

Info <<"UcoeffMax: " << UcoeffMax<<endl;

    sumUcoeff = 0.0;
    UcoeffMax = 0.0;
    
    if (!USmoothed_)
    {
        this->UTrans() = MSC().smooth(this->UTrans());
        this->UCoeff() = MSC().smooth(this->UCoeff());
        
        USmoothed_ = true;
    }

Info <<"After MSC sum of Ucoeff: "<<endl;

    forAll(this->UCoeff(), u)
    {
        if (this->UCoeff()[u] > UcoeffMax)
        {
            UcoeffMax = this->UCoeff()[u];
        }
        
        sumUcoeff += this->UCoeff()[u];
    }
Info <<sumUcoeff<<endl;
Info <<"UcoeffMax: " << UcoeffMax<<endl;
    
    return CloudType::SU(U);
}


template<class CloudType>
inline const Foam::tmp<Foam::volScalarField> 
Foam::KinematicMSCCloud<CloudType>::theta() const
{
    
    tmp<volScalarField> ttheta
    (
        volScalarField::New
        (
            this->name() + ":thetaSmoothed",
            this->mesh_,
            dimensionedScalar(dimless, 0),
            extrapolatedCalculatedFvPatchScalarField::typeName
        )
    );

    volScalarField& theta = ttheta.ref();
    forAllConstIter(typename KinematicMSCCloud<CloudType>, *this, iter)
    {
        const parcelType& p = iter();
        const label celli = p.cell();
        
//         const scalar particleX = p.position().x();
//         const scalar R = p.d()/2.0;
//         const scalar h = (mag(particleX)+R) - 0.015;
//         
//         if ( h > 0 )
//         {
//             const scalar a_square = pow(R, 2) - pow((R - h), 2);
//             const scalar VsphereCap = 3.1415926/6.0*h*
//                                 (3*a_square + pow(h, 2));
//             theta[celli] += p.nParticle()*(p.volume() - VsphereCap);
//         }
//         else
//         {
            theta[celli] += p.nParticle()*p.volume();
//         }
    }
    
      Info<< "thera before: "<<endl;
  
    theta = MSC().smooth(theta);
    
     Info<< "thera after: "<<endl;
  
    theta.primitiveFieldRef() /= this->mesh_.V();
    theta.correctBoundaryConditions();

    return ttheta;
}


// ************************************************************************* //
