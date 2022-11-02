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

#include "steppedDBM.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::steppedDBM<CloudType>::steppedDBM
(
    const dictionary& dict,
    CloudType& cloud
)
:
    MSCModel<CloudType>(dict, cloud, typeName)
{}


template<class CloudType>
Foam::steppedDBM<CloudType>::steppedDBM(const steppedDBM<CloudType>& mscm)
:
    MSCModel<CloudType>(mscm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::steppedDBM<CloudType>::~steppedDBM()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// how to iterate particle data
// template<class CloudType>
// void Foam::PairCollision<CloudType>::preInteraction()
// {
//     // Set accumulated quantities to zero
//     forAllIter(typename CloudType, this->owner(), iter)
//     {
//         typename CloudType::parcelType& p = iter();
// 
//         p.f() = Zero;
// 
//         p.torque() = Zero;
//     }
// }


template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::steppedDBM<CloudType>::sample
(
    const volScalarField& vf
) const
{
    tmp<volScalarField> averagedFieldTmp
    (
        vf
    );
    
    return averagedFieldTmp;
}


template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::steppedDBM<CloudType>::sample
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
Foam::tmp<Foam::volScalarField> 
Foam::steppedDBM<CloudType>::smooth
(
    const volScalarField& vf
) const
{
    tmp<volScalarField> averagedFieldTmp
    (
        vf
    );
    
    return averagedFieldTmp;
}


template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::steppedDBM<CloudType>::smooth
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
Foam::steppedDBM<CloudType>::smooth
(
    const volScalarField::Internal& vfi
) const
{
    tmp<volScalarField::Internal> averagedFieldTmp
    (
        vfi
    );
    
    return averagedFieldTmp;
}


template<class CloudType>
Foam::tmp<Foam::volVectorField::Internal> 
Foam::steppedDBM<CloudType>::smooth
(
    const volVectorField::Internal& vfi
) const
{
    tmp<volVectorField::Internal> averagedFieldTmp
    (
        vfi
    );
    
    return averagedFieldTmp;
}


// ************************************************************************* //
