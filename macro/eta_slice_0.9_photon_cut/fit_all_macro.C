void fit_all_macro(const char *inFile)
{	
	gStyle->SetOptFit(1111);
	TH1F *eta_hist[96];
	for (int i=0; i<96; i++)
		eta_hist[i] = nullptr;
	
	TFile *file = new TFile(inFile);
	for (int i=0; i<96; i++)
	{
		TString a;
		a.Form("%d", i);
		TString b = "eta_"+ a;
		TH1F *h_temp = (TH1F *)file->Get(b.Data());
		eta_hist[i] = h_temp;
	}

  TF1 *f1[100]; 
  TF1 *f2[100];
  TF1 *total[100];
  TF1 * fit_fn[100];
	int kj=0;

	auto c1 = new TCanvas();


	TH1F *hdist = new TH1F("hdist", "", 200, 0.0, 2.0);

	for (int i=0; i<96; i++)
	{
		float pkloc =  0.0;  
		float bsavloc = 0.;

		for (int kfi = 1; kfi < 20; kfi++)
		{
			float locbv = eta_hist[i]->GetBinContent(kfi);
			if (locbv > bsavloc)
			{
				pkloc = eta_hist[i]->GetBinCenter(kfi);
				bsavloc = locbv;
			} 
		}

		 f1[kj] = new TF1("f1", "gaus", 0.06,0.20);   //pkloc-0.03, pkloc+0.03);
		 f2[kj] = new TF1("f2", "pol2", 0.01, 0.4);
		 eta_hist[i]->Fit(f1[kj],"","", pkloc-0.04,pkloc+0.04);
		 float fpkloc2 = f1[kj]->GetParameter(1);

		 TGraphErrors * grtemp = new TGraphErrors();
		 TString bkgNm;
		 bkgNm.Form("grBkgEta_%d",i);
				
		 std::cout << " getting " << bkgNm.Data() << "  mean was " 
								<< fpkloc2 << " " << pkloc << std::endl;
		 grtemp->SetName(bkgNm.Data());
		 int ingr = 0;
		for (int gj = 1; gj < eta_hist[i]->GetNbinsX()+1; gj++)
		{
			float binc = eta_hist[i]->GetBinCenter(gj); 
			float cntc = eta_hist[i]->GetBinContent(gj); 
			if ((binc > 0.06*fpkloc2/0.145 && binc < 0.09 *fpkloc2/0.145)
				 || (binc > 0.22*fpkloc2/0.145 && binc < 0.35*fpkloc2/0.145))
			{
				grtemp->SetPoint(ingr,binc,cntc);
				grtemp->SetPointError(ingr++,0.001,sqrt(cntc));
			}
		}  
		grtemp->Fit(f2[kj]);
				
		total[kj] = new TF1("total", "gaus(0)+pol2(3)", 0.06, 0.25);

		double par[6];

		f1[kj]->GetParameters(&par[0]);
		f2[kj]->GetParameters(&par[3]);

		total[kj]->SetParameters(par);
		total[kj]->SetParLimits(2,0.01,0.027);
		eta_hist[i]->Fit(total[kj], "R");
		fit_fn[kj] = eta_hist[i]->GetFunction("total");

		float amp = fit_fn[kj]->GetParameter(0);
		float amp_err = fit_fn[kj]->GetParError(0);
		float peak_mean = fit_fn[kj]->GetParameter(1);
		float peak_err = fit_fn[kj]->GetParError(1);
		float sigma = fit_fn[kj]->GetParameter(2);
		float sigma_err = fit_fn[kj]->GetParError(2);
		
		hdist->Fill(0.135/peak_mean);

		kj++;
	}

	hdist->Draw();
}
