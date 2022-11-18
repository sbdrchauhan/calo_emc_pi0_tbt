Double_t fitf(Double_t *x, Double_t *par)
{
	Double_t a = (x[0]-par[1])/par[2];
	return par[0]*TMath::Exp(-0.5*a*a);
}


void read_histo()
{
	TFile *f = new TFile("write_histo.root");

	TH1D *h1 = (TH1D*)f->Get("h1");
	TH1F *h2 = (TH1F*)f->Get("h2");

	TFile *f2 = new TFile("read_histo.root", "RECREATE");
	f2->cd();
	
	TCanvas *c1 = new TCanvas("c1");
	c1->Divide(1,2);

	TF1 *func = new TF1("func", fitf, 0, 10, 3);
	func->SetParameters(10, h1->GetMean(), h1->GetRMS());
	func->SetParNames("Constant", "Mean_Value", "Sigma");
	
	c1->cd(1);
	h1->Fit("func", "QR");
	h1->Write();
	c1->cd(2);
	h2->Fit("gaus","Q");
	h2->Write();	
	c1->Write();
	f2->Write();

	f2->Close();
	f->Close();
	delete f2;
	delete f;


	/*

	TF1 *fit1 = new TF1("fit1", "gaus", 0, 5);
	TF1 *fit2 = new TF1("fit2", "expo", 5, 10);
	TF1 *total = new TF1("total", "gaus(0)+expo(3)", 0,10);
	
	


	h2->Fit(fit1, "R");
	h2->Fit(fit2, "R+");
	
	double par[5];
	fit1->GetParameters(&par[0]);
	fit2->GetParameters(&par[3]);

	total->SetParameters(par);

	h2->Fit(total, "R+");

	h2->Write();
	//f2->Write();
	f2->Close();
	f->Close();
	delete f2;
	delete f;

	*/
}
