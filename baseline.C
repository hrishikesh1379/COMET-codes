{
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <map>


  TFile myFile("baselinesamples2.root"); // Open the file
  TTree* myTree = (TTree*) myFile.Get("tree"); // Get the tree from the file

  int nEntries = myTree->GetEntries(); // Get the number of entries in this tree
  int wf[32][1024];        // An array of the wf values
  int cidx[4];       // An array of the cidx values
  int capval[32][1024][10000];
  float baseline[32][1024] = {0.0};

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

  int max[32][1024] = {0};
  int binmax = 0;
  char buffer [8];
  TH1I *h[32][1024];
  // auto canvas1 = new TCanvas("canvas1", "Calibrated Pulse", 1400, 990);
  // canvas1->Divide(4,2);
  for (int l = 0; l < 32; l++){
    for (int m = 0; m < 1024; m++) {
      sprintf(buffer, "h[%d][%d]", l, m);
      h[l][m] = new TH1I(buffer, buffer, 300, 600, 1200);
      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        h[l][m]->Fill(capval[l][m][iEnt]);
      }
      binmax = h[l][m]->GetMaximumBin();
      max[l][m] = h[l][m]->GetXaxis()->GetBinCenter(binmax);
      // if (m<8) {
      //   canvas1->cd(m+1);
      //   h[l][m]->Draw();
      // }
    }
  }
//Create baseline by averaging over 1000 samples.
  for (int l = 0; l < 32; l++) {
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < 10000; iEnt ++) {
        baseline[l][m] += (capval[l][m][iEnt] - max[l][m]);
      }
      baseline[l][m] = (baseline[l][m]/10000);// - max[l][m];
      //baseline[l][m] = capval[l][m][3000] - max[l][m];
    }
  }


  //  gROOT->Reset();
  // Open the file for writing

  TFile myFile1("calibration.root"); // Open the file
  TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file

  int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree
  int wf1[32][1024];        // An array of the wf values
  int cidx1[4];             // An array of the cidx values
  int oldval[32][1024][200];
  int newval[32][1024][200];

  myTree1->SetBranchAddress("wf",wf1);
  myTree1->SetBranchAddress("cidx",cidx1);

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
      newval[l][m][iEnt] = oldval[l][m][iEnt]- max[l][m];
      newval[l][m][iEnt] = newval[l][m][iEnt] - baseline[l][m];
    }
   }

  }

   float x[1024];
   float y[1024];

  auto canvas = new TCanvas("canvas", "Calibrated Pulse", 1400, 990);
  canvas->Divide(8,4);
  TGraph *g[32];

  // for (Int_t i=cidx1[0];i<1024+cidx1[0];i++) {
  //  x[i-cidx1[0]] = i-cidx1[0];
  // }
  for (int j=0; j<32; j++) {
    if (j<8) {
      for (Int_t i=cidx1[0];i<1024+cidx1[0];i++) {
        x[i-cidx1[0]] = i-cidx1[0];
        y[i-cidx1[0]] = newval[j][i%1024][100]; //j: channel, 150: event no
      }
    }
    else if (j<16) {
      for (Int_t i=cidx1[1];i<1024+cidx1[1];i++) {
        x[i-cidx1[1]] = i-cidx1[1];
        y[i-cidx1[1]] = newval[j][i%1024][100]; //j: channel, 150: event no
      }
    }
    else if (j<24) {
      for (Int_t i=cidx1[2];i<1024+cidx1[2];i++) {
        x[i-cidx1[2]] = i-cidx1[2];
        y[i-cidx1[2]] = newval[j][i%1024][100]; //j: channel, 150: event no
      }
    }
    else if (j<32) {
      for (Int_t i=cidx1[3];i<1024+cidx1[3];i++) {
        x[i-cidx1[3]] = i-cidx1[3];
        y[i-cidx1[3]] = newval[j][i%1024][100]; //j: channel, 150: event no
      }
    }
   canvas->cd(j+1);
   g[j] = new TGraph(1024, x, y);
   g[j]->Draw("AC*");
 }


}
