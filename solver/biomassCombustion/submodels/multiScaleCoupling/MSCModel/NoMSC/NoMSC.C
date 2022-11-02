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

#include "NoMSC.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
Foam::NoMSC<CloudType>::NoMSC
(
    const dictionary&,
    CloudType& owner
)
:
    MSCModel<CloudType>(owner)
{}


template<class CloudType>
Foam::NoMSC<CloudType>::NoMSC
(
    const NoMSC<CloudType>& mscm
)
:
    MSCModel<CloudType>(mscm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
Foam::NoMSC<CloudType>::~NoMSC()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::NoMSC<CloudType>::sample
(
    const volScalarField& vf
) const
{    
    return same(vf);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::NoMSC<CloudType>::sample
(
    const volVectorField& vf
) const
{
    return same(vf);
}


template<class CloudType>
Foam::tmp<Foam::volScalarField> 
Foam::NoMSC<CloudType>::smooth
(
    const volScalarField& vf
) const
{
Info<<" smooth function called here "<<endl;
    return same(vf);
}



template<class CloudType>
Foam::tmp<Foam::volVectorField> 
Foam::NoMSC<CloudType>::smooth
(
    const volVectorField& vf
) const
{
    return same(vf);
}


template<class CloudType>
Foam::tmp<Foam::volScalarField::Internal> 
Foam::NoMSC<CloudType>::smooth
(
    const volScalarField::Internal& vfi
) const
{
    
Info<<" smooth Internal function called here "<<endl;
    return same(vfi);
}


template<class CloudType>
Foam::tmp<Foam::volVectorField::Internal> 
Foam::NoMSC<CloudType>::smooth
(
    const volVectorField::Internal& vfi
) const
{    
    return same(vfi);
}

template<class CloudType>
template<class Type>
Foam::tmp<Foam::GeometricField<Type, Foam::fvPatchField, Foam::volMesh>> 
Foam::NoMSC<CloudType>::same
(
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    using volFieldType = GeometricField<Type, fvPatchField, volMesh>;
    
    tmp<volFieldType> tvf
    (
        new volFieldType 
        (
            IOobject
            (
                "averagedField",
                this->mesh().time().timeName(),
                this->mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            vf
        )
    );
    
    return tvf;
}
    
template<class CloudType>
template<class Type>
Foam::tmp<Foam::DimensionedField<Type, Foam::volMesh>> 
Foam::NoMSC<CloudType>::same
(
    const DimensionedField<Type, volMesh>& f
) const
{
    using Internal = DimensionedField<Type, volMesh>;
    
    tmp<Internal> tf
    (
        Internal::New
        (
            "averagedInternalField",
            f
        )
    );
    
    
    return tf;
}




// ************************************************************************* //
