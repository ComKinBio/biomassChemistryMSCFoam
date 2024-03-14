<div id="top"></div>
<!--
*** README template used
*** https://github.com/othneildrew/Best-README-Template
-->

<!-- PROJECT SHIELDS -->
<!--
*** Markdown "reference style" is used links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->


<!-- PROJECT -->
# biomassChemistryMSCFoam



<!-- PROJECT LOGO -->
The biomassChemistryMSCFoam is an extended solver based on the official "[coalChemistryFoam](https://github.com/OpenFOAM/OpenFOAM-7/tree/master/applications/solvers/lagrangian/coalChemistryFoam)" solver, and our developed solver "[biomassChemistryFoam](https://github.com/ComKinBio/biomassChemistryFoam)". MSC stands for Meso Scale Coupling. It used a better coding structure and design to realize the coupling method in our previous publication [[1]](#1) and [[2]](#2).
<br />
<br />

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![OpenFOAM v7](https://img.shields.io/badge/OpenFOAM-v7-brightgreen.svg)](https://openfoam.org/)
[![License: GPL v3][license-shield]][license-url]

<div align="center">
  <p align="center">
    <a href="https://github.com/ComKinBio/biomassChemistryMSCFoam/issues">Report Bug</a>
    ·
    <a href="https://github.com/ComKinBio/biomassChemistryMSCFoam/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">Features</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#Contributing">Contributing</a></li>
    <li><a href="#Contact">Contact</a></li>
    <li><a href="#Publications">Publications</a></li>
    <li><a href="#Publications using this repo">Publications using this repo</a></li>
  </ol>
</details>



<!-- Features -->
## Features

### About the MSC submodels

### Solver


A single particle case is added as a test and tutorial case for this slover.


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Contributing -->

## Contributing

This repo accepts updating. For example, correcting the coding style to the [OpenFOAM style](https://openfoam.org/dev/coding-style-guide/), adding particle shape submodel to [RTS mechanism](https://openfoamwiki.net/index.php/OpenFOAM_guide/runTimeSelection_mechanism), making submodels of thermally thick particle properties (currently hard coded)... ...

If you have any contribution to this repo, please fork the repo and create a pull request (to dev). You can also simply open an issue with the tag "improvement".

Besides coding, academic discussions through emails are most approciated.



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the [GPLv3 License](https://www.gnu.org/licenses/gpl-3.0.en.html). ([OpenFOAM license control](https://openfoam.org/licence/))

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Corinna Schulze-Netzer - corinna.netzer@ntnu.no

Jingyuan Zhang - jingyuan.zhang@ntnu.no 

Tian Li - tian.li@ntnu.no / tian.li@risefr.no


Research group: [ComKin group at NTNU](https://www.ntnu.edu/comkin/)


<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Publications -->
## Publications

If you want to use biomassChemistryMSCFoam in your research, you should cite the following papers:

### Publications using this repo
* <a id="1">[1]</a> [Zhang J, Li T, Ström H, et al. Grid-independent Eulerian-Lagrangian approaches for simulations of solid fuel particle combustion[J]. Chemical Engineering Journal, 2020, 387: 123964.](https://www.sciencedirect.com/science/article/pii/S1385894719333790)
  
*<a id="2">[2]</a> [Zhang J, Li T, Ström H, et al. A novel coupling method for unresolved CFD-DEM modeling[J]. International Journal of Heat and Mass Transfer, 2023, 203: 123817.](https://www.sciencedirect.com/science/article/pii/S0017931022012856)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ComKinBio/biomassChemistryMSCFoam.svg?style=flat
[contributors-url]: https://github.com/ComKinBio/biomassChemistryMSCFoam/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ComKinBio/biomassChemistryMSCFoam.svg?style=flat
[forks-url]: https://github.com/ComKinBio/biomassChemistryMSCFoam/network/members
[stars-shield]: https://img.shields.io/github/stars/ComKinBio/biomassChemistryMSCFoam.svg?style=flat
[stars-url]: https://github.com/ComKinBio/biomassChemistryMSCFoam/stargazers
[issues-shield]: https://img.shields.io/github/issues/ComKinBio/biomassChemistryMSCFoam.svg?style=flat
[issues-url]: https://github.com/ComKinBio/biomassChemistryMSCFoam/issues
[license-shield]: https://img.shields.io/badge/License-GPLv3-blue.svg
[license-url]: https://www.gnu.org/licenses/gpl-3.0

