{
  #include "TTree.h"
  #include "TFile.h"
  #include "TH1F.h"
  #include "TCanvas.h"
  #include<iostream>
  #include<string>
  #include<vector>
  #include<fstream>
  #include<sstream>
  std::vector<string> inpVoltages;
  std::ifstream file ("inpVoltages.txt");
  std::string filename;
  while (file.good()){
    getline(file, filename);
    inpVoltages.push_back(filename);
  }
  for (int file=0; file<3;file++){
    TFile *myFile1 = new TFile(inpVoltages[file]); // Open the file
    TTree* myTree1 = (TTree*) myFile1->Get("tree"); // Get the tree from the file
    myTree1->Print();
    delete[] myTree1;
    delete[] myFile1;
  }

}
