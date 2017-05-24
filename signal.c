{
  TFile myFile1("baselinesamples2.root"); // Open the file
  TFile myFile2("newCapValues.root");
  TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file
  TTree* myTree2 = (TTree*) myFile2.Get("meanTree"); // Get the tree from the file
  const int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree
  int wf1[32][1024];        // An array of the wf values
  int cidx1[4];             // An array of the cidx values
  float oldval[32][1024][nEntries1];
  float newval[32][1024][nEntries1];
  float capmean[32][1024];
  myTree1->SetBranchAddress("wf",wf1);
  myTree1->SetBranchAddress("cidx",cidx1);
  myTree2->SetBranchAddress("Mean Cap Value",capmean);
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
    }
   }

  }
  float finalCapValues[1024] = {0.0};
  float indexArray[1024];
  for (int i = 0; i<1024; i++){
    finalCapValues[i] = newval[0][i][527];
    indexArray[i] = i+1;
  }
  TGraph *finalHist = new TGraph(1024,indexArray,finalCapValues);
  finalHist->Draw("AC*");
  myFile1.Close(); // Close file
}
