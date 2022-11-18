#include "pattern_2d.C"

void get_corr(const char *incorr="")
{
	TFile *file = new TFile(incorr, "READ");

	TNtuple *ntuple = (TNtuple*)file->Get("nt_corrVals");
	TH1F *hist = new TH1F("hist", "", 100, 0.5,1.5);
	float tower_eta, tower_phi;
	float corr_val,agg_cv, pattern_cv;
	ntuple->SetBranchAddress("tower_eta", &tower_eta);
	ntuple->SetBranchAddress("tower_phi", &tower_phi);
	ntuple->SetBranchAddress("corr_val", &corr_val);
	ntuple->SetBranchAddress("agg_cv", &agg_cv);


	TH2F *h2 = pattern_2d();

	for(int i=0; i<ntuple->GetEntries(); i++)
	{
		ntuple->GetEntry(i);
		int ieta = (int)tower_eta;
		int iphi = (int)tower_phi;
		pattern_cv = h2->GetBinContent(ieta+1, iphi+1);
		hist->Fill(agg_cv*pattern_cv);
	}
	hist->Draw();
}
