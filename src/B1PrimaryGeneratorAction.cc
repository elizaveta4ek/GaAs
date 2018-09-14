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
// $Id: B1PrimaryGeneratorAction.cc 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Geantino.hh"

using namespace CLHEP;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0) 
{ G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(1*MeV);
  //fParticleGun->SetParticleDefinition(G4Geantino::Geantino()); 
  //G4double PartEn = 0*eV;
  //fParticleGun->SetParticleEnergy(PartEn);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  /*G4ParticleDefinition* ion;
  G4int i = (int)(2.*G4UniformRand());
  std::cout << "i = " << i << std::endl;
  switch(i){
      case 0: ion = G4IonTable::GetIonTable()->GetIon(31,72,0); break;
      case 1: ion = G4IonTable::GetIonTable()->GetIon(33,76,0); break;
  }
  
  fParticleGun->SetParticleDefinition(ion);
  
  G4double a, b, c;
  G4double n;
  do {
      a = (G4UniformRand()-0.5);
      b = (G4UniformRand()-0.5);
      c = (G4UniformRand()-0.5);
      n = a*a + b*b + c*c; 
  } while (n>1 || n == 0.0);
  
  n = std::sqrt(n);
  a /= n;
  b /= n;
  c /= n;
  
  G4ThreeVector direction(a,b,c);
  
  fParticleGun->SetParticleMomentumDirection(direction);

  G4cout << "x = " << a << ", y = " << b << ", z = " << c << '\n' << G4endl;
    
    
  G4double x0 = 14*mm * (G4UniformRand());
  G4double y0 = 14*mm * (G4UniformRand());
  G4double z0 = 1000*um * (G4UniformRand()-0.5);
  //G4double z0 = 1*cm;*/
  
  G4double x0 = 14*mm * (G4UniformRand());
  G4double y0 = 14*mm * (G4UniformRand());
 // G4double z0 = 1000*um * (G4UniformRand()-0.5);
  G4double z0 = -5*cm;
  
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
