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

#include "biomassMSCCloud.H"

#include "makeParcelCloudFunctionObjects.H"

// // Kinematic
// #include "makeParcelForces.H"
// #include "makeParcelDispersionModels.H"
// #include "makeReactingMultiphaseParcelInjectionModels.H" // MP variant
// #include "makeParcelPatchInteractionModels.H"
// #include "makeReactingMultiphaseParcelStochasticCollisionModels.H" // MP variant
// #include "makeReactingParcelSurfaceFilmModels.H" // Reacting variant

// Multi scale coupling
#include "makeMSCModels.H"

// Thermodynamic
#include "makeParcelHeatTransferModels.H"

// Reacting
#include "makeReactingMultiphaseParcelCompositionModels.H" // MP Variant
#include "makeReactingParcelPhaseChangeModels.H"

// Reacting multiphase
#include "makeReactingMultiphaseParcelDevolatilisationModels.H"
#include "makeReactingMultiphaseParcelSurfaceReactionModels.H"

// thermally thick particle model
#include "makeReactingMultiphaseIBMParcelPyrolysisModels.H" // MPIBM Variant
#include "makeReactingMultiphaseIBMParcelCharOxidizationModels.H" // MPIBM Variant

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// makeParcelCloudFunctionObjects(biomassMSCCloud);

// // Kinematic sub-models
// makeParcelForces(biomassCloud);
// makeParcelDispersionModels(biomassCloud);
// makeReactingMultiphaseParcelInjectionModels(biomassCloud);
// makeParcelPatchInteractionModels(biomassCloud);
// makeReactingMultiphaseParcelStochasticCollisionModels
// (
//     biomassCloud
// );
// makeReactingParcelSurfaceFilmModels(biomassCloud);


// MSC sub-models
makeMSCModels(biomassMSCCloud);

// Thermo sub-models
makeParcelHeatTransferModels(biomassMSCCloud);

// Reacting sub-models
makeReactingMultiphaseParcelCompositionModels
(
    biomassMSCCloud
);
makeReactingParcelPhaseChangeModels(biomassMSCCloud);

// Reacting multiphase sub-models
makeReactingMultiphaseParcelDevolatilisationModels
(
    biomassMSCCloud
);
makeReactingMultiphaseParcelSurfaceReactionModels
(
    biomassMSCCloud
);

// thermally thick particle model
makeReactingMultiphaseIBMParcelPyrolysisModels
(
    biomassMSCCloud
);
makeReactingMultiphaseIBMParcelCharOxidizationModels
(
    biomassMSCCloud
);


// ************************************************************************* //
