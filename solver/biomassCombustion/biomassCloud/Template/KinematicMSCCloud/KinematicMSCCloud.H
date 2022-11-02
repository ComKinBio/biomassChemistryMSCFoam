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
    Foam::KinematicMSCCloud

Description
    Templated base class for multiscale coupling cloud

    - Adds to kinematic cloud
      - multiscale coupling models

SourceFiles
    KinematicMSCCloudI.H
    KinematicMSCCloud.C

\*---------------------------------------------------------------------------*/

#ifndef KinematicMSCCloud_H
#define KinematicMSCCloud_H

#include "KinematicCloud.H"
#include "kinematicMSCCloud.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes

template<class CloudType>
class MSCModel;

/*---------------------------------------------------------------------------*\
                        Class KinematicMSCCloud Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class KinematicMSCCloud
:
    public CloudType,
    public kinematicMSCCloud
{
public:

    // Public Typedefs

        //- Type of cloud this cloud was instantiated for
        typedef CloudType cloudType;

        //- Type of parcel the cloud was instantiated for
        typedef typename CloudType::particleType parcelType;

        //- Convenience typedef for this cloud type
        typedef KinematicMSCCloud<CloudType> kinematicMSCCloudType;


private:

    // Private Data

        //- Cloud copy pointer
        autoPtr<KinematicMSCCloud<CloudType>> cloudCopyPtr_;
        
        
        //- Flag whether the momentum source has been MSCed
        bool USmoothed_;
        
        //- Flag whether the heat source has been MSCed
        bool ESmoothed_;
        
        //- Flag whether the mass source has been MSCed
        bool rhoSmoothed_;


protected:

    // Protected data

        //- Thermo parcel constant properties
        typename parcelType::constantProperties constProps_;


        // References to the cloud sub-models

            //- Meso-scale coupling model
            autoPtr<MSCModel<KinematicMSCCloud<CloudType>>>
                MSCModel_;
                

    // Protected Member Functions

         // Initialisation

            //- Set cloud sub-models
            void setModels();


        // Cloud evolution functions

            //- Reset state of cloud
            void cloudReset(KinematicMSCCloud<CloudType>& c);


public:

    // Constructors

        //- Construct given carrier gas fields
        KinematicMSCCloud
        (
            const word& cloudName,
            const volScalarField& rho,
            const volVectorField& U,
            const volScalarField& mu,
            const dimensionedVector& g,
            bool readFields = true
        );

        //- Copy constructor with new name
        KinematicMSCCloud(KinematicMSCCloud<CloudType>& c, const word& name);

        //- Copy constructor with new name - creates bare cloud
        KinematicMSCCloud
        (
            const fvMesh& mesh,
            const word& name,
            const KinematicMSCCloud<CloudType>& c
        );

        //- Disallow default bitwise copy construction
        KinematicMSCCloud(const KinematicMSCCloud&) = delete;

        //- Construct and return clone based on (this) with new name
        virtual autoPtr<Cloud<parcelType>> clone(const word& name)
        {
            return autoPtr<Cloud<parcelType>>
            (
                new KinematicMSCCloud(*this, name)
            );
        }

        //- Construct and return bare clone based on (this) with new name
        virtual autoPtr<Cloud<parcelType>> cloneBare(const word& name) const
        {
            return autoPtr<Cloud<parcelType>>
            (
                new KinematicMSCCloud(this->mesh(), name, *this)
            );
        }


    //- Destructor
    virtual ~KinematicMSCCloud();


    // Member Functions

        // Access

            //- Return a reference to the cloud copy
            inline const KinematicMSCCloud& cloudCopy() const;
            
            //- Return a reference to rhoSmoothed_ 
            inline const bool& USmoothed() const;
            
            //- Return a reference to rhoSmoothed_ 
            inline const bool& ESmoothed() const;
            
            //- Return a reference to rhoSmoothed_ 
            inline const bool& rhoSmoothed() const;

            //- Return the constant properties
            inline const typename parcelType::constantProperties&
                constProps() const;
                
       
        // Edit
                
            //- Return a reference to rhoSmoothed_ 
            inline bool& USmoothed();
            
            //- Return a reference to rhoSmoothed_ 
            inline bool& ESmoothed();
                
            //- Return a reference to rhoSmoothed_ 
            inline bool& rhoSmoothed();

            //- Return access to the constant properties
            inline typename parcelType::constantProperties& constProps();


            // Sub-models

                //- Return const-access reference to heat transfer model
                inline const MSCModel<KinematicMSCCloud<CloudType>>&
                    MSC() const;
                    
                //- Return reference to heat transfer model
                inline MSCModel<KinematicMSCCloud<CloudType>>&
                    MSC();


            // Sources

                // Momentum

                    //- Return tmp momentum source term
                    inline tmp<fvVectorMatrix> SU(volVectorField& U);
                    
            // Fields
                
                //- Return the particle volume fraction field
                //  Note: for particles belonging to this cloud only
                inline const tmp<volScalarField> theta() const;
                    

        // Cloud evolution functions

            //- Store the current cloud state
            void storeState();

            //- Reset the current cloud to the previously stored state
            void restoreState();
            
            //- Reset the cloud source terms
            void resetSourceTerms();

            //- Evolve the cloud
            void evolve();



        // I-O

            //- Print cloud information
            void info();


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const KinematicMSCCloud&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "KinematicMSCCloudI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "KinematicMSCCloud.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
