/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

Class
    Foam::ThermoMSCCloud

Description
    Adds MSC to Thermo clouds

SourceFiles
    ThermoMSCCloudI.H

\*---------------------------------------------------------------------------*/

#ifndef ThermoMSCCloud_H
#define ThermoMSCCloud_H

#include "ThermoCloud.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                        Class ThermoMSCCloud Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class ThermoMSCCloud
:
    public ThermoCloud<CloudType>
{
public:

    // Constructors
    using ThermoCloud<CloudType>::ThermoCloud;
    
        //- Disallow default bitwise copy construction
        ThermoMSCCloud(const ThermoMSCCloud&) = delete;

        
    //- Destructor
    virtual ~ThermoMSCCloud();



    // Member Functions

        // Access

            // Sources

                // Enthalpy

                    //- Return sensible enthalpy source term [J/kg/m^3/s]
                    inline tmp<fvScalarMatrix> Sh(volScalarField& hs);


                // Radiation - overrides thermoCloud virtual abstract members

// Radiation is not applied to MSC now
//                     //- Return tmp equivalent particulate emission
//                     inline tmp<volScalarField> Ep() const;
// 
//                     //- Return tmp equivalent particulate absorption
//                     inline tmp<volScalarField> ap() const;
// 
//                     //- Return tmp equivalent particulate scattering factor
//                     inline tmp<volScalarField> sigmap() const;


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const ThermoMSCCloud&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "ThermoMSCCloudI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "ThermoMSCCloud.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif

// ************************************************************************* //
