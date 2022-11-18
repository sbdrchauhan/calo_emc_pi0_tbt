void reso_new_cut()
{
	
	// For etabin 50

	// sigma_E/E = a/sqrt(X)+b; with a = 13.9%, b=5.8%
	TF1 *f1 = new TF1("f1", "sqrt(0.139*0.139/x+0.058*0.058)", 0.1, 3.);
		
	// sigma_m/m
	TH1F *h1 = new TH1F("h1", "", 300, 0, 3);
	for (int i=11; i<300; i++)
	{
		if (i>60) h1->SetBinContent(i+1, sqrt(0.25*f1->Eval(TMath::Max(0.6, 1.0/3.0*i*0.01))*f1->Eval(TMath::Max(0.6, 1.0/3.0*i*0.01)) + 0.25*f1->Eval(i*0.01)*f1->Eval(i*0.01)  ));
		
		else h1->SetBinContent(i+1, 1.0/sqrt(2)*f1->Eval(i*0.01));
	}

	TH1F *h2 = (TH1F*)h1->Clone();

	Double_t scale = 0.90;
	h2->Scale(scale);

	// peak_width/peak_mean from fit
	const Int_t n = 6;
	Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
	Double_t y[n] = {0.11514404278, 0.11437460137, 0.10393473746, 0.10606255585, 0.10200792545, 0.10167783537};
	TGraph *gr = new TGraph(n,x,y);
	gr->SetMarkerStyle(21);
	gr->SetMarkerColor(4);
	//gr->SetMarkerSize(2);

	f1->Draw();
	h1->Draw("P,same");
	h2->Draw("HIST, same");
	gr->Draw("P,same");
		


/*
	h1->Draw("P");
	gr->Draw("P");
	f1->Draw("same");
	*/
}

