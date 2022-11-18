#include <string>
#include "TChain.h"
#include "TTree.h"
#include "TString.h"

void tree_analysis(TString ifile)
{
	ifstream inFile;
	inFile.open(ifile, ios::in);
	TChain *pitree = new TChain("_eventTree");
	string root_file;
	while (std::getline(inFile, root_file))
		pitree->Add(root_file.c_str());
	
	pitree->Draw("_clusterEnergies");
}
