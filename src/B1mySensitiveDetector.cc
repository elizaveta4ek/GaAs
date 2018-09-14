#include "B1mySensitiveDetector.hh"
#include "G4StepPoint.hh" 
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Trajectory.hh"
 
#include "G4ThreeVector.hh"
#include <iomanip> 
#include "SimpleRootWriter.hh"

#include "TH2F.h"

#include <map>
#include <cmath>
#include <set>

#include "TrackingAction.hh"
#include "G4TouchableHandle.hh"

using namespace CLHEP;


std::map<G4String,int> hit;   //контейнер - счетчик частиц


G4bool B1mySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* aHist)
{    
 SimpleRootWriter* RW = SimpleRootWriter::GetPointer();
    
 G4StepPoint* point1 = aStep->GetPreStepPoint();
 G4StepPoint* point2 = aStep->GetPostStepPoint();
 G4Track* track         = aStep->GetTrack();
 G4ThreeVector pos1 = point1->GetPosition();
 G4ThreeVector pos2 = point2->GetPosition();
 G4ThreeVector momentum = track->GetMomentum();
 G4double kinEnergy     = track->GetKineticEnergy();
 G4double EnergyDeposit = aStep->GetTotalEnergyDeposit();
 G4String particleName = track->GetDefinition()->GetParticleName();
 G4double trackLength = track->GetTrackLength();
 
 
 // get copy number of sensitive volume
 G4TouchableHandle theTouchable = point1->GetTouchableHandle();
 G4int DetCopyNo = theTouchable->GetCopyNumber();
 
 
 //если частица покинула текущий чувствительный объем
 if (point2->GetStepStatus() == fGeomBoundary){
    /* G4cout << "Pixel number: " << DetCopyNo << G4endl;
     G4cout << "Parlicle left GaAs volume" << "\n" << G4endl;
     G4cout << "Track length = " << trackLength << "\n" << G4endl;
     G4cout <<  "\n" << G4endl;*/
 }
  //счетчик частиц
 
 hit[particleName]++;


 if (particleName == "gamma"){
	RW->hGammaSpectra[0]->Fill(kinEnergy/keV);
} 

//if (track->GetParentID()>2){ 
 if (particleName == "e-"){
     
     //считаем длину шага в плоскости (x,y)
     G4double StepLen = sqrt((pos2[0]-pos1[0])*(pos2[0]-pos1[0])+(pos2[1]-pos1[1])*(pos2[1]-pos1[1]));
     /*if(RW->EdepTrack/keV>7){*/RW->TrackLength+=StepLen;//}
 
     //считаем потери энергии частицы в чувствительном детекторе     
     RW->EdepTrack+=EnergyDeposit;
     for (int i=0; i<256;  i++){
        for (int j=0; j<256; j++){
            G4int PixNo = i*256 + j;
            if (PixNo == DetCopyNo){
                if(RW->EdepTrack/keV!=0){RW->setDetCopy.insert(DetCopyNo); }
                RW->h2D[1]->Fill(i,j,EnergyDeposit/keV);
            }
        }
     }
 }
// }
 
 
 
 
return true;
}


 
