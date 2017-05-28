{
  #include "TTree.h"
  #include "TFile.h"
  #include "TH1F.h"
  #include "TCanvas.h"
  #include<stdlib.h>
  #include<iostream>
  #include<string>

  TFile myFile("baselinesamples2.root"); // Open the file
  TTree* myTree = (TTree*) myFile.Get("tree"); // Get the tree from the file

  int nEntries = myTree->GetEntries(); // Get the number of entries in this tree
  int wf[32][1024];        // An array of the wf values
  int cidx[4];       // An array of the cidx values
  int capval[32][1024][10000];
  float capmean[32][1024] = {0.0};

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

  for (int l = 0; l < 32; l++){
    for (int m = 0; m < 1024; m++) {
      for (int iEnt = 0; iEnt < nEntries; iEnt++) {
        capmean[l][m] += capval[l][m][iEnt];
      }
      capmean[l][m] = capmean[l][m]/nEntries;
    }
  }
  float maxmean[8][50] = {0.0};
  float inpVoltages[50] = {0.0};
  int values[8][1024][100];
  int maxval[8][100] = {0};

  //To create an array of input voltage values.
  //To create an array of input voltage values.
    int wf0[32][1024];        // An array of the wf values
    int cidx0[4];       // An array of the cidx values
    TFile myFile0("149.root"); // Open the file
    TTree* myTree0 = (TTree*) myFile0.Get("tree"); // Get the tree from the file
    inpVoltages[0] = 149;
    const int nEntries0 = myTree0->GetEntries(); // Get the number of entries in this tree

    myTree0->SetBranchAddress("wf",wf0);
    myTree0->SetBranchAddress("cidx",cidx0);

    for (int iEnt = 0; iEnt < nEntries0; iEnt++) { //to extract values from signal waveform
      myTree0->GetEntry(iEnt); // Gets the next entry (filling the linked variables)
      for (int l = 0; l < 8; l++){
      for (int c = cidx0[0], d = 0; c < cidx0[0]+1024; c++){
          values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
          values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
          d++;
        }
      }
    }

    for (int l = 1; l < 6; l++){
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

      int wf1[32][1024];        // An array of the wf values //Here 0->1
      int cidx1[4];       // An array of the cidx values //Here 0->1
      TFile myFile1("150.root"); // Open the file //Here 0->1
      TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[1] = 150; //Here 0->1
      const int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree1->SetBranchAddress("wf",wf1); //Here 0->1
      myTree1->SetBranchAddress("cidx",cidx1); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries1; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree1->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx1[0], d = 0; c < cidx1[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][1] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][1] = maxmean[l][1]/nEntries1; //find the mean of maximas across entries //Here 0->1
        }
  int wf2[32][1024];        // An array of the wf values //Here 0->1
      int cidx2[4];       // An array of the cidx values //Here 0->1
      TFile myFile2("152.root"); // Open the file //Here 0->1
      TTree* myTree2 = (TTree*) myFile2.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[2] = 152; //Here 0->1
      const int nEntries2 = myTree2->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree2->SetBranchAddress("wf",wf2); //Here 0->1
      myTree2->SetBranchAddress("cidx",cidx2); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries2; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree2->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx2[0], d = 0; c < cidx2[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries2; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][2] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][2] = maxmean[l][2]/nEntries2; //find the mean of maximas across entries //Here 0->1
        }
  int wf3[32][1024];        // An array of the wf values //Here 0->1
      int cidx3[4];       // An array of the cidx values //Here 0->1
      TFile myFile3("156.root"); // Open the file //Here 0->1
      TTree* myTree3 = (TTree*) myFile3.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[3] = 156; //Here 0->1
      const int nEntries3 = myTree3->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree3->SetBranchAddress("wf",wf3); //Here 0->1
      myTree3->SetBranchAddress("cidx",cidx3); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries3; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree3->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx3[0], d = 0; c < cidx3[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries3; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][3] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][3] = maxmean[l][3]/nEntries3; //find the mean of maximas across entries //Here 0->1
        }

        int wf4[32][1024];        // An array of the wf values //Here 0->1
      int cidx4[4];       // An array of the cidx values //Here 0->1
      TFile myFile4("160.root"); // Open the file //Here 0->1
      TTree* myTree4 = (TTree*) myFile4.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[4] = 160; //Here 0->1
      const int nEntries4 = myTree4->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree4->SetBranchAddress("wf",wf4); //Here 0->1
      myTree4->SetBranchAddress("cidx",cidx4); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries4; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree4->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx4[0], d = 0; c < cidx4[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries4; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][4] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][4] = maxmean[l][4]/nEntries4; //find the mean of maximas across entries //Here 0->1
        }
        int wf5[32][1024];        // An array of the wf values //Here 0->1
      int cidx5[4];       // An array of the cidx values //Here 0->1
      TFile myFile5("164.root"); // Open the file //Here 0->1
      TTree* myTree5 = (TTree*) myFile5.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[5] = 164; //Here 0->1
      const int nEntries5 = myTree5->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree5->SetBranchAddress("wf",wf5); //Here 0->1
      myTree5->SetBranchAddress("cidx",cidx5); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries5; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree5->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx5[0], d = 0; c < cidx5[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries5; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][5] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][5] = maxmean[l][5]/nEntries5; //find the mean of maximas across entries //Here 0->1
        }
        int wf6[32][1024];        // An array of the wf values //Here 0->1
      int cidx6[4];       // An array of the cidx values //Here 0->1
      TFile myFile6("166.root"); // Open the file //Here 0->1
      TTree* myTree6 = (TTree*) myFile6.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[6] = 166; //Here 0->1
      const int nEntries6 = myTree6->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree6->SetBranchAddress("wf",wf6); //Here 0->1
      myTree6->SetBranchAddress("cidx",cidx6); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries6; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree6->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx6[0], d = 0; c < cidx6[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries6; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][6] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][6] = maxmean[l][6]/nEntries6; //find the mean of maximas across entries //Here 0->1
        }
        int wf7[32][1024];        // An array of the wf values //Here 0->1
      int cidx7[4];       // An array of the cidx values //Here 0->1
      TFile myFile7("167.root"); // Open the file //Here 0->1
      TTree* myTree7 = (TTree*) myFile7.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[7] = 167; //Here 0->1
      const int nEntries7 = myTree7->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree7->SetBranchAddress("wf",wf7); //Here 0->1
      myTree7->SetBranchAddress("cidx",cidx7); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries7; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree7->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx7[0], d = 0; c < cidx7[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf7[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries7; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][7] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][7] = maxmean[l][7]/nEntries7; //find the mean of maximas across entries //Here 0->1
        }
        int wf8[32][1024];        // An array of the wf values //Here 0->1
      int cidx8[4];       // An array of the cidx values //Here 0->1
      TFile myFile8("168.root"); // Open the file //Here 0->1
      TTree* myTree8 = (TTree*) myFile8.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[8] = 168; //Here 0->1
      const int nEntries8 = myTree8->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree8->SetBranchAddress("wf",wf8); //Here 0->1
      myTree8->SetBranchAddress("cidx",cidx8); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries8; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree8->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx8[0], d = 0; c < cidx8[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf8[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries8; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][8] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][8] = maxmean[l][8]/nEntries8; //find the mean of maximas across entries //Here 0->1
        }
        int wf9[32][1024];        // An array of the wf values //Here 0->1
      int cidx9[4];       // An array of the cidx values //Here 0->1
      TFile myFile9("169.root"); // Open the file //Here 0->1
      TTree* myTree9 = (TTree*) myFile9.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[9] = 169; //Here 0->1
      const int nEntries9 = myTree9->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree9->SetBranchAddress("wf",wf9); //Here 0->1
      myTree9->SetBranchAddress("cidx",cidx9); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries9; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree9->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx9[0], d = 0; c < cidx9[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf9[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries9; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][9] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][9] = maxmean[l][9]/nEntries9; //find the mean of maximas across entries //Here 0->1
        }
        int wf10[32][1024];        // An array of the wf values //Here 0->1
      int cidx10[4];       // An array of the cidx values //Here 0->1
      TFile myFile10("170.root"); // Open the file //Here 0->1
      TTree* myTree10 = (TTree*) myFile10.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[10] = 170; //Here 0->1
      const int nEntries10 = myTree10->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree10->SetBranchAddress("wf",wf10); //Here 0->1
      myTree10->SetBranchAddress("cidx",cidx10); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries10; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree10->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx10[0], d = 0; c < cidx10[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf10[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries10; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][10] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][10] = maxmean[l][10]/nEntries10; //find the mean of maximas across entries //Here 0->1
        }
        int wf11[32][1024];        // An array of the wf values //Here 0->1
      int cidx11[4];       // An array of the cidx values //Here 0->1
      TFile myFile11("171.root"); // Open the file //Here 0->1
      TTree* myTree11 = (TTree*) myFile11.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[11] = 171; //Here 0->1
      const int nEntries11 = myTree11->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree11->SetBranchAddress("wf",wf11); //Here 0->1
      myTree11->SetBranchAddress("cidx",cidx11); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries11; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree11->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx11[0], d = 0; c < cidx11[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf11[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries11; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][11] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][11] = maxmean[l][11]/nEntries11; //find the mean of maximas across entries //Here 0->1
        }
        int wf12[32][1024];        // An array of the wf values //Here 0->1
      int cidx12[4];       // An array of the cidx values //Here 0->1
      TFile myFile12("173.root"); // Open the file //Here 0->1
      TTree* myTree12 = (TTree*) myFile12.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[12] = 173; //Here 0->1
      const int nEntries12 = myTree12->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree12->SetBranchAddress("wf",wf12); //Here 0->1
      myTree12->SetBranchAddress("cidx",cidx12); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries12; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree12->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx12[0], d = 0; c < cidx12[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf12[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries12; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][12] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][12] = maxmean[l][12]/nEntries12; //find the mean of maximas across entries //Here 0->1
        }
  int wf13[32][1024];        // An array of the wf values //Here 0->1
      int cidx13[4];       // An array of the cidx values //Here 0->1
      TFile myFile13("174.root"); // Open the file //Here 0->1
      TTree* myTree13 = (TTree*) myFile13.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[13] = 174; //Here 0->1
      const int nEntries13 = myTree13->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree13->SetBranchAddress("wf",wf13); //Here 0->1
      myTree13->SetBranchAddress("cidx",cidx13); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries13; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree13->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx13[0], d = 0; c < cidx13[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf13[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries13; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][13] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][13] = maxmean[l][13]/nEntries13; //find the mean of maximas across entries //Here 0->1
        }
        int wf14[32][1024];        // An array of the wf values //Here 0->1
      int cidx14[4];       // An array of the cidx values //Here 0->1
      TFile myFile14("175.root"); // Open the file //Here 0->1
      TTree* myTree14 = (TTree*) myFile14.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[14] = 175; //Here 0->1
      const int nEntries14 = myTree14->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree14->SetBranchAddress("wf",wf14); //Here 0->1
      myTree14->SetBranchAddress("cidx",cidx14); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries14; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree14->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx14[0], d = 0; c < cidx14[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf14[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries14; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][14] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][14] = maxmean[l][14]/nEntries14; //find the mean of maximas across entries //Here 0->1
        }
        int wf15[32][1024];        // An array of the wf values //Here 0->1
      int cidx15[4];       // An array of the cidx values //Here 0->1
      TFile myFile15("177.root"); // Open the file //Here 0->1
      TTree* myTree15 = (TTree*) myFile15.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[15] = 177; //Here 0->1
      const int nEntries15 = myTree15->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree15->SetBranchAddress("wf",wf15); //Here 0->1
      myTree15->SetBranchAddress("cidx",cidx15); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries15; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree15->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx15[0], d = 0; c < cidx15[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf15[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries15; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][15] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][15] = maxmean[l][15]/nEntries15; //find the mean of maximas across entries //Here 0->1
        }
        int wf16[32][1024];        // An array of the wf values //Here 0->1
      int cidx16[4];       // An array of the cidx values //Here 0->1
      TFile myFile16("178.root"); // Open the file //Here 0->1
      TTree* myTree16 = (TTree*) myFile16.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[16] = 178; //Here 0->1
      const int nEntries16 = myTree16->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree16->SetBranchAddress("wf",wf16); //Here 0->1
      myTree16->SetBranchAddress("cidx",cidx16); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries16; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree16->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx16[0], d = 0; c < cidx16[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf16[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries16; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][16] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][16] = maxmean[l][16]/nEntries16; //find the mean of maximas across entries //Here 0->1
        }
        int wf17[32][1024];        // An array of the wf values //Here 0->1
      int cidx17[4];       // An array of the cidx values //Here 0->1
      TFile myFile17("179.root"); // Open the file //Here 0->1
      TTree* myTree17 = (TTree*) myFile17.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[17] = 179; //Here 0->1
      const int nEntries17 = myTree17->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree17->SetBranchAddress("wf",wf17); //Here 0->1
      myTree17->SetBranchAddress("cidx",cidx17); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries17; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree17->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx17[0], d = 0; c < cidx17[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf17[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries17; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][17] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][17] = maxmean[l][17]/nEntries17; //find the mean of maximas across entries //Here 0->1
        }
        int wf18[32][1024];        // An array of the wf values //Here 0->1
      int cidx18[4];       // An array of the cidx values //Here 0->1
      TFile myFile18("180.root"); // Open the file //Here 0->1
      TTree* myTree18 = (TTree*) myFile18.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[18] = 180; //Here 0->1
      const int nEntries18 = myTree18->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree18->SetBranchAddress("wf",wf18); //Here 0->1
      myTree18->SetBranchAddress("cidx",cidx18); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries18; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree18->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx18[0], d = 0; c < cidx18[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf18[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries18; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][18] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][18] = maxmean[l][18]/nEntries18; //find the mean of maximas across entries //Here 0->1
        }
        int wf19[32][1024];        // An array of the wf values //Here 0->1
      int cidx19[4];       // An array of the cidx values //Here 0->1
      TFile myFile19("181.root"); // Open the file //Here 0->1
      TTree* myTree19 = (TTree*) myFile19.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[19] = 181; //Here 0->1
      const int nEntries19 = myTree19->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree19->SetBranchAddress("wf",wf19); //Here 0->1
      myTree19->SetBranchAddress("cidx",cidx19); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries19; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree19->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx19[0], d = 0; c < cidx19[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf19[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries19; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][19] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][19] = maxmean[l][19]/nEntries19; //find the mean of maximas across entries //Here 0->1
        }
        int wf20[32][1024];        // An array of the wf values //Here 0->1
      int cidx20[4];       // An array of the cidx values //Here 0->1
      TFile myFile20("184.root"); // Open the file //Here 0->1
      TTree* myTree20 = (TTree*) myFile20.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[20] = 184; //Here 0->1
      const int nEntries20 = myTree20->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree20->SetBranchAddress("wf",wf20); //Here 0->1
      myTree20->SetBranchAddress("cidx",cidx20); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries20; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree20->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx20[0], d = 0; c < cidx20[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf20[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries20; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][20] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][20] = maxmean[l][20]/nEntries20; //find the mean of maximas across entries //Here 0->1
        }
        int wf21[32][1024];        // An array of the wf values //Here 0->1
      int cidx21[4];       // An array of the cidx values //Here 0->1
      TFile myFile21("185.root"); // Open the file //Here 0->1
      TTree* myTree21 = (TTree*) myFile21.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[21] = 185; //Here 0->1
      const int nEntries21 = myTree21->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree21->SetBranchAddress("wf",wf21); //Here 0->1
      myTree21->SetBranchAddress("cidx",cidx21); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries21; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree21->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx21[0], d = 0; c < cidx21[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf21[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries21; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][21] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][21] = maxmean[l][21]/nEntries21; //find the mean of maximas across entries //Here 0->1
        }
        int wf22[32][1024];        // An array of the wf values //Here 0->1
      int cidx22[4];       // An array of the cidx values //Here 0->1
      TFile myFile22("187.root"); // Open the file //Here 0->1
      TTree* myTree22 = (TTree*) myFile22.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[22] = 187; //Here 0->1
      const int nEntries22 = myTree22->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree22->SetBranchAddress("wf",wf22); //Here 0->1
      myTree22->SetBranchAddress("cidx",cidx22); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries22; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree22->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx22[0], d = 0; c < cidx22[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf22[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries22; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][22] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][22] = maxmean[l][22]/nEntries22; //find the mean of maximas across entries //Here 0->1
        }
        int wf23[32][1024];        // An array of the wf values //Here 0->1
      int cidx23[4];       // An array of the cidx values //Here 0->1
      TFile myFile23("188.root"); // Open the file //Here 0->1
      TTree* myTree23 = (TTree*) myFile23.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[23] = 188; //Here 0->1
      const int nEntries23 = myTree23->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree23->SetBranchAddress("wf",wf23); //Here 0->1
      myTree23->SetBranchAddress("cidx",cidx23); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries23; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree23->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx23[0], d = 0; c < cidx23[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf23[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries23; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][23] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][23] = maxmean[l][23]/nEntries23; //find the mean of maximas across entries //Here 0->1
        }
        int wf24[32][1024];        // An array of the wf values //Here 0->1
      int cidx24[4];       // An array of the cidx values //Here 0->1
      TFile myFile24("190.root"); // Open the file //Here 0->1
      TTree* myTree24 = (TTree*) myFile24.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[24] = 190; //Here 0->1
      const int nEntries24 = myTree24->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree24->SetBranchAddress("wf",wf24); //Here 0->1
      myTree24->SetBranchAddress("cidx",cidx24); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries24; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree24->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx24[0], d = 0; c < cidx24[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf24[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries24; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][24] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][24] = maxmean[l][24]/nEntries24; //find the mean of maximas across entries //Here 0->1
        }
        int wf25[32][1024];        // An array of the wf values //Here 0->1
      int cidx25[4];       // An array of the cidx values //Here 0->1
      TFile myFile25("191.root"); // Open the file //Here 0->1
      TTree* myTree25 = (TTree*) myFile25.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[25] = 191; //Here 0->1
      const int nEntries25 = myTree25->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree25->SetBranchAddress("wf",wf25); //Here 0->1
      myTree25->SetBranchAddress("cidx",cidx25); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries25; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree25->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx25[0], d = 0; c < cidx25[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf25[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries25; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][25] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][25] = maxmean[l][25]/nEntries25; //find the mean of maximas across entries //Here 0->1
        }
        int wf26[32][1024];        // An array of the wf values //Here 0->1
      int cidx26[4];       // An array of the cidx values //Here 0->1
      TFile myFile26("192.root"); // Open the file //Here 0->1
      TTree* myTree26 = (TTree*) myFile26.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[26] = 192; //Here 0->1
      const int nEntries26 = myTree26->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree26->SetBranchAddress("wf",wf26); //Here 0->1
      myTree26->SetBranchAddress("cidx",cidx26); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries26; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree26->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx26[0], d = 0; c < cidx26[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf26[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries26; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][26] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][26] = maxmean[l][26]/nEntries26; //find the mean of maximas across entries //Here 0->1
      }

      int wf27[32][1024];        // An array of the wf values //Here 0->1
      int cidx27[4];       // An array of the cidx values //Here 0->1
      TFile myFile27("193.root"); // Open the file //Here 0->1
      TTree* myTree27 = (TTree*) myFile27.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[27] = 193; //Here 0->1
      const int nEntries27 = myTree27->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree27->SetBranchAddress("wf",wf27); //Here 0->1
      myTree27->SetBranchAddress("cidx",cidx27); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries27; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree27->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx27[0], d = 0; c < cidx27[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf27[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries27; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][27] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][27] = maxmean[l][27]/nEntries27; //find the mean of maximas across entries //Here 0->1
      }

      int wf28[32][1024];        // An array of the wf values //Here 0->1
      int cidx28[4];       // An array of the cidx values //Here 0->1
      TFile myFile28("195.root"); // Open the file //Here 0->1
      TTree* myTree28 = (TTree*) myFile28.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[28] = 195; //Here 0->1
      const int nEntries28 = myTree28->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree28->SetBranchAddress("wf",wf28); //Here 0->1
      myTree28->SetBranchAddress("cidx",cidx28); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries28; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree28->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx28[0], d = 0; c < cidx28[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf28[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries28; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][28] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][28] = maxmean[l][28]/nEntries28; //find the mean of maximas across entries //Here 0->1
      }

      int wf29[32][1024];        // An array of the wf values //Here 0->1
      int cidx29[4];       // An array of the cidx values //Here 0->1
      TFile myFile29("197.root"); // Open the file //Here 0->1
      TTree* myTree29 = (TTree*) myFile29.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[29] = 197; //Here 0->1
      const int nEntries29 = myTree29->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree29->SetBranchAddress("wf",wf29); //Here 0->1
      myTree29->SetBranchAddress("cidx",cidx29); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries29; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree29->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx29[0], d = 0; c < cidx29[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf29[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries29; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][29] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][29] = maxmean[l][29]/nEntries29; //find the mean of maximas across entries //Here 0->1
      }

      int wf30[32][1024];        // An array of the wf values //Here 0->1
      int cidx30[4];       // An array of the cidx values //Here 0->1
      TFile myFile30("201.root"); // Open the file //Here 0->1
      TTree* myTree30 = (TTree*) myFile30.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[30] = 201; //Here 0->1
      const int nEntries30 = myTree30->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree30->SetBranchAddress("wf",wf30); //Here 0->1
      myTree30->SetBranchAddress("cidx",cidx30); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries30; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree30->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx30[0], d = 0; c < cidx30[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf30[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries30; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][30] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][30] = maxmean[l][30]/nEntries30; //find the mean of maximas across entries //Here 0->1
      }

      int wf31[32][1024];        // An array of the wf values //Here 0->1
      int cidx31[4];       // An array of the cidx values //Here 0->1
      TFile myFile31("203.root"); // Open the file //Here 0->1
      TTree* myTree31 = (TTree*) myFile31.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[31] = 203; //Here 0->1
      const int nEntries31 = myTree31->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree31->SetBranchAddress("wf",wf31); //Here 0->1
      myTree31->SetBranchAddress("cidx",cidx31); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries31; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree31->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx31[0], d = 0; c < cidx31[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf31[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries31; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][31] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][31] = maxmean[l][31]/nEntries31; //find the mean of maximas across entries //Here 0->1
      }

      int wf32[32][1024];        // An array of the wf values //Here 0->1
      int cidx32[4];       // An array of the cidx values //Here 0->1
      TFile myFile32("204.root"); // Open the file //Here 0->1
      TTree* myTree32 = (TTree*) myFile32.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[32] = 204; //Here 0->1
      const int nEntries32 = myTree32->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree32->SetBranchAddress("wf",wf32); //Here 0->1
      myTree32->SetBranchAddress("cidx",cidx32); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries32; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree32->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx32[0], d = 0; c < cidx32[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf32[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries32; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][32] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][32] = maxmean[l][32]/nEntries32; //find the mean of maximas across entries //Here 0->1
      }

      int wf33[32][1024];        // An array of the wf values //Here 0->1
      int cidx33[4];       // An array of the cidx values //Here 0->1
      TFile myFile33("205.root"); // Open the file //Here 0->1
      TTree* myTree33 = (TTree*) myFile33.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[33] = 205; //Here 0->1
      const int nEntries33 = myTree33->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree33->SetBranchAddress("wf",wf33); //Here 0->1
      myTree33->SetBranchAddress("cidx",cidx33); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries33; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree33->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx33[0], d = 0; c < cidx33[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf33[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries33; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][33] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][33] = maxmean[l][33]/nEntries33; //find the mean of maximas across entries //Here 0->1
      }

      int wf34[32][1024];        // An array of the wf values //Here 0->1
      int cidx34[4];       // An array of the cidx values //Here 0->1
      TFile myFile34("207.root"); // Open the file //Here 0->1
      TTree* myTree34 = (TTree*) myFile34.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[34] = 207; //Here 0->1
      const int nEntries34 = myTree34->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree34->SetBranchAddress("wf",wf34); //Here 0->1
      myTree34->SetBranchAddress("cidx",cidx34); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries34; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree34->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx34[0], d = 0; c < cidx34[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf34[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries34; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][34] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][34] = maxmean[l][34]/nEntries34; //find the mean of maximas across entries //Here 0->1
      }

      int wf35[32][1024];        // An array of the wf values //Here 0->1
      int cidx35[4];       // An array of the cidx values //Here 0->1
      TFile myFile35("208.root"); // Open the file //Here 0->1
      TTree* myTree35 = (TTree*) myFile35.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[35] = 208; //Here 0->1
      const int nEntries35 = myTree35->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree35->SetBranchAddress("wf",wf35); //Here 0->1
      myTree35->SetBranchAddress("cidx",cidx35); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries35; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree35->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx35[0], d = 0; c < cidx35[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf35[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries35; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][35] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][35] = maxmean[l][35]/nEntries35; //find the mean of maximas across entries //Here 0->1
      }

      int wf36[32][1024];        // An array of the wf values //Here 0->1
      int cidx36[4];       // An array of the cidx values //Here 0->1
      TFile myFile36("209.root"); // Open the file //Here 0->1
      TTree* myTree36 = (TTree*) myFile36.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[36] = 209; //Here 0->1
      const int nEntries36 = myTree36->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree36->SetBranchAddress("wf",wf36); //Here 0->1
      myTree36->SetBranchAddress("cidx",cidx36); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries36; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree36->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx36[0], d = 0; c < cidx36[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf36[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries36; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][36] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][36] = maxmean[l][36]/nEntries36; //find the mean of maximas across entries //Here 0->1
      }

      int wf37[32][1024];        // An array of the wf values //Here 0->1
      int cidx37[4];       // An array of the cidx values //Here 0->1
      TFile myFile37("211.root"); // Open the file //Here 0->1
      TTree* myTree37 = (TTree*) myFile37.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[37] = 211; //Here 0->1
      const int nEntries37 = myTree37->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree37->SetBranchAddress("wf",wf37); //Here 0->1
      myTree37->SetBranchAddress("cidx",cidx37); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries37; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree37->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx37[0], d = 0; c < cidx37[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf37[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries37; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][37] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][37] = maxmean[l][37]/nEntries37; //find the mean of maximas across entries //Here 0->1
      }

      int wf38[32][1024];        // An array of the wf values //Here 0->1
      int cidx38[4];       // An array of the cidx values //Here 0->1
      TFile myFile38("214.root"); // Open the file //Here 0->1
      TTree* myTree38 = (TTree*) myFile38.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[38] = 214; //Here 0->1
      const int nEntries38 = myTree38->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree38->SetBranchAddress("wf",wf38); //Here 0->1
      myTree38->SetBranchAddress("cidx",cidx38); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries38; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree38->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx38[0], d = 0; c < cidx38[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf38[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries38; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][38] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][38] = maxmean[l][38]/nEntries38; //find the mean of maximas across entries //Here 0->1
      }

      int wf39[32][1024];        // An array of the wf values //Here 0->1
      int cidx39[4];       // An array of the cidx values //Here 0->1
      TFile myFile39("215.root"); // Open the file //Here 0->1
      TTree* myTree39 = (TTree*) myFile39.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[39] = 215; //Here 0->1
      const int nEntries39 = myTree39->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree39->SetBranchAddress("wf",wf39); //Here 0->1
      myTree39->SetBranchAddress("cidx",cidx39); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries39; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree39->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx39[0], d = 0; c < cidx39[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf39[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries39; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][39] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][39] = maxmean[l][39]/nEntries39; //find the mean of maximas across entries //Here 0->1
      }

      int wf40[32][1024];        // An array of the wf values //Here 0->1
      int cidx40[4];       // An array of the cidx values //Here 0->1
      TFile myFile40("216.root"); // Open the file //Here 0->1
      TTree* myTree40 = (TTree*) myFile40.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[40] = 216; //Here 0->1
      const int nEntries40 = myTree40->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree40->SetBranchAddress("wf",wf40); //Here 0->1
      myTree40->SetBranchAddress("cidx",cidx40); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries40; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree40->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx40[0], d = 0; c < cidx40[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf40[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries40; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][40] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][40] = maxmean[l][40]/nEntries40; //find the mean of maximas across entries //Here 0->1
      }

      int wf41[32][1024];        // An array of the wf values //Here 0->1
      int cidx41[4];       // An array of the cidx values //Here 0->1
      TFile myFile41("218.root"); // Open the file //Here 0->1
      TTree* myTree41 = (TTree*) myFile41.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[41] = 218; //Here 0->1
      const int nEntries41 = myTree41->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree41->SetBranchAddress("wf",wf41); //Here 0->1
      myTree41->SetBranchAddress("cidx",cidx41); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries41; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree41->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx41[0], d = 0; c < cidx41[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf41[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries41; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][41] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][41] = maxmean[l][41]/nEntries41; //find the mean of maximas across entries //Here 0->1
      }

      int wf42[32][1024];        // An array of the wf values //Here 0->1
      int cidx42[4];       // An array of the cidx values //Here 0->1
      TFile myFile42("219.root"); // Open the file //Here 0->1
      TTree* myTree42 = (TTree*) myFile42.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[42] = 219; //Here 0->1
      const int nEntries42 = myTree42->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree42->SetBranchAddress("wf",wf42); //Here 0->1
      myTree42->SetBranchAddress("cidx",cidx42); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries42; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree42->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx42[0], d = 0; c < cidx42[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf42[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries42; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][42] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][42] = maxmean[l][42]/nEntries42; //find the mean of maximas across entries //Here 0->1
      }

      int wf43[32][1024];        // An array of the wf values //Here 0->1
      int cidx43[4];       // An array of the cidx values //Here 0->1
      TFile myFile43("220.root"); // Open the file //Here 0->1
      TTree* myTree43 = (TTree*) myFile43.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[43] = 220; //Here 0->1
      const int nEntries43 = myTree43->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree43->SetBranchAddress("wf",wf43); //Here 0->1
      myTree43->SetBranchAddress("cidx",cidx43); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries43; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree43->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx43[0], d = 0; c < cidx43[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf43[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries43; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][43] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][43] = maxmean[l][43]/nEntries43; //find the mean of maximas across entries //Here 0->1
      }

      int wf44[32][1024];        // An array of the wf values //Here 0->1
      int cidx44[4];       // An array of the cidx values //Here 0->1
      TFile myFile44("224.root"); // Open the file //Here 0->1
      TTree* myTree44 = (TTree*) myFile44.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[44] = 224; //Here 0->1
      const int nEntries44 = myTree44->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree44->SetBranchAddress("wf",wf44); //Here 0->1
      myTree44->SetBranchAddress("cidx",cidx44); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries44; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree44->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx44[0], d = 0; c < cidx44[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf44[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries44; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][44] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][44] = maxmean[l][44]/nEntries44; //find the mean of maximas across entries //Here 0->1
      }

      int wf45[32][1024];        // An array of the wf values //Here 0->1
      int cidx45[4];       // An array of the cidx values //Here 0->1
      TFile myFile45("225.root"); // Open the file //Here 0->1
      TTree* myTree45 = (TTree*) myFile45.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[45] = 225; //Here 0->1
      const int nEntries45 = myTree45->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree45->SetBranchAddress("wf",wf45); //Here 0->1
      myTree45->SetBranchAddress("cidx",cidx45); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries45; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree45->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx45[0], d = 0; c < cidx45[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf45[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries45; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][45] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][45] = maxmean[l][45]/nEntries45; //find the mean of maximas across entries //Here 0->1
      }

      int wf46[32][1024];        // An array of the wf values //Here 0->1
      int cidx46[4];       // An array of the cidx values //Here 0->1
      TFile myFile46("226.root"); // Open the file //Here 0->1
      TTree* myTree46 = (TTree*) myFile46.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[46] = 226; //Here 0->1
      const int nEntries46 = myTree46->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree46->SetBranchAddress("wf",wf46); //Here 0->1
      myTree46->SetBranchAddress("cidx",cidx46); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries46; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree46->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx46[0], d = 0; c < cidx46[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf46[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries46; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][46] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][46] = maxmean[l][46]/nEntries46; //find the mean of maximas across entries //Here 0->1
      }

      int wf47[32][1024];        // An array of the wf values //Here 0->1
      int cidx47[4];       // An array of the cidx values //Here 0->1
      TFile myFile47("228.root"); // Open the file //Here 0->1
      TTree* myTree47 = (TTree*) myFile47.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[47] = 228; //Here 0->1
      const int nEntries47 = myTree47->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree47->SetBranchAddress("wf",wf47); //Here 0->1
      myTree47->SetBranchAddress("cidx",cidx47); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries47; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree47->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx47[0], d = 0; c < cidx47[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf47[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries47; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][47] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][47] = maxmean[l][47]/nEntries47; //find the mean of maximas across entries //Here 0->1
      }

      int wf48[32][1024];        // An array of the wf values //Here 0->1
      int cidx48[4];       // An array of the cidx values //Here 0->1
      TFile myFile48("232.root"); // Open the file //Here 0->1
      TTree* myTree48 = (TTree*) myFile48.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[48] = 232; //Here 0->1
      const int nEntries48 = myTree48->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree48->SetBranchAddress("wf",wf48); //Here 0->1
      myTree48->SetBranchAddress("cidx",cidx48); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries48; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree48->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx48[0], d = 0; c < cidx48[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf48[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries48; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][48] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][48] = maxmean[l][48]/nEntries48; //find the mean of maximas across entries //Here 0->1
      }

      int wf49[32][1024];        // An array of the wf values //Here 0->1
      int cidx49[4];       // An array of the cidx values //Here 0->1
      TFile myFile49("237.root"); // Open the file //Here 0->1
      TTree* myTree49 = (TTree*) myFile49.Get("tree"); // Get the tree from the file //Here 0->1
      inpVoltages[49] = 237; //Here 0->1
      const int nEntries49 = myTree49->GetEntries(); // Get the number of entries in this tree //Here 0->1

      myTree49->SetBranchAddress("wf",wf49); //Here 0->1
      myTree49->SetBranchAddress("cidx",cidx49); //Here 0->1

      for (int iEnt = 0; iEnt < nEntries49; iEnt++) { //to extract values from signal waveform //Here 0->1
        myTree49->GetEntry(iEnt); // Gets the next entry (filling the linked variables) //Here 0->1
        for (int l = 0; l < 8; l++){
        for (int c = cidx49[0], d = 0; c < cidx49[0]+1024; c++){ //Here 0->1
            values[l][c%1024][iEnt] = wf49[l][d]; //values extracted from the waveform //Here 0->1
            values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
            d++;
          }
        }
      }

      for (int l = 1; l < 6; l++){
        for (int iEnt = 0; iEnt < nEntries49; iEnt++) {
          for (int m = 0; m < 1024; m++){
            if (values[l][m][iEnt] > maxval[l][iEnt]){
              maxval[l][iEnt] = values[l][m][iEnt]; //Find the maximum for a particular entry
            }
          }
          maxmean[l][49] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][49] = maxmean[l][49]/nEntries49; //find the mean of maximas across entries //Here 0->1
      }

      auto canvas = new TCanvas("canvas", "First canvas", 1000, 800);
      canvas->Divide(2,3);
      float maxmeanCh[50] = {0.0};
      //canvas->Divide(2,4);
      TGraph *g[5];
      for (int readingNum=0; readingNum<50; readingNum++) {
          maxmeanCh[readingNum] = maxmean[4][readingNum];
      }
      for (int j=1; j<6; j++) {
      
       //cout<<j<<endl;
       canvas->cd(j);
       g[j-1] = new TGraph(50, inpVoltages, maxmeanCh);
       g[j-1]->Draw("AC*");

      }
}