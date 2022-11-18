#include "TFile.h"
#include "TH1.h"
#include "TRandom.h"

void write_histo()
{
	TFile *f = new TFile("write_histo.root", "RECREATE");
	
	// 1st histogram
	TH1D *h1 = new TH1D("h1", "h1", 100, 0, 10);
	for (int i=0; i<1000; i++)
	{
		h1->Fill(gRandom->Exp(5));
	}

	// 2nd histogram
	TH1F *h2 = new TH1F("h2", "h2 histo", 100, -5, 5);
	h2->FillRandom("gaus", 10000);
	
	// writing into the file
	h1->Write();
	h2->Write();
	f->Close();
	delete f;
}
