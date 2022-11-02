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
    Foam::kinematicMSCCloud

Description
    Virtual abstract base class for templated KinematicMSCCloud

SourceFiles
    kinematicMSCCloud.C

\*---------------------------------------------------------------------------*/

#ifndef kinematicMSCCloud_H
#define kinematicMSCCloud_H

#include "typeInfo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class kinematicMSCCloud Declaration
\*---------------------------------------------------------------------------*/

class kinematicMSCCloud
{
public:

    //- Runtime type information
    TypeName("kinematicMSCCloud");

    // Constructors

        //- Null constructor
        kinematicMSCCloud();

        //- Disallow default bitwise copy construction
        kinematicMSCCloud(const kinematicMSCCloud&) = delete;


    //- Destructor
    virtual ~kinematicMSCCloud();


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const kinematicMSCCloud&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
