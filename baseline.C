{
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"


  TFile myFile("baselinesamples2.root"); // Open the file
  TTree* myTree = (TTree*) myFile.Get("tree"); // Get the tree from the file

  int nEntries = myTree->GetEntries(); // Get the number of entries in this tree
  int wf[32][1024];        // An array of the wf values
  int cidx[4];       // An array of the cidx values
  int capval[32][1024][10000];
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

  for (int l = 0; l < 32; l++){
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        capmean[l][m] += capval[l][m][iEnt];
      }
      capmean[l][m] = capmean[l][m]/nEntries;
    }
  }


  //  gROOT->Reset();
  // Open the file for writing

  TFile myFile1("baselinesamples2.root"); // Open the file
  TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file

  int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree
  int wf1[32][1024];        // An array of the wf values
  int cidx1[4];             // An array of the cidx values
  float oldval[32][1024][10000];
  float newval[32][1024][10000];
  float newvalf[32][1024];

  myTree1->SetBranchAddress("wf",        wf1);
  //myTree1->SetBranchAddress("event",        event);
  myTree1->SetBranchAddress("cidx",       cidx1);

  for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
    myTree1->GetEntry(iEnt); // Gets the next entry (filling the linked variables)


    for (int l = 0; l < 8; l++){
      for (int c = cidx1[0], d = 0; c < cidx1[0]+1024; c++){
        oldval[l][c%1024][iEnt] = wf1[l][d];
        d++;
      }
    }

    for (int l = 8; l < 16; l++){
      for (int c = cidx1[1], d = 0; c < cidx1[1]+1024; c++){
        oldval[l][c%1024][iEnt] = wf1[l][d];
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx1[2], d = 0; c < cidx1[2]+1024; c++){
        oldval[l][c%1024][iEnt] = wf1[l][d];
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx1[3], d = 0; c < cidx1[3]+1024; c++){
        oldval[l][c%1024][iEnt] = wf1[l][d];
        d++;
      }
    }
   for (int l = 0; l < 32; l++){
    for (int m = 0; m < 1024; m++) {
    newval[l][m][iEnt] = oldval[l][m][iEnt] - capmean[l][m];
    //if(l==0 && iEnt==2) cout<< l << " " << m << " " << iEnt <<" " << oldval[l][m][iEnt] << endl;
    }
   }

  }


   float x[1024];
   float y[1024];

  auto canvas = new TCanvas("canvas", "First canvas", 1000, 800);
  canvas->Divide(2,4);
  TGraph *g[16];

  //for (int j=0; j<16; j++) {
  for (Int_t i=cidx1[0];i<1024+cidx1[0];i++) {
   x[i-cidx1[0]] = i-cidx1[0];
  }
  for (int j=0; j<8; j++) {
   for (Int_t i=cidx1[0];i<1024+cidx1[0];i++) {
    y[i-cidx1[0]] = newval[j][i%1024][1007]; //j: channel, 1007: event no
   }

   //cout<<j<<endl;
   canvas->cd(j+1);
   g[j] = new TGraph(1024, x, y);
   g[j]->Draw("AC*");

}



/*

  myTree1->Branch("newvalues", &newvalf, "newvalues/F");

  for (Int_t i=0; i < nEntries1; i++) {
    for (int l = 0; l < 32; l++){
      for (int m = 0; m < 1024; m++) {
      newvalf[l][m] = newval[l][m][i];
      }
    }
      // Fills tree:
    myTree1->Fill();
  }

  myTree1->Draw("newvalf");


  myFile.Close(); // Close file
  myFile1.Close(); // Close file */
}
