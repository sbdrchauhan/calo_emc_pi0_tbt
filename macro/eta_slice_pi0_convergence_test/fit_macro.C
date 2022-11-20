void fit_macro(const char *inFile, int h)
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

	eta_hist[h]->Draw();


  TF1 *f1; 
  TF1 *f2;
  TF1 *total;
  TF1 * fit_fn;

	float pkloc =  0.0;  
	float bsavloc = 0.;

	for (int kfi = 1; kfi < 20; kfi++)
	{
		float locbv = eta_hist[h]->GetBinContent(kfi);
		if (locbv > bsavloc)
		{
			pkloc = eta_hist[h]->GetBinCenter(kfi);
			bsavloc = locbv;
		} 
	}

   f1 = new TF1("f1", "gaus", pkloc-0.03, pkloc+0.03 );//0.06,0.20);   //pkloc-0.03, pkloc+0.03);
   f2 = new TF1("f2", "pol2", 0.01, 0.4);
   eta_hist[h]->Fit(f1,"","", pkloc-0.04,pkloc+0.04);
   float fpkloc2 = f1->GetParameter(1);

   TGraphErrors * grtemp = new TGraphErrors();
   TString bkgNm;
   bkgNm.Form("grBkgEta_%d",h);
      
   std::cout << " getting " << bkgNm.Data() << "  mean was " 
							<< fpkloc2 << " " << pkloc << std::endl;
   grtemp->SetName(bkgNm.Data());
   int ingr = 0;
  for (int gj = 1; gj < eta_hist[h]->GetNbinsX()+1; gj++)
	{
		float binc = eta_hist[h]->GetBinCenter(gj); 
  	float cntc = eta_hist[h]->GetBinContent(gj); 
  	if ((binc > 0.06*fpkloc2/0.145 && binc < 0.09 *fpkloc2/0.145)
  	   || (binc > 0.22*fpkloc2/0.145 && binc < 0.35*fpkloc2/0.145))
    {
			grtemp->SetPoint(ingr,binc,cntc);
     	grtemp->SetPointError(ingr++,0.001,sqrt(cntc));
    }
	}  
	auto c1 = new TCanvas();
  grtemp->Fit(f2);
      
  total = new TF1("total", "gaus(0)+pol2(3)", 0.06, 0.25);

  double par[6];

  f1->GetParameters(&par[0]);
  f2->GetParameters(&par[3]);

  total->SetParameters(par);
  total->SetParLimits(2,0.01,0.027);

	auto c2 = new TCanvas();
  eta_hist[h]->Fit(total, "R");
  fit_fn = eta_hist[h]->GetFunction("total");

	float amp = fit_fn->GetParameter(0);
	float amp_err = fit_fn->GetParError(0);
	float peak_mean = fit_fn->GetParameter(1);
	float peak_err = fit_fn->GetParError(1);
	float sigma = fit_fn->GetParameter(2);
	float sigma_err = fit_fn->GetParError(2);

  int lowBin = eta_hist[h]->FindBin(peak_mean - 2.5*sigma);
	int highBin = eta_hist[h]->FindBin(peak_mean + 2.5*sigma);

	int N2 = eta_hist[h]->Integral(lowBin, highBin);	
	int numberBins = highBin - lowBin + 1;
	int N1 = eta_hist[h]->Integral(lowBin-numberBins+1, lowBin);
	int N3 = eta_hist[h]->Integral(highBin, highBin+numberBins-1);
	double b = (N1+N3)/2.0;
	double s = N2 - b;


	std::cout << "N1 low bin cont: " << eta_hist[h]->GetBinCenter(lowBin-numberBins+1) << std::endl;
	std::cout << "N1 high bin cont: " << eta_hist[h]->GetBinCenter(lowBin) << std::endl;

	std::cout << "N3 low bin cont: " << eta_hist[h]->GetBinCenter(highBin) << std::endl;
	std::cout << "N3 low bin cont: " << eta_hist[h]->GetBinCenter(highBin+numberBins-1) << std::endl;
	/*

	std::cout << "======================" << std::endl;
	std::cout << "N1 counts: " << N1 << std::endl;
	std::cout << "N2 counts: " << N2 << std::endl;
	std::cout << "N3 counts: " << N3 << std::endl;
	std::cout << "p0: " << amp << std::endl;
	std::cout << "p0 error: " << amp_err << std::endl;
	std::cout << "p1: " << peak_mean << std::endl;
	std::cout << "p1 error: " << peak_err << std::endl;
	std::cout << "p2: " << sigma << std::endl;
	std::cout << "p2 error: " << sigma_err << std::endl;
	std::cout << "==================" << std::endl;
	std::cout << "Signal: " << s << std::endl;
	std::cout << "Background: " << b << std::endl;

	*/


}
