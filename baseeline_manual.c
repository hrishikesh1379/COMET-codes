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
  int capval[32][1024][2000];
  float capmax[32][1024] = {0.0};

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
  for (int l = 0; l < 1; l++) { //Channel
    for (int m = 0; m<1024; m++) { //Capacitor
      std::map <int, int> cap;
      std::map <int, int> cap1;
      //cap = new std::map<int, int>;
      for(int iEnt = 0; iEnt < 2000; iEnt++) {
        if (!cap.count(capval[l][m][iEnt])) { //Create map for one capacitor of a channel
          cap[capval[l][m][iEnt]] = 1;
        }
        else {
          cap[capval[l][m][iEnt]]= cap[capval[l][m][iEnt]] + 1;
        }
      //  cout << l << " " << iEnt << " " << cap[capval[l][m][iEnt]] << endl;
      }
      for(int i=0; i<40;i++){
        cap1[902+5*i] = 0; //Keep tabs
        for(int j=0;j<5;j++){
          cap1[902+5*i] = cap1[902+5*i] + cap[902+5*i+j];
        }
        if (cap1[902+5*i] > max[l][m]) {
          max[l][m] = cap1[902+5*i];
        }
      }
    }
  }


  /*
  for (int l = 0; l < 32; l++){
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        capmean[l][m] += capval[l][m][iEnt];
      }
      capmean[l][m] = capmean[l][m]/nEntries;
    }
  }
  */
/*
  int binmax = 0;
  char buffer [8];
  TH1I *h[32][1024];
  for (int l = 0; l < 32; l++){
    //h[l] = new TH1I[1024];
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        sprintf(buffer, "h[%d][%d]", l, m);
        h[l][m] = new TH1I(buffer, buffer, 400, 0, 1200);
        h[l][m].Fill(capval[l][m][iEnt]);
      }
      binmax = h[l][m].GetMaximumBin();
      capmax[l][m] = h[l][m]->GetXaxis()->GetBinCenter(binmax);
    }
  }*/


  //  gROOT->Reset();
  // Open the file for writing

  TFile myFile1("baselinesamples2.root"); // Open the file
  TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file

  int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree
  int wf1[32][1024];        // An array of the wf values
  int cidx1[4];             // An array of the cidx values
  float oldval[32][1024][2000];
  float newval[32][1024][2000];

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
   for (int l = 0; l < 1; l++){
    for (int m = 0; m < 1024; m++) {
    newval[l][m][iEnt] = oldval[l][m][iEnt] - max[l][m];
    //if(l==0 && iEnt==2) cout<< l << " " << m << " " << iEnt <<" " << oldval[l][m][iEnt] << endl;
    }
   }

  }

   float x[1024];
   float y[1024];

  auto canvas = new TCanvas("canvas", "First canvas", 1000, 800);
  canvas->Divide(8,4);
  TGraph *g[32];


  //for (int j=0; j<16; j++) {
  for (Int_t i=cidx1[0];i<1024+cidx1[0];i++) {
   x[i-cidx1[0]] = i-cidx1[0];
  }
  for (int j=0; j<32; j++) {
   for (Int_t i=cidx1[0];i<1024+cidx1[0];i++) {
    y[i-cidx1[0]] = newval[j][i%1024][1007]; //j: channel, 1007: event no
   }
   canvas->cd(j+1);
   g[j] = new TGraph(1024, x, y);
   g[j]->Draw("AC*");
 }


}
