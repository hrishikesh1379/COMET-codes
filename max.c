{
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"


  TFile myFile("149.root"); // Open the file
  TTree* myTree = (TTree*) myFile.Get("tree"); // Get the tree from the file
  
  int nEntries = myTree->GetEntries(); // Get the number of entries in this tree
  int wf[32][1024];        // An array of the wf values
  int cidx[4];       // An array of the cidx values
  int values[8][1024][nEntries];
  int maxval[8][100] = {0};
  int maxmean[8];

  myTree->SetBranchAddress("wf",        wf);
  myTree->SetBranchAddress("cidx",       cidx);

  for (int iEnt = 0; iEnt < nEntries; iEnt++) {
    myTree->GetEntry(iEnt); // Gets the next entry (filling the linked variables)

    for (int l = 0; l < 8; l++){
	  for (int c = cidx[0], d = 0; c < cidx[0]+1024; c++){
        values[l][c%1024][iEnt] = wf[l][d];
        d++;
      }
    } 
  }

  for (int l = 1; l < 6; l++){
    for (int iEnt = 0; iEnt < nEntries; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]) maxval[l][iEnt] = values[l][m][iEnt];
      }
    cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
  }	

  for (int l = 1; l < 6; l++){

      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        maxmean[l] += maxval[l][iEnt];
      }
      maxmean[l] = maxmean[l]/nEntries;
     cout << l << " " << maxmean[l] << endl;
  } 

}  

