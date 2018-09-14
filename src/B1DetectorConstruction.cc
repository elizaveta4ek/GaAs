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
// $Id: B1DetectorConstruction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
//#include "G4VSensitiveDetector.hh" 

#include "B1mySensitiveDetector.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 10*cm;
  G4double world_sizeZ  = 20*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
 
/*
  //     
  // Shape 1
  //  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  G4ThreeVector pos1 = G4ThreeVector(0, 2*cm, -7*cm);
        
  // Conical section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
  G4double shape1_hz = 3.*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Cons* solidShape1 =    
    new G4Cons("Shape1", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

*/
  //     
  // Shape 2
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_GALLIUM_ARSENIDE");
  //G4ThreeVector pos2 = G4ThreeVector(0, 0*cm, 0*cm);

  
  G4VisAttributes* BoxColor2 = new G4VisAttributes(G4Color(1.0, 0.5, 0.25, 1));

  // Box shape
  //кажный пиксель - отдельный объем
  G4double pX = 55*um;
  G4double pY = 55*um;
  G4double pZ = 1000*um;
  
  //цельный объем
 /* G4double pX = 14*mm;
  G4double pY = 14*mm;
  G4double pZ = 1000*um;*/
 
  G4Box* MySolidDet =
    new G4Box("Shape2",
                    0.5*pX,
                    0.5*pY,
                    0.5*pZ);

  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(MySolidDet,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name

  logicShape2->SetVisAttributes(BoxColor2);
   
  
  //кажный пиксель - отдельный объем
  for (int i = 0; i<256; i++){
      for (int j = 0; j<256; j++){
            G4ThreeVector pos2 = G4ThreeVector(i*55*um, j*55*um, 0);
            new G4PVPlacement(0,                       //no rotation
                            pos2,                    //at position
                            logicShape2,             //its logical volume
                            "Shape2",                //its name
                            logicWorld,                //its mother  volume
                            false,                   //no boolean operation
                            i+256*j,                       //copy number
                            checkOverlaps = 0);          //overlaps checking
      }
          
    }
  
  //цельный объем
 /* G4ThreeVector pos2 = G4ThreeVector(7*mm, 7*mm, 0);
            new G4PVPlacement(0,                       //no rotation
                            pos2,                    //at position
                            logicShape2,             //its logical volume
                            "Shape2",                //its name
                            logicWorld,                //its mother  volume
                            false,                   //no boolean operation
                            0,                       //copy number
                            checkOverlaps = 0);          //overlaps checking
  */
  
  //
  G4VSensitiveDetector *mySD = new B1mySensitiveDetector("mydet");
  G4SDManager::GetSDMpointer()->AddNewDetector(mySD);
  logicShape2->SetSensitiveDetector(mySD);
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;
  
 
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
