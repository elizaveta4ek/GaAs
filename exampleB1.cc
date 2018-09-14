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
// $Id: exampleB1.cc 86065 2014-11-07 08:51:15Z gcosmo $
//
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "QGSP_BERT_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"

#include "G4RadioactiveDecayPhysics.hh"

#include "SimpleRootWriter.hh"

#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "TrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
/*  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif
*/
  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new B1DetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
  physicsList->SetVerboseLevel(1);
  physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics());
  //physicsList->SetDefaultCutValue(1.0*mm);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  runManager->SetUserInitialization(new B1ActionInitialization());
 
  // Initialize ROOT
  SimpleRootWriter* RW = SimpleRootWriter::GetPointer();
  RW->Initialize();
  
  RW->hGammaSpectra[0] = new TH1F("hGammaSpectra","Gamma spectra",100,0,5000);
  RW->hParticles[0] = new TH1F("hParticlesDeposit","Particle energy in Detector",100,0,2500);
  RW->hParticles[1] = new TH1F("hClsSize","ClsSize",50,0,50);
  RW->h2D[0] = new TH2F("hEnDepVsClsSize","EnergyDeposit vs ClsSize",100,0,1000,50,0,50);
  RW->h2D[1] = new TH2F("hClsSumEnergy","ClsSumEnergy",256,0,255,256,0,255);
 
  RW->h2D[0]->GetXaxis()->SetTitle("EnergyDeposit, keV");
  RW->h2D[0]->GetYaxis()->SetTitle("ClsSize, pxl");
  RW->h2D[1]->GetXaxis()->SetTitle("PxlX");
  RW->h2D[1]->GetYaxis()->SetTitle("PlxY");
  RW->h2D[1]->GetZaxis()->SetTitle("Energy deposit, keV");
  RW->h2D[1]->GetZaxis()->SetLabelSize(0.024);
  RW->hGammaSpectra[0]->SetOption("hist");
  RW->hGammaSpectra[0]->GetXaxis()->SetTitle("Energy, keV");
  RW->hGammaSpectra[0]->GetYaxis()->SetTitle("Entries");
  RW->hParticles[0]->GetXaxis()->SetTitle("Energy, keV");
  RW->hParticles[0]->GetYaxis()->SetTitle("Entries");
  RW->hParticles[1]->GetXaxis()->SetTitle("Pixels");
  RW->hParticles[1]->GetYaxis()->SetTitle("Entries");
  
  

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Define UI terminal for interactive mode
//  G4UIsession * session = new G4UIterminal(new G4UItcsh);

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

 runManager->Initialize();

  // Process macro or start UI session
  //
 // if ( ! ui ) { 
   //  batch mode
   // G4String command = "/control/execute ";
   // G4String fileName = argv[1];
   // UImanager->ApplyCommand(command+fileName);
  //}
  //else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
 //  session->SessionStart();
    ui->SessionStart();
   
 //   delete session;
    delete ui;
  //}

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

  /// Save images
  char PicName [100];  
    
  TCanvas* cvClsSumEnergy = new TCanvas("cvClsSumEnergy", "e- Energy Deposit in GaAs", 800, 800);
  gStyle->SetOptStat("ne");
  gPad->SetRightMargin(0.2);
  RW->h2D[1]->Draw("colz");
  cvClsSumEnergy->Update();
  sprintf(PicName, "/home/elizaveta/B1/Pictures/ClsSumEnergy.png");
  cvClsSumEnergy->Print(PicName);
  
  TCanvas* cvElectronDeposit = new TCanvas("cvElectronDeposit", "e- Energy Deposit in GaAs", 800, 800);
  gStyle->SetOptStat("neoumr");
  gPad->SetTopMargin(0.12);
  RW->hParticles[0]->Draw();
  cvElectronDeposit->Update();
  sprintf(PicName, "/home/elizaveta/B1/Pictures/ParticleDeposit.png");
  cvElectronDeposit->Print(PicName);
  
  TCanvas* cvClsSize = new TCanvas("cvClsSize", "ClsSize.png", 800, 800);
  gStyle->SetOptStat("neoumr");
  RW->hParticles[1]->Draw();
  cvClsSize->Update();
  sprintf(PicName, "/home/elizaveta/B1/Pictures/ClsSize.png");
  cvClsSize->Print(PicName);
  
  TCanvas* cvSpectra = new TCanvas("pSpectra", "Gamma spectra", 800, 800);
  RW->hGammaSpectra[0]->Draw();
  gPad->SetLeftMargin(0.12);
  cvSpectra->Update();
  sprintf(PicName, "/home/elizaveta/B1/Pictures/Gamma_spectra.png");
  cvSpectra->Print(PicName);
  
  TCanvas* cvEnDep = new TCanvas("cvEnDep", "Gamma spectra", 800, 800);
  RW->h2D[0]->Draw("colZ");
  gPad->SetRightMargin(0.12);
  cvEnDep->Update();
  sprintf(PicName, "/home/elizaveta/B1/Pictures/EnergyDeposit vs ClsSize.png");
  cvEnDep->Print(PicName);


  RW->Finalize();
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
