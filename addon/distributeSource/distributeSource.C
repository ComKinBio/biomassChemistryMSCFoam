/*---------------------------------------------------------------------------*\
    888b     d888                                  d8888                   
    8888b   d8888                                 d88888                   
    88888b.d88888                                d88P888                   
    888Y88888P888  .d88b.  888  888  .d88b.     d88P 888 888  888  .d88b.  
    888 Y888P 888 d88""88b 888  888 d8P  Y8b   d88P  888 888  888 d8P  Y8b 
    888  Y8P  888 888  888 Y88  88P 88888888  d88P   888 Y88  88P 88888888 
    888   "   888 Y88..88P  Y8bd8P  Y8b.     d8888888888  Y8bd8P  Y8b.     
    888       888  "Y88P"    Y88P    "Y8888 d88P     888   Y88P    "Y8888  
-------------------------------------------------------------------------------                                                                                                                                                    
License
    This file is part of distributeSource.

    distributeSource is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    distributeSource is distributed in the hope that it will be useful, but 
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with  distributeSource.  If not, see <http://www.gnu.org/licenses/>.
\*---------------------------------------------------------------------------*/

#include "distributeSource/distributeSource.H"

Foam::distributeSource::distributeSource(const fvMesh& mesh, const aveSpace& box)
: 
    regIOobject
    (
        IOobject
        (
            "distributeSource",
            mesh.time().constantPath(),
            mesh
        )
    ),
    manager_(mesh,box),
    mesh_(mesh)
{    
    // Get the local cell volumes 
    const auto& V = mesh.V();
 
    // Get the halo volumes
    if(Pstream::parRun())
        collectData(V,haloCellVolumes_);
    
    totalCellVolume_.resize(V.size(),0);
    
    // Get total cell volumes
    forAll(V,cellID)
    {
        // Average over this cellID
        const compactCellList& localStencilID = manager_.stencilsID()[cellID];       

        for(label localCellID : localStencilID)
        {
            totalCellVolume_[cellID] += V[localCellID];
        }

        
        // check if the cell requires parallel handling:
        if (manager_.hasProcesorContribution(cellID))
        {
            // get processors to look up from
            const labelList procList = manager_.cellToProcMap()[cellID];
            for (auto procI : procList)
            {
                const List<scalar>& haloCellVolumesOfProcessorI = haloCellVolumes_[procI];
                const labelList& haloCellIDList = manager_.haloCellIDLists()[cellID][procI];
                for (label haloCellID : haloCellIDList)
                {
                    totalCellVolume_[cellID] += haloCellVolumesOfProcessorI[haloCellID];
                }
            }
        }
    }
};


bool Foam::distributeSource::writeData(Foam::Ostream& os) const
{
    os << "distributeSource has no output"<<endl;
    return true;
}

