#include "SimpleRootWriter.hh"

SimpleRootWriter* SimpleRootWriter::pInstance=0;

void SimpleRootWriter::Initialize(bool SaveTree){

  char fname[30];
  sprintf(fname,"B1.root");
  file = new TFile(fname,"RECREATE");

  int hidx = 0;
  for (hidx=0; hidx<100; hidx++)
  {
    hGammaSpectra[hidx]=0;
    hParticles[hidx]=0;
    h2D[hidx]=0;
  }

  fSaveTree = SaveTree;
}

void SimpleRootWriter::Fill(){
  if(fSaveTree) tree->Fill();
}

void SimpleRootWriter::Finalize(){
  file->cd();

  int hidx = 0;
  for (hidx=0; hidx<100; hidx++)
  {
    if (hGammaSpectra[hidx]!=0) {hGammaSpectra[hidx]->Sumw2(); hGammaSpectra[hidx]->Write();}
    if (hParticles[hidx]!=0) {hParticles[hidx]->Sumw2(); hParticles[hidx]->Write();}
    if (h2D[hidx]!=0) {h2D[hidx]->Sumw2(); h2D[hidx]->Write();}
  }

  if(fSaveTree && tree!=0) tree->Write();

  file->Close();
}


