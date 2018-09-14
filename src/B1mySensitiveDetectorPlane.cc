#include "B1mySensitiveDetector.hh"
#include "G4StepPoint.hh" 
#include "G4Step.hh"
#include "G4Track.hh"
 
#include "G4ThreeVector.hh"
#include <iomanip> 
#include "SimpleRootWriter.hh"

#include "TH2F.h"



#include "TrackingAction.hh"

using namespace CLHEP;





G4bool B1mySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* aHist)
{
 char sHistName[100];   
    


return true;
}