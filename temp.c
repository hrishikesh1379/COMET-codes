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

  int tempin[8][7];

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
  float inpTemp[7] = {0.0};
  int values[32][1024][100];
  int maxval[32][100] = {0};

  //To create an array of input voltage values.
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
          values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
          d++;
        }
      }

    for (int l = 8; l < 16; l++){
      for (int c = cidx[1], d = 0; c < cidx[1]+1024; c++){
        values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx[2], d = 0; c < cidx[2]+1024; c++){
        values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx[3], d = 0; c < cidx[3]+1024; c++){
        values[l][c%1024][iEnt] = wf0[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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

      int wf1[32][1024];        // An array of the wf values //Here 0->1
      int cidx1[4];       // An array of the cidx values //Here 0->1
      TFile myFile1("23.root"); // Open the file //Here 0->1
      TTree* myTree1 = (TTree*) myFile1.Get("tree"); // Get the tree from the file //Here 0->1
      inpTemp[1] = 23; //Here 0->1
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


    for (int l = 8; l < 16; l++){
      for (int c = cidx1[1], d = 0; c < cidx1[1]+1024; c++){
        values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx1[2], d = 0; c < cidx1[2]+1024; c++){
        values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx1[3], d = 0; c < cidx1[3]+1024; c++){
        values[l][c%1024][iEnt] = wf1[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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
          maxmean[l][1] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][1] = maxmean[l][1]/nEntries1; //find the mean of maximas across entries //Here 0->1
        }

  	  int wf2[32][1024];        // An array of the wf values //Here 0->1
      int cidx2[4];       // An array of the cidx values //Here 0->1
      TFile myFile2("24.root"); // Open the file //Here 0->1
      TTree* myTree2 = (TTree*) myFile2.Get("tree"); // Get the tree from the file //Here 0->1
      inpTemp[2] = 24; //Here 0->1
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
    for (int l = 8; l < 16; l++){
      for (int c = cidx2[1], d = 0; c < cidx2[1]+1024; c++){
        values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx2[2], d = 0; c < cidx2[2]+1024; c++){
        values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx2[3], d = 0; c < cidx2[3]+1024; c++){
        values[l][c%1024][iEnt] = wf2[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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
          maxmean[l][2] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][2] = maxmean[l][2]/nEntries2; //find the mean of maximas across entries //Here 0->1
        }

  	  int wf3[32][1024];        // An array of the wf values //Here 0->1
      int cidx3[4];       // An array of the cidx values //Here 0->1
      TFile myFile3("25.root"); // Open the file //Here 0->1
      TTree* myTree3 = (TTree*) myFile3.Get("tree"); // Get the tree from the file //Here 0->1
      inpTemp[3] = 25; //Here 0->1
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

    for (int l = 8; l < 16; l++){
      for (int c = cidx3[1], d = 0; c < cidx3[1]+1024; c++){
        values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx3[2], d = 0; c < cidx3[2]+1024; c++){
        values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx3[3], d = 0; c < cidx3[3]+1024; c++){
        values[l][c%1024][iEnt] = wf3[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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
          maxmean[l][3] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][3] = maxmean[l][3]/nEntries3; //find the mean of maximas across entries //Here 0->1
        }


      int wf4[32][1024];        // An array of the wf values //Here 0->1
      int cidx4[4];       // An array of the cidx values //Here 0->1
      TFile myFile4("26.root"); // Open the file //Here 0->1
      TTree* myTree4 = (TTree*) myFile4.Get("tree"); // Get the tree from the file //Here 0->1
      inpTemp[4] = 26; //Here 0->1
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
      for (int l = 8; l < 16; l++){
      for (int c = cidx4[1], d = 0; c < cidx4[1]+1024; c++){
        values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx4[2], d = 0; c < cidx4[2]+1024; c++){
        values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx4[3], d = 0; c < cidx4[3]+1024; c++){
        values[l][c%1024][iEnt] = wf4[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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
          maxmean[l][4] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][4] = maxmean[l][4]/nEntries4; //find the mean of maximas across entries //Here 0->1
        }


      int wf5[32][1024];        // An array of the wf values //Here 0->1
      int cidx5[4];       // An array of the cidx values //Here 0->1
      TFile myFile5("27.root"); // Open the file //Here 0->1
      TTree* myTree5 = (TTree*) myFile5.Get("tree"); // Get the tree from the file //Here 0->1
      inpTemp[5] = 27; //Here 0->1
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

    for (int l = 8; l < 16; l++){
      for (int c = cidx5[1], d = 0; c < cidx5[1]+1024; c++){
        values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx5[2], d = 0; c < cidx5[2]+1024; c++){
        values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx5[3], d = 0; c < cidx5[3]+1024; c++){
        values[l][c%1024][iEnt] = wf5[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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
          maxmean[l][5] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][5] = maxmean[l][5]/nEntries5; //find the mean of maximas across entries //Here 0->1
        }

      int wf6[32][1024];        // An array of the wf values //Here 0->1
      int cidx6[4];       // An array of the cidx values //Here 0->1
      TFile myFile6("28.root"); // Open the file //Here 0->1
      TTree* myTree6 = (TTree*) myFile6.Get("tree"); // Get the tree from the file //Here 0->1
      inpTemp[6] = 28; //Here 0->1
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

    for (int l = 8; l < 16; l++){
      for (int c = cidx6[1], d = 0; c < cidx6[1]+1024; c++){
        values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 16; l < 24; l++){
      for (int c = cidx6[2], d = 0; c < cidx6[2]+1024; c++){
        values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
        d++;
      }
    }

    for (int l = 24; l < 32; l++){
      for (int c = cidx6[3], d = 0; c < cidx6[3]+1024; c++){
        values[l][c%1024][iEnt] = wf6[l][d]; //values extracted from the waveform
        values[l][c%1024][iEnt] = values[l][c%1024][iEnt] - capmean[l][c%1024]; // removes the offset
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
          maxmean[l][6] += maxval[l][iEnt]; //Here 0->1
        //cout << l << " " << iEnt << " " << maxval[l][iEnt] << endl;
        }
        maxmean[l][6] = maxmean[l][6]/nEntries6; //find the mean of maximas across entries //Here 0->1
      }

      auto canvas = new TCanvas("canvas", "First canvas", 1000, 800);
      canvas->Divide(8,4);
      float maxmeanCh[7] = {0.0};
      //canvas->Divide(2,4);
      TGraph *g[32];
      	//int j = 2;
      for (int j=0; j<32; j++) {
          for (int readingNum=0; readingNum<7; readingNum++) {
          maxmeanCh[readingNum] = maxmean[j][readingNum];
          }
       //cout<<j<<endl;
       canvas->cd(j+1);
       g[j] = new TGraph(7, inpTemp, maxmeanCh);
       g[j]->Draw("AC*");

      }

}
