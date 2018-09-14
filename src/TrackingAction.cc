//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \original file electromagnetic/TestEm9/src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
// $Id: TrackingAction.cc 67268 2013-02-13 11:38:40Z ihrivnac $
//

//---------------------------------------------------------------------------
//
// ClassName:   TrackingAction
//
// Description: Implementation file for MC truth.
//
// Author:      V.Ivanchenko 17/03/01
//
// Modified:
//
//----------------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "TrackingAction.hh"
#include "SimpleRootWriter.hh"
#include "B1DetectorConstruction.hh"
#include "G4PVPlacement.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TrackingAction::TrackingAction():
  G4UserTrackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

TrackingAction::~TrackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

std::map<G4String,int> hit1;

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
 G4String particleName = aTrack->GetDefinition()->GetParticleName();

  SimpleRootWriter::GetPointer()->IncHits(particleName);

  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void TrackingAction::PostUserTrackingAction(const G4Track*)
{   
    SimpleRootWriter* RW = SimpleRootWriter::GetPointer();
    //заполнение гистограмм 
    if (RW->EdepTrack/keV!=0 && RW->setDetCopy.size()!=0){
        RW->h2D[0]->Fill(RW->EdepTrack/keV, RW->setDetCopy.size(),1.);
        RW->hParticles[0]->Fill(RW->EdepTrack/keV);
    }
    if (RW->setDetCopy.size()!=0){    
        RW->hParticles[1]->Fill(RW->setDetCopy.size());
        
    }
    RW->WriteEdepTrack();
    RW->ResetEdepTrack();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
