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

#include "MSCModel.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::MSCModel<CloudType>::MSCModel(CloudType& owner)
:
    CloudSubModelBase<CloudType>(owner),
    mesh_(owner.mesh())/*,
    BirdCorrection_(false)*/
{}


template<class CloudType>
Foam::MSCModel<CloudType>::MSCModel
(
    const dictionary& dict,
    CloudType& owner,
    const word& type
)
:
    CloudSubModelBase<CloudType>(owner, dict, typeName, type),
    mesh_(owner.mesh())/*,
    BirdCorrection_(this->coeffDict().lookup("BirdCorrection"))*/
{}


template<class CloudType>
Foam::MSCModel<CloudType>::MSCModel
(
    const MSCModel<CloudType>& mscm
)
:
    CloudSubModelBase<CloudType>(mscm),
    mesh_(mscm.mesh_)/*,
    BirdCorrection_(mscm.BirdCorrection_)*/
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::MSCModel<CloudType>::~MSCModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// template<class CloudType>
// const Foam::Switch& Foam::MSCModel<CloudType>::BirdCorrection() const
// {
//     return BirdCorrection_;
// }


// template<class CloudType>
// Foam::scalar Foam::MSCModel<CloudType>::htc
// (
//     const scalar dp,
//     const scalar Re,
//     const scalar Pr,
//     const scalar kappa,
//     const scalar NCpW
// ) const
// {
//     const scalar Nu = this->Nu(Re, Pr);
// 
//     scalar htc = Nu*kappa/dp;
// 
//     if (BirdCorrection_ && (mag(htc) > rootVSmall) && (mag(NCpW) > rootVSmall))
//     {
//         const scalar phit = min(NCpW/htc, 50);
//         if (phit > 0.001)
//         {
//             htc *= phit/(exp(phit) - 1.0);
//         }
//     }
// 
//     return htc;
// }


template<class CloudType>
void Foam::MSCModel<CloudType>::info(Ostream& os)
{
    os  << "    multi scale coupling applied " << nl;

}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "MSCModelNew.C"

// ************************************************************************* //
