void fit_macro(int eta_h=0, int eta=0, int phi=0, const char *inFile="run1_LCE_comb.root")
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

	// file came from runLCE loop macro	
	// that conatins histograms
	TFile *file = new TFile(inFile);

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
			TString i1;
	  	TString j1;
	  	i1.Form("%d",i);
	  	j1.Form("%d",j);
	  	TString hist_name = "emc_ieta" + i1 + "_phi"+ j1;
	  	TH1F *h_eta_phi_temp = (TH1F *)file->Get(hist_name.Data());
	  	cemc_hist_eta_phi[i][j] = h_eta_phi_temp;	
		}
	}

	TFile *outfile = new TFile("out_fit_macro.root", "RECREATE");
	outfile->cd();

	TH2F *fitp1_eta_phi2d = new TH2F("fitp1_eta_phi2d", "peak mean eta-phi", 96,0,96,256,0,256);

	TF1 *f1_eta[25000];
	TF1 *f1_etaphi[25000];

  TF1 *f2_eta[25000];
	TF1 *f2_etaphi[25000];

  TF1 *total_eta[25000];
	TF1 *total_etaphi[25000];

	TF1 *fit_fn_eta[25000];
	TF1 *fit_fn_etaphi[25000];

  int kj = 0;
	
	// First prepare for eta_hists
	double eta_value[96];
  double eta_par1_value[96] = {0.0};
  double eta_par1_error[96] = {0.0};
  double eta_par2_value[96] = {0.0};
  double eta_par2_error[96] = {0.0};

	double cemc_par1_values[96][256] = {{0.0}}; //mising braces Werror w/o double braces
	double cemc_par1_errors[96][256] = {{0.0}};

	for (int ieta=0; ieta<96; ieta++)	// eta loop
	{
		std::cout << "" << std::endl;
		std::cout << "outer loop of 96 eta_slice # " << ieta << std::endl;
		std::cout << "" << std::endl;
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

    f1_eta[kj] = new TF1("f1", "gaus");//, 0.06, 0.20 );//pkloc-0.03, pkloc+0.03);
    f2_eta[kj] = new TF1("f2", "pol2");//, 0.01, 0.4);

    eta_hist[ieta]->Fit(f1_eta[kj],"Q","",pkloc_in-0.04,pkloc_in+0.04);
    float fpkloc2_in = f1_eta[kj]->GetParameter(1);

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
      
    grtemp_in->Fit(f2_eta[kj], "Q");
      
    total_eta[kj] = new TF1("total", "gaus(0)+pol2(3)", 0.06, 0.3);//0.3*fpkloc2/0.145);

    double par_in[6];

    f1_eta[kj]->GetParameters(&par_in[0]);
    f2_eta[kj]->GetParameters(&par_in[3]);

    total_eta[kj]->SetParameters(par_in);
    total_eta[kj]->SetParLimits(2,0.01,0.027);
    eta_hist[ieta]->Fit(total_eta[kj], "RQ");
		eta_hist[ieta]->Write();
    fit_fn_eta[kj] = eta_hist[ieta]->GetFunction("total");
     
    if (fit_fn_eta[kj])
		{
	  	eta_value[ieta] = ieta;
	  	eta_par1_value[ieta]= fit_fn_eta[kj]->GetParameter(1); 
	  	if (!(eta_par1_value[ieta] > 0))
	      eta_par1_value[ieta] = 0.5;
	  	eta_par1_error[ieta]= fit_fn_eta[kj]->GetParError(1); 
	  	eta_par2_value[ieta]= fit_fn_eta[kj]->GetParameter(2); 
	  	eta_par2_error[ieta]= fit_fn_eta[kj]->GetParError(2); 
		}
    else
		{
	  	std::cout <<  "WarninG :: Fit Failed for eta bin : " << ieta << std::endl;
		}	
		
		// start of the inner for Loop to work for eta-phi towers
		// -----------------------------------------------------------------..
		for (int iphi=0; iphi<256; iphi++)
		{
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
				
			f1_etaphi[kj] = new TF1("f1", "gaus");// 0.145+0.03);//"gaus",pkloc-0.03,pkloc+0.03
			f2_etaphi[kj] = new TF1("f2", "pol2");//, 0.01, 0.4);

			cemc_hist_eta_phi[ieta][iphi]->Fit(f1_etaphi[kj], "Q", "",\
							 pkloc-0.03*pkloc/0.145, pkloc+0.03*pkloc/0.145);//, pkloc-0.03, pkloc+0.03);
			float fpkloc2 = f1_etaphi[kj]->GetParameter(1);
			
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
					
			grtemp->Fit(f2_etaphi[kj],"Q");

			total_etaphi[kj] = new TF1("total", "gaus(0)+pol2(3)",0.07, 0.30);//0.3*fpkloc2/0.145

			double par[6];

			// gaus parameters use from corresponding eta_slice
			par[0] = par_in[0];
			par[1] = par_in[1];
			par[2] = par_in[2];
			double f2_0 = f2_etaphi[kj]->GetParameter(0);
			double f2_1 = f2_etaphi[kj]->GetParameter(1);
			double f2_2 = f2_etaphi[kj]->GetParameter(2);

			par[3] = f2_0;
			par[4] = f2_1;
			par[5] = f2_2;

			total_etaphi[kj]->SetParameters(par); //_in);
			total_etaphi[kj]->SetParLimits(2, 0.01, 0.027);
			
			//total_etaphi[kj]->FixParameter(3,f2_0);
			//total_etaphi[kj]->FixParameter(4,f2_1);
			//total_etaphi[kj]->FixParameter(5,f2_2);

			cemc_hist_eta_phi[ieta][iphi]->Fit(total_etaphi[kj], "RQ");
			cemc_hist_eta_phi[ieta][iphi]->Write();
			fit_fn_etaphi[kj] = cemc_hist_eta_phi[ieta][iphi]->GetFunction("total");
			
			if (fit_fn_etaphi[kj])
			{
				cemc_par1_values[ieta][iphi] = fit_fn_etaphi[kj]->GetParameter(1);
				/*if (fit_fn_etaphi[kj]->GetParameter(1) <= 0.054)
				{
					// what new changes to do refit?
				}*/
				cemc_par1_errors[ieta][iphi] = fit_fn_etaphi[kj]->GetParError(1);
			}
			else
			{
				std::cout << "Warning::Fit Failed for eta bin : " << ieta << iphi << std::endl;
				cemc_par1_values[ieta][iphi] = -999.0;
				cemc_par1_errors[ieta][iphi] = -999.0;
			}

			fitp1_eta_phi2d->SetBinContent(ieta+1,iphi+1,cemc_par1_values[ieta][iphi]);
			fitp1_eta_phi2d->SetBinError(ieta+1,iphi+1,cemc_par1_errors[ieta][iphi]);

			kj++;
		}
	}
	//fitp1_eta_phi2d->SetMinimum(0.11);
	//fitp1_eta_phi2d->SetMaximum(0.18);
	fitp1_eta_phi2d->Write();
	
	// saving eta slices into jpg
	/*
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
	}
}


