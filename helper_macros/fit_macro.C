void fit_macro(const char *inFile="run1_LCE_comb_smooth1.root")
{	
	gStyle->SetOptFit(1111);

	// declaring histograms
	TH1F *eta_hist[96];
	TH1F *cemc_hist_eta_phi[96][256];
	for (int nj = 0; nj < 96; nj++)
	{
		eta_hist[nj] = nullptr;
		for (int nk = 0; nk < 256; nk++)
		{
			cemc_hist_eta_phi[nj][nk] = nullptr;
		}
	}

	// that contains histograms
	TFile *file = new TFile(inFile);

	float x_axis[24576];
	int x_count = 0;
	// getting histograms from the input file
	for (int i=0; i<96; i++)
	{
		TString a;
		a.Form("%d", i);
		TString b = "eta_"+ a;
		TH1F *h_temp = (TH1F *)file->Get(b.Data());
		eta_hist[i] = h_temp;
		for (int j=0; j<256; j++)
		{
			x_axis[x_count] = x_count;
			x_count ++;
			TString i1;
	  	TString j1;
	  	i1.Form("%d",i);
	  	j1.Form("%d",j);
	  	TString hist_name = "emc_ieta" + i1 + "_phi"+ j1;
	  	TH1F *h_eta_phi_temp = (TH1F *)file->Get(hist_name.Data());
	  	cemc_hist_eta_phi[i][j] = h_eta_phi_temp;	
		}
	}

	// saving fit files into this:
	TFile *outfile = new TFile("out_fit_macro1.root", "RECREATE");
	outfile->cd();

	TH2F *fitp1_eta_phi2d = new TH2F("fitp1_eta_phi2d", "peak mean eta-phi", 96,0,96,256,0,256);
	float chi2 = -9999.99;
	float ndf = -9999.99;
	double par[6];

	TF1 *fit_gaus;
	TF1 *fit_bkg;
	TF1 *fit_total;
	TF1 *fit_result;
	

	double cemc_par1_values[96][256] = {{0.0}};
	double cemc_par1_errors[96][256] = {{0.0}};
	float cemc_etaphi_fitmean[24576];
	int it_etaphi=0;

	// outer etabin loop
	for (int ieta=0; ieta<96; ieta++)
	{
		std::cout << "started etabin: " << ieta << std::endl;
		//find max bin around peak
		float pkloc_in =  0.0;  
		float bsavloc_in = 0.0;

		for (int kfi_in = 1; kfi_in < 20; kfi_in++)
		{
			float locbv_in = eta_hist[ieta]->GetBinContent(kfi_in);
			if (locbv_in > bsavloc_in)
			{
				pkloc_in = eta_hist[ieta]->GetBinCenter(kfi_in);
				bsavloc_in = locbv_in;
			} 
		}

    fit_gaus = new TF1("fit_gaus", "gaus");//, 0.06, 0.20 );//pkloc-0.03, pkloc+0.03);
    fit_bkg = new TF1("fit_bkg", "pol2");//, 0.01, 0.4);
    eta_hist[ieta]->Fit(fit_gaus,"Q","",pkloc_in-0.04,pkloc_in+0.04);
    float fpkloc2_in = fit_gaus->GetParameter(1);

    TGraphErrors * grtemp_in = new TGraphErrors();
    TString bkgNm_in;
    bkgNm_in.Form("grBkgEta_%d",ieta);
      
    /*std::cout << " getting " << bkgNm_in.Data() << "  mean was " 
		<< fpkloc2_in << " " << pkloc_in << std::endl;*/
    grtemp_in->SetName(bkgNm_in.Data());
    int ingr_in = 0;
    for (int gj_in = 1; gj_in < eta_hist[ieta]->GetNbinsX()+1; gj_in++)
		{
	  	float binc_in = eta_hist[ieta]->GetBinCenter(gj_in); 
	  	float cntc_in = eta_hist[ieta]->GetBinContent(gj_in); 
	  	if ((binc_in > 0.06*fpkloc2_in/0.145 && binc_in < 0.09 *fpkloc2_in/0.145)
	  	   || (binc_in > 0.22*fpkloc2_in/0.145 && binc_in < 0.35*fpkloc2_in/0.145))
	    {
	     	grtemp_in->SetPoint(ingr_in,binc_in,cntc_in);
	     	grtemp_in->SetPointError(ingr_in++,0.001,sqrt(cntc_in));
	    }
		}
      
    grtemp_in->Fit(fit_bkg, "Q");

    fit_total = new TF1("fit_total", "gaus(0)+pol2(3)", 0.06, 0.30);//0.3*fpkloc2/0.145);

    double par_in[6];

    fit_gaus->GetParameters(&par_in[0]);
    fit_bkg->GetParameters(&par_in[3]);

    fit_total->SetParameters(par_in);
    fit_total->SetParLimits(2,0.01,0.027);
    eta_hist[ieta]->Fit(fit_total, "RQ");
		eta_hist[ieta]->Write();
  		
		// start of the inner for Loop to work for eta-phi towers
		// -----------------------------------------------------------------..
		for (int iphi=0; iphi<256; iphi++)
		{
			//if (!cemc_hist_eta_phi[ieta][iphi]->GetBinContent(10))continue;

			// find max bin around peak	
			float pkloc = 0.0;
			float bsavloc = 0.0;
			for (int kfi=1; kfi<20; kfi++)	// old kfi<25
			{
				float locbv = cemc_hist_eta_phi[ieta][iphi]->GetBinContent(kfi);
				if (locbv > bsavloc)
				{
					pkloc = cemc_hist_eta_phi[ieta][iphi]->GetBinCenter(kfi);
					bsavloc = locbv;
				}
			}
				
			cemc_hist_eta_phi[ieta][iphi]->Fit(fit_gaus, "Q", "",\
							 pkloc-0.03*pkloc/0.145, pkloc+0.03*pkloc/0.145);//, pkloc-0.03, pkloc+0.03);
			float fpkloc2 = fit_gaus->GetParameter(1);
			
			TGraphErrors *grtemp = new TGraphErrors();
			TString bkgNm;
			bkgNm.Form("grBkgEta_phi_%d_%d", ieta, iphi);
				
			/*std::cout << " getting " << bkgNm.Data() << " mean was " << fpkloc2\
			<< " " << pkloc << std::endl;*/
			
			grtemp->SetName(bkgNm.Data());
			int ingr = 0;
			for (int gj=1; gj<cemc_hist_eta_phi[ieta][iphi]->GetNbinsX()+1; gj++)
			{
				float binc = cemc_hist_eta_phi[ieta][iphi]->GetBinCenter(gj);
				float cntc = cemc_hist_eta_phi[ieta][iphi]->GetBinContent(gj);
				if ((binc>0.06*fpkloc2/0.145 && binc<0.09*fpkloc2/0.145) ||\
					 (binc>0.22*fpkloc2/0.145 && binc<0.45*fpkloc2/0.145))
				{
					grtemp->SetPoint(ingr,binc,cntc);
					grtemp->SetPointError(ingr++,0.001,sqrt(cntc));
				}
			}
					
			grtemp->Fit(fit_bkg,"Q");
			
			double parr[6];
			parr[0] = par_in[0];
			parr[1] = par_in[1];
			parr[2] = par_in[2];
			parr[3] = fit_bkg->GetParameter(0);
			parr[4] = fit_bkg->GetParameter(1);
			parr[5] = fit_bkg->GetParameter(2);
			
			fit_total->SetParameters(parr);
			//fit_total->SetParLimits(1, 0.1215, 0.1485);
 
			fit_total->SetParLimits(1,0.11,0.19);
			
			// gaus parameters use from corresponding eta_slice
			fit_total->FixParameter(1,0.135);
			cemc_hist_eta_phi[ieta][iphi]->Fit(fit_total, "Q");
			fit_total->SetParLimits(1,0.11,0.19);
			cemc_hist_eta_phi[ieta][iphi]->Fit(fit_total,"RQ");
			//cemc_hist_eta_phi[ieta][iphi]->Write();
			fit_result = cemc_hist_eta_phi[ieta][iphi]->GetFunction("fit_total");
			chi2 = fit_result->GetChisquare();
			ndf = fit_result->GetNDF();
			int fit_count = 0;
			int p1_change = 0;
			while (chi2/ndf > 3.0 && fit_count < 7)
			{
				if (p1_change==0)fit_total->FixParameter(1,0.17);
				if (p1_change==1)fit_total->FixParameter(1,0.16);
				if (p1_change==2)fit_total->FixParameter(1,0.15);
				if (p1_change==3)fit_total->FixParameter(1,0.14);
				if (p1_change==4)fit_total->FixParameter(1,0.13);
				
				cemc_hist_eta_phi[ieta][iphi]->Fit(fit_total, "Q");
				fit_total->SetParLimits(1,0.11,0.19);
				cemc_hist_eta_phi[ieta][iphi]->Fit(fit_total,"RQ");
				fit_result = cemc_hist_eta_phi[ieta][iphi]->GetFunction("fit_total");
				chi2 = fit_result->GetChisquare();
				ndf = fit_result->GetNDF();
				
				p1_change++;
				fit_count++;
			}

			cemc_hist_eta_phi[ieta][iphi]->Write();
			cemc_par1_values[ieta][iphi] = fit_result->GetParameter(1);
			cemc_par1_errors[ieta][iphi] = fit_result->GetParError(1);
			fitp1_eta_phi2d->SetBinContent(ieta+1,iphi+1,cemc_par1_values[ieta][iphi]);
			fitp1_eta_phi2d->SetBinError(ieta+1,iphi+1,cemc_par1_errors[ieta][iphi]);
			cemc_etaphi_fitmean[it_etaphi] = cemc_par1_values[ieta][iphi];
			it_etaphi++;
		}
	}

	fitp1_eta_phi2d->Write();	
	
	TGraphErrors *gr = new TGraphErrors(24576,x_axis,cemc_etaphi_fitmean,0,0);
	gr->SetName("etaphi_fit_mean");
	gr->Write();


	// saving eta slices into jpg
	
	TCanvas *c_eta = new TCanvas("c_eta");
	c_eta->Divide(8,12);
	//c_eta->Divide(4,4);
	for (int i=0; i<96; i++)
	{
		c_eta->cd(i+1);
		eta_hist[i]->SetStats(0);
		eta_hist[i]->SetTitle("");
		eta_hist[i]->Draw();

		double x0 = 0.4;
		int bin = eta_hist[i]->FindBin(x0);
		double y = eta_hist[i]->GetBinContent(bin);
		double y0 = 0.2*y;
		
		std::string tt = "eta_"+std::to_string(i);
		
		TText *t = new TText(x0,y0,tt.c_str());
		t->SetTextSize(0.2);
		t->Draw();
	}
	c_eta->SaveAs("eta_slice_fitting.pdf");
	//---------------------------------------*/
	
	// saving eta-phi tbt into jpg
	
	std::vector<TCanvas *> c_eta_phi(192);
	int tbt_count = 0;
	int c_count = 1;
	int cd_it = 1;
	int flag = true;
	for (int i=0; i<96; i++)
	{
		for (int j=0; j<256; j++)
		{
			if (tbt_count < 128)
			{
				if (flag) {
					TString c_name = "canvas_" + std::to_string(c_count);
					TCanvas *c = new TCanvas(c_name.Data());
					c_eta_phi[c_count] = c;
					c_eta_phi[c_count]->Divide(8,16);//16,8);
					flag = false;
				}

				c_eta_phi[c_count]->cd(cd_it);
				cemc_hist_eta_phi[i][j]->SetStats(0);
				cemc_hist_eta_phi[i][j]->SetTitle("");
				cemc_hist_eta_phi[i][j]->Draw();
				
				double x0 = 0.4;
				int bin = cemc_hist_eta_phi[i][j]->FindBin(x0);
				double y = cemc_hist_eta_phi[i][j]->GetBinContent(bin);
				double y0 = 0.2*y;
				std::string tt = "eta_"+std::to_string(i)+"_phi_"+std::to_string(j);

				TText *t = new TText(x0,y0,tt.c_str());
				t->SetTextSize(0.15);
				t->Draw();
				tbt_count += 1;
				cd_it += 1;
			}
			
			if(tbt_count==128)
			{
				TString save = "Canvas_"+std::to_string(c_count)+".pdf";
				c_eta_phi[c_count]->SaveAs(save.Data());
				tbt_count=0;
				cd_it = 1;
				c_count += 1;
				flag = true;
			}
		}
	}//--------------*/



}


