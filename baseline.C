{
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"


  TFile myFile("baselinesamples2.root"); // Open the file
  TTree* myTree = (TTree*) myFile.Get("tree"); // Get the tree from the file
  TFile *newFile = new TFile("newCapValues.root","RECREATE");
  TTree *tree = new TTree("meanTree", "Updated Capacitor Values");
  const int nEntries = myTree->GetEntries(); // Get the number of entries in this tree
  int wf[32][1024];        // An array of the wf values
  int cidx[4];       // An array of the cidx values
  int capval[32][1024][nEntries];
  float capmean[32][1024] = {0.0};

  // Linking the local variables to the tree branches
  myTree->SetBranchAddress("wf",        wf);
  myTree->SetBranchAddress("cidx",       cidx);

  for (int iEnt = 0; iEnt < nEntries; iEnt++) {
    myTree->GetEntry(iEnt); // Gets the next entry (filling the linked variables)

    for (int l = 0; l < 8; l++){
      for (int c = cidx[0], d = 0; c < cidx[0]+1024; c++){
        capval[l][c%1024][iEnt] = wf[l][d];
        d++;
      }
    }

    for (int l = 8; l < 16; l++){
      for (int c = cidx[1], d = 0; c < cidx[1]+1024; c++){
        capval[l][c%1024][iEnt] = wf[l][d];
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx[2], d = 0; c < cidx[2]+1024; c++){
        capval[l][c%1024][iEnt] = wf[l][d];
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx[3], d = 0; c < cidx[3]+1024; c++){
        capval[l][c%1024][iEnt] = wf[l][d];
        d++;
      }
    }
  }
  tree->Branch("Mean Cap Value", &capmean, "capmean[32][1024]/F");
  for (int l = 0; l < 32; l++){
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        capmean[l][m] += capval[l][m][iEnt];
      }
      capmean[l][m] = capmean[l][m]/nEntries;
      tree->Fill();
    }
  }
  tree->Write();
  newFile->Close();

  myFile.Close(); // Close file */
  TFile f("newCapValues.root");
   if (f.IsZombie()) {
      cout << "Error opening file" << endl;
      exit(-1);
   }
  f.Close();
}
