void fit_all_macro(const char *inFile)
{	
	gStyle->SetOptFit(1111);
	TH1F *cemc_hist_eta_phi[96][256];
	for (int i=0; i<96; i++)
	{
		for (int j=0;j<256; j++)
		{
			cemc_hist_eta_phi[i][j] = nullptr;
		}
	}
	
	TFile *file = new TFile(inFile);
	for (int i=0; i<96; i++)
	{
		for (int j=0; j<256; j++)
		{
			TString i1;
			TString j1;
			i1.Form("%d",i);
			j1.Form("%d",j);
			TString hist_name = "emc_ieta" + i1 + "_phi" + j1;
			TH1F *htemp = (TH1F *)file->Get(hist_name.Data());
			cemc_hist_eta_phi[i][j] = htemp;
		}
	}

  TF1 *f1[25000]; 
  TF1 *f2[25000];
  TF1 *total[25000];
  TF1 * fit_fn[25000];
	
	TH2F *fitp1_eta_phi2d = new TH2F("fitp1_eta_phi2d", "", 96,0,96,256,0,256);
	int kj=0;

	TH1F *hdist = new TH1F("hdist", "", 200, 0.0, 2.0);

	for (int ieta=0; ieta<96; ieta++)
	{
		for (int iphi=0; iphi<256; iphi++)
		{
			if (ieta>15 || iphi>15) continue;
			
			float pkloc =  0.0;  
			float bsavloc = 0.0;

			for (int kfi = 1; kfi < 20; kfi++)
			{
				float locbv = cemc_hist_eta_phi[ieta][iphi]->GetBinContent(kfi);
					if (locbv > bsavloc)
					{
						pkloc = cemc_hist_eta_phi[ieta][iphi]->GetBinCenter(kfi);
						bsavloc = locbv;
					} 
				}

				 f1[kj] = new TF1("f1", "gaus", 0.06,0.20);   //pkloc-0.03, pkloc+0.03);
				 f2[kj] = new TF1("f2", "pol2", 0.01, 0.4);

				 cemc_hist_eta_phi[ieta][iphi]->Fit(f1[kj],"","", pkloc-0.04,pkloc+0.04);
				 float fpkloc2 = f1[kj]->GetParameter(1);

				 TGraphErrors * grtemp = new TGraphErrors();
				 TString bkgNm;
				 bkgNm.Form("grBkgEta_%d_%d",ieta,iphi);
						
				 std::cout << " getting " << bkgNm.Data() << "  mean was " 
										<< fpkloc2 << " " << pkloc << std::endl;
				 grtemp->SetName(bkgNm.Data());
			 int ingr = 0;
			for (int gj = 1; gj < cemc_hist_eta_phi[ieta][iphi]->GetNbinsX()+1; gj++)
			{
				float binc = cemc_hist_eta_phi[ieta][iphi]->GetBinCenter(gj); 
				float cntc = cemc_hist_eta_phi[ieta][iphi]->GetBinContent(gj); 
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

			cemc_hist_eta_phi[ieta][iphi]->Fit(total[kj], "R");
			fit_fn[kj] = cemc_hist_eta_phi[ieta][iphi]->GetFunction("total");

			float amp = fit_fn[kj]->GetParameter(0);
			float amp_err = fit_fn[kj]->GetParError(0);
			float peak_mean = fit_fn[kj]->GetParameter(1);
			float peak_err = fit_fn[kj]->GetParError(1);
			float sigma = fit_fn[kj]->GetParameter(2);
			float sigma_err = fit_fn[kj]->GetParError(2);
			
			fitp1_eta_phi2d->SetBinContent(ieta+1,iphi+1,peak_mean);


			kj++;
		}

	}
	fitp1_eta_phi2d->Draw("colz");
}
