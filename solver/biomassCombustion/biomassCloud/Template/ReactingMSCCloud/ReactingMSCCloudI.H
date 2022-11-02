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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
inline Foam::tmp<Foam::fvScalarMatrix> Foam::ReactingMSCCloud<CloudType>::SYi
(
    const label i,
    volScalarField& Yi
)
{
    
    if (!this->rhoSmoothed())
    {
        forAll(this->rhoTrans_, j)
        {
            this->rhoTrans_[j] = this->MSC().smooth(this->rhoTrans_[j]);
        }
        
        this->rhoSmoothed() = true;
    }
    
    return ReactingCloud<CloudType>::SYi(i, Yi);
}


template<class CloudType>
inline Foam::tmp<Foam::DimensionedField<Foam::scalar, Foam::volMesh>>
Foam::ReactingMSCCloud<CloudType>::Srho(const label i)
{
    if (!this->rhoSmoothed())
    {
        forAll(this->rhoTrans_, j)
        {
            this->rhoTrans_[j] = this->MSC().smooth(this->rhoTrans_[j]);
        }
        
        this->rhoSmoothed() = true;
    }

    return ReactingCloud<CloudType>::Srho(i);
}


template<class CloudType>
inline Foam::tmp<Foam::DimensionedField<Foam::scalar, Foam::volMesh>>
Foam::ReactingMSCCloud<CloudType>::Srho()
{
    if (!this->rhoSmoothed())
    {
        forAll(this->rhoTrans_, j)
        {
            this->rhoTrans_[j] = this->MSC().smooth(this->rhoTrans_[j]);
        }
        
        this->rhoSmoothed() = true;
    }

    return ReactingCloud<CloudType>::Srho();
}


template<class CloudType>
inline Foam::tmp<Foam::fvScalarMatrix>
Foam::ReactingMSCCloud<CloudType>::Srho(volScalarField& rho)
{
    if (!this->rhoSmoothed())
    {
        forAll(this->rhoTrans_, j)
        {
            this->rhoTrans_[j] = this->MSC().smooth(this->rhoTrans_[j]);
        }
        
        this->rhoSmoothed() = true;
    }

    return ReactingCloud<CloudType>::Srho(rho);
}


// ************************************************************************* //
