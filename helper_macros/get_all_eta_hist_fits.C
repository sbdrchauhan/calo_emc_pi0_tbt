#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>

void get_all_eta_hist_fits(const char * ifile="")
{
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)

	TH1F *eta_hist[96];
	for (int i=0; i<96; i++)
		eta_hist[i] = nullptr;
	

	TFile *file = new TFile(ifile);
	for (int i=0; i<96; i++)
	{
		TString a;
		a.Form("%d", i);
		TString b = "eta_"+ a;
		TH1F *h_temp = (TH1F *)file->Get(b.Data());
		eta_hist[i] = h_temp;
	}
	// 3x3
	TCanvas *c11 = new TCanvas("c11");
	c11->Divide(3,3);
	c11->cd(1);
	eta_hist[0]->Draw();
	c11->cd(2);
	eta_hist[10]->Draw();
	c11->cd(3);
	eta_hist[20]->Draw();
	c11->cd(4);
	eta_hist[30]->Draw();
	c11->cd(5);
	eta_hist[40]->Draw();
	c11->cd(6);
	eta_hist[50]->Draw();
	c11->cd(7);
	eta_hist[60]->Draw();
	c11->cd(8);
	eta_hist[80]->Draw();
	c11->cd(9);
	eta_hist[90]->Draw();
	c11->SaveAs("3x3_eta_hist.jpg");


/*
	//-------------------------------
	// 0-23
	TCanvas*c1 = new TCanvas("c1");
	c1->Divide(6,4);
	for (int i=0; i<24; i++)
	{
		c1->cd(i+1);
		eta_hist[i]->Draw();
	}
	c1->SaveAs("canvas 1: 0-23.jpg");
	
	//---------------------------------------
	// 24-47
	TCanvas*c2 = new TCanvas("c2");
	c2->Divide(6,4);
	for (int i=24; i<48; i++)
	{
		c2->cd(i-23);
		eta_hist[i]->Draw();
	}
	c2->SaveAs("canvas 2: 24-47.jpg");
	//-------------------------------------
	// 48-71
	TCanvas*c3 = new TCanvas("c3");
	c3->Divide(6,4);
	for (int i=48; i<72; i++)
	{
		c3->cd(i-47);
		eta_hist[i]->Draw();
	}
	c3->SaveAs("canvas 3: 48-71.jpg");

	//------------------------------
	//72-95
	TCanvas*c4 = new TCanvas("c4");
	c4->Divide(6,4);
	for (int i=72; i<96; i++)
	{
		c4->cd(i-71);
		eta_hist[i]->Draw();
	}
	c4->SaveAs("canvas 4: 72-95.jpg");
	*/

}
