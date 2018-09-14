#ifndef SimpleRootWriter_H
#define SimpleRootWriter_H 1

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TFile.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <set>
using namespace std;

class SimpleRootWriter{
  public:
    void ResetEdepTrack() {EdepTrack=0;TrackLength=0;setDetCopy.clear();}  
    void WriteEdepTrack() {
     /* cout << '\n'<< endl;  
      cout << "Total energy deposit in detector:" << EdepTrack*1000 << " keV" << endl;
      cout << "Track Length (x,y) plane:" << TrackLength*1000 << " um" <<endl;
      cout << "Number of pixels (from trajectory): " << ceil(TrackLength/0.055) << endl;
      
      cout << "Number of pixels: " << setDetCopy.size() << endl;
      for (int i : setDetCopy){
         cout << "Pixel number: " << i << endl;    
                  }
      cout << '\n'<< endl;*/
    }
    
    void Initialize(bool SaveTree=false);	
    void Fill();		// store an event
    void Finalize();	// write tree to a file
    static SimpleRootWriter* GetPointer(){
      if(pInstance==0) pInstance = new SimpleRootWriter();
      return pInstance;
    };
    void IncHits(string id) { hits[id] += 1;} 
    void ResetHits() {hits.clear();}
    void WriteHits() {
      cout << '\n'<< endl;  
      cout << "Number of particles (1): \n";
      for (map<string,int>::iterator it=hits.begin(); it!=hits.end(); ++it)
      cout << it->first << " => " << it->second << endl;
            ResetHits();
      cout << '\n'<< endl;
   }

  private:
    SimpleRootWriter(){fSaveTree = false;};	// empty constructor
    static SimpleRootWriter* pInstance;         //для подсчета появившихся частиц

    bool fSaveTree;

  public:

    TH1F*  hGammaSpectra[100];
    TH2F*  h2D[100];
    TH1F*  hParticles[100];
    TProfile* p1[100];
     
    TTree* tree;
    double EdepTrack;  //суммарная энергия, потерянная частицей в детекторе
    double TrackLength; //длина трека в плоскости (x,y) {sqrt([x2-x1]^2*[y2-y1]^2)}
    set<int> setDetCopy; //контейнер с номерами пикселей для каждого трека

  private:
    TFile* file;
    map<string,int> hits; //контейнер со списком всех появившихся частиц

};

#endif
