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
    Foam::ReactingMSCCloud

Description
    Adds MSC to reacting cloud

SourceFiles
    ReactingMSCCloudI.H

\*---------------------------------------------------------------------------*/

#ifndef ReactingMSCCloud_H
#define ReactingMSCCloud_H

#include "ReactingCloud.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class ReactingMSCCloud Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class ReactingMSCCloud
:
    public ReactingCloud<CloudType>
{
public:

    // Constructors
    using ReactingCloud<CloudType>::ReactingCloud;
    
        //- Disallow default bitwise copy construction
        ReactingMSCCloud(const ReactingMSCCloud&) = delete;

    //- Destructor
    virtual ~ReactingMSCCloud();

        
    // Member Functions

        // Access

            // Sources

                //- Mass

                    //- Return mass source term for specie i - specie eqn
                    inline tmp<fvScalarMatrix> SYi
                    (
                        const label i,
                        volScalarField& Yi
                    );

                    //- Return tmp mass source for field i - fully explicit
                    inline tmp<volScalarField::Internal>
                        Srho(const label i);

                    //- Return tmp total mass source for carrier phase
                    //  - fully explicit
                    inline tmp<volScalarField::Internal> Srho();

                    //- Return total mass source term [kg/m^3/s]
                    inline tmp<fvScalarMatrix> Srho(volScalarField& rho);
                    
                    
    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const ReactingMSCCloud&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "ReactingMSCCloudI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "ReactingMSCCloud.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
