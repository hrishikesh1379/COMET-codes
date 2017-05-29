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
  float baseline[32][1024] = {0.0};

  // Linking the local variables to the tree branches

  myTree->SetBranchAddress("wf",wf);
  myTree->SetBranchAddress("cidx",cidx);

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
//Create baseline by averaging over 10000 samples.
  for (int l = 0; l < 32; l++) {
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < 10000; iEnt ++) {
        baseline[l][m] += (capval[l][m][iEnt] - max[l][m]);
      }
      baseline[l][m] = (baseline[l][m]/10000);// - max[l][m];
      //baseline[l][m] = capval[l][m][3000] - max[l][m];
    }
  }
  // for (int l = 0; l < 32; l++){
  //   for (int m = 0; m < 1024; m++) {
  //     for (int iEnt = 0; iEnt < nEntries; iEnt++) {
  //       capmean[l][m] += capval[l][m][iEnt];
  //     }
  //     capmean[l][m] = capmean[l][m]/nEntries;
  //   }
  // }

  float tempin[8][7];

  //manually enter the values in the array
  for (int channel = 0; channel < 8; channel++) {
    switch(channel) {
      case 0:
        tempin[0][0] = 22.4209;
        tempin[0][1] = 22.9657;
        tempin[0][2] = 23.5116;
        tempin[0][3] = 24.8536;
        tempin[0][4] = 24.6069;
        tempin[0][5] = 25.7066;
        tempin[0][6] = 26.2582;
        break;
      case 1:
        tempin[1][0] = 22.6932;
        tempin[1][1] = 23.2385;
        tempin[1][2] = 23.5116;
        tempin[1][3] = 24.0587;
        tempin[1][4] = 25.1562;
        tempin[1][5] = 25.9822;
        tempin[1][6] = 26.5344;
        break;
      case 2:
        tempin[2][0] = 22.6932;
        tempin[2][1] = 22.9657;
        tempin[2][2] = 23.5116;
        tempin[2][3] = 24.0587;
        tempin[2][4] = 24.8814;
        tempin[2][5] = 25.7066;
        tempin[2][6] = 26.2582;
        break;
      case 3:
        tempin[3][0] = 21.8772;
        tempin[3][1] = 22.1489;
        tempin[3][2] = 22.9657;
        tempin[3][3] = 23.2385;
        tempin[3][4] = 24.0587;
        tempin[3][5] = 25.1562;
        tempin[3][6] = 26.4312;
        break;
      case 4:
        tempin[4][0] = 22.6932;
        tempin[4][1] = 22.6932;
        tempin[4][2] = 23.5116;
        tempin[4][3] = 23.7850;
        tempin[4][4] = 25.1562;
        tempin[4][5] = 25.7066;
        tempin[4][6] = 26.2582;
        break;
      case 5:
        tempin[5][0] = 22.6932;
        tempin[5][1] = 22.9657;
        tempin[5][2] = 23.7850;
        tempin[5][3] = 24.3327;
        tempin[5][4] = 25.1562;
        tempin[5][5] = 26.2582;
        tempin[5][6] = 26.5344;
        break;
      case 6:
        tempin[6][0] = 22.6932;
        tempin[6][1] = 22.9657;
        tempin[6][2] = 23.5116;
        tempin[6][3] = 24.0587;
        tempin[6][4] = 24.8814;
        tempin[6][5] = 25.7066;
        tempin[6][6] = 26.2582;
        break;
      case 7:
        tempin[7][0] = 21.8772;
        tempin[7][1] = 22.1489;
        tempin[7][2] = 22.9657;
        tempin[7][3] = 23.2385;
        tempin[7][4] = 24.0587;
        tempin[7][5] = 25.4312;
        tempin[7][6] = 26.1562;
        break;
      default: cout<<"Oops!"<<endl;
    }
  }

  float maxmean[32][50] = {0.0};
  float maxmean1[32][50] = {0.0};
  float inpTemp[7] = {0.0};
  int values[32][1024][100];
  int maxval[32][100] = {0};
  int values1[32][1024][100];
  int maxval1[32][100] = {0};

  //To create an array of input voltage values.
  int wf0[32][1024];        // An array of the wf values
  int cidx0[4];       // An array of the cidx values
  TFile myFile0("22.root"); // Open the file
  TTree* myTree0 = (TTree*) myFile0.Get("tree"); // Get the tree from the file
  inpTemp[0] = 22;
  const int nEntries0 = myTree0->GetEntries(); // Get the number of entries in this tree

  myTree0->SetBranchAddress("wf",wf0);
  myTree0->SetBranchAddress("cidx",cidx0);

  for (int iEnt = 0; iEnt < nEntries0; iEnt++) { //to extract values from signal waveform
    myTree0->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx0[0], d = 0; c < cidx0[0]+1024; c++){
        values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx0[1], d = 0; c < cidx0[1]+1024; c++){
      values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx0[2], d = 0; c < cidx0[2]+1024; c++){
      values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx0[3], d = 0; c < cidx0[3]+1024; c++){
      values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries0; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][0] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][0] = maxmean[l][0]/nEntries0; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries0; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][0] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][0] = maxmean1[l][0]/nEntries0; //find the mean of maximas across entries
  }

  int wf1[32][1024];        // An array of the wf values
  int cidx1[4];       // An array of the cidx values
  TFile myFile1("23.root"); // Open the file
  TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file
  inpTemp[1] = 23;
  const int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree

  myTree1->SetBranchAddress("wf",wf1);
  myTree1->SetBranchAddress("cidx",cidx1);

  for (int iEnt = 0; iEnt < nEntries1; iEnt++) { //to extract values from signal waveform
    myTree1->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx1[0], d = 0; c < cidx1[0]+1024; c++){
        values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx1[1], d = 0; c < cidx1[1]+1024; c++){
      values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx1[2], d = 0; c < cidx1[2]+1024; c++){
      values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx1[3], d = 0; c < cidx1[3]+1024; c++){
      values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][1] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][1] = maxmean[l][1]/nEntries1; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][1] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][1] = maxmean1[l][1]/nEntries1; //find the mean of maximas across entries
  }

  int wf2[32][1024];        // An array of the wf values
  int cidx2[4];       // An array of the cidx values
  TFile myFile2("24.root"); // Open the file
  TTree* myTree2 = (TTree*) myFile2.Get("tree"); // Get the tree from the file
  inpTemp[2] = 24;
  const int nEntries2 = myTree2->GetEntries(); // Get the number of entries in this tree

  myTree2->SetBranchAddress("wf",wf2);
  myTree2->SetBranchAddress("cidx",cidx2);

  for (int iEnt = 0; iEnt < nEntries2; iEnt++) { //to extract values from signal waveform
    myTree2->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx2[0], d = 0; c < cidx2[0]+1024; c++){
        values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx2[1], d = 0; c < cidx2[1]+1024; c++){
      values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx2[2], d = 0; c < cidx2[2]+1024; c++){
      values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx2[3], d = 0; c < cidx2[3]+1024; c++){
      values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries2; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][2] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][2] = maxmean[l][2]/nEntries2; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries2; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][2] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][2] = maxmean1[l][2]/nEntries2; //find the mean of maximas across entries
  }

  int wf3[32][1024];        // An array of the wf values
  int cidx3[4];       // An array of the cidx values
  TFile myFile3("25.root"); // Open the file
  TTree* myTree3 = (TTree*) myFile3.Get("tree"); // Get the tree from the file
  inpTemp[3] = 25;
  const int nEntries3 = myTree3->GetEntries(); // Get the number of entries in this tree

  myTree3->SetBranchAddress("wf",wf3);
  myTree3->SetBranchAddress("cidx",cidx3);

  for (int iEnt = 0; iEnt < nEntries3; iEnt++) { //to extract values from signal waveform
    myTree3->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx3[0], d = 0; c < cidx3[0]+1024; c++){
        values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx3[1], d = 0; c < cidx3[1]+1024; c++){
      values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx3[2], d = 0; c < cidx3[2]+1024; c++){
      values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx3[3], d = 0; c < cidx3[3]+1024; c++){
      values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries3; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][3] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][3] = maxmean[l][3]/nEntries3; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries3; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][3] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][3] = maxmean1[l][3]/nEntries3; //find the mean of maximas across entries
  }

  int wf4[32][1024];        // An array of the wf values
  int cidx4[4];       // An array of the cidx values
  TFile myFile4("26.root"); // Open the file
  TTree* myTree4 = (TTree*) myFile4.Get("tree"); // Get the tree from the file
  inpTemp[4] = 26;
  const int nEntries4 = myTree4->GetEntries(); // Get the number of entries in this tree

  myTree4->SetBranchAddress("wf",wf4);
  myTree4->SetBranchAddress("cidx",cidx4);

  for (int iEnt = 0; iEnt < nEntries4; iEnt++) { //to extract values from signal waveform
    myTree4->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx4[0], d = 0; c < cidx4[0]+1024; c++){
        values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx4[1], d = 0; c < cidx4[1]+1024; c++){
      values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx4[2], d = 0; c < cidx4[2]+1024; c++){
      values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx4[3], d = 0; c < cidx4[3]+1024; c++){
      values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries4; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][4] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][4] = maxmean[l][4]/nEntries4; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries4; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][4] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][4] = maxmean1[l][4]/nEntries4; //find the mean of maximas across entries
  }

  int wf5[32][1024];        // An array of the wf values
  int cidx5[4];       // An array of the cidx values
  TFile myFile5("27.root"); // Open the file
  TTree* myTree5 = (TTree*) myFile5.Get("tree"); // Get the tree from the file
  inpTemp[5] = 27;
  const int nEntries5 = myTree5->GetEntries(); // Get the number of entries in this tree

  myTree5->SetBranchAddress("wf",wf5);
  myTree5->SetBranchAddress("cidx",cidx5);

  for (int iEnt = 0; iEnt < nEntries5; iEnt++) { //to extract values from signal waveform
    myTree5->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx5[0], d = 0; c < cidx5[0]+1024; c++){
        values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx5[1], d = 0; c < cidx5[1]+1024; c++){
      values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx5[2], d = 0; c < cidx5[2]+1024; c++){
      values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx5[3], d = 0; c < cidx5[3]+1024; c++){
      values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries5; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][5] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][5] = maxmean[l][5]/nEntries5; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries5; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][5] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][5] = maxmean1[l][5]/nEntries5; //find the mean of maximas across entries
  }

  int wf6[32][1024];        // An array of the wf values
  int cidx6[4];       // An array of the cidx values
  TFile myFile6("28.root"); // Open the file
  TTree* myTree6 = (TTree*) myFile6.Get("tree"); // Get the tree from the file
  inpTemp[6] = 28;
  const int nEntries6 = myTree6->GetEntries(); // Get the number of entries in this tree

  myTree6->SetBranchAddress("wf",wf6);
  myTree6->SetBranchAddress("cidx",cidx6);

  for (int iEnt = 0; iEnt < nEntries6; iEnt++) { //to extract values from signal waveform
    myTree6->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
    for (int l = 0; l < 8; l++){
    for (int c = cidx6[0], d = 0; c < cidx6[0]+1024; c++){
        values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
        values1[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capval[l][c%1024][4000];
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
        d++;
      }
    }

  for (int l = 8; l < 16; l++){
    for (int c = cidx6[1], d = 0; c < cidx6[1]+1024; c++){
      values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 16; l < 24; l++){
    for (int c = cidx6[2], d = 0; c < cidx6[2]+1024; c++){
      values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }

  for (int l = 24; l < 32; l++){
    for (int c = cidx6[3], d = 0; c < cidx6[3]+1024; c++){
      values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
      values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - baseline[l][c%1024]; // removes the offset
      d++;
    }
  }
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries6; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values[l][m][iEnt] > maxval[l][iEnt]){
          maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean[l][6] += maxval[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean[l][6] = maxmean[l][6]/nEntries6; //find the mean of maximas across entries
  }

  for (int l = 0; l < 32; l++){
    for (int iEnt = 0; iEnt < nEntries6; iEnt++) {
      for (int m = 0; m < 1024; m++){
        if (values1[l][m][iEnt] > maxval1[l][iEnt]){
          maxval1[l][iEnt] = values1[l][m][iEnt]; //Find the maximum for a particular entry
        }
      }
      maxmean1[l][6] += maxval1[l][iEnt];
    //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
    }
    maxmean1[l][6] = maxmean1[l][6]/nEntries6; //find the mean of maximas across entries
  }
    auto canvas = new TCanvas("canvas", "Mean of maximum voltages v/s temperature", 1440, 900);
    canvas->Divide(4,2);
    float maxmeanCh[7] = {0.0};
    //float maxmeanCh1[7] = {0.0};
    //canvas->Divide(2,4);
    TGraph *g[8];
    	//int j = 2;
    for (int j=0; j<8; j++) {
      for (int readingNum=0; readingNum<7; readingNum++) {
        maxmeanCh[readingNum] = maxmean[j][readingNum];
        inpTemp[readingNum] = tempin[j][readingNum];
        //maxmeanCh1[readingNum] = maxmean1[j][readingNum];
      }
     //cout<<j<<endl;
      canvas->cd(j+1);
      g[j] = new TGraph(7, inpTemp, maxmeanCh);
      g[j]->Draw("AL*");
  }
}
