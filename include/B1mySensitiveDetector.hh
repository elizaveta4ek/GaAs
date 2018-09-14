#ifndef mysd_hh
#define mysd_hh 1

#include "G4VSensitiveDetector.hh"

class B1mySensitiveDetector : public G4VSensitiveDetector
{
public:

B1mySensitiveDetector(G4String name) : G4VSensitiveDetector(name){};

G4bool ProcessHits(G4Step*, G4TouchableHistory*);

private:
};


#endif
