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
    Foam::CollidingMSCCloud

Description
    Adds coolisions to kinematic clouds

SourceFiles
    CollidingMSCCloudI.H
    CollidingMSCCloud.C

\*---------------------------------------------------------------------------*/

#ifndef CollidingMSCCloud_H
#define CollidingMSCCloud_H

#include "CollidingCloud.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class CollidingMSCCloud Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class CollidingMSCCloud
:
    public CollidingCloud<CloudType>
{

public:

    // Constructors
    
        using CollidingCloud<CloudType>::CollidingCloud;

        
    //- Destructor
        virtual ~CollidingMSCCloud();
    
        
    
    // Member Functions
    
        // Cloud evolution functions    
            //- Evolve the cloud
            void evolve();
        
        // I-O

            //- Print cloud information
            void info();
    

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const CollidingMSCCloud&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #include "CollidingMSCCloudI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "CollidingMSCCloud.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
