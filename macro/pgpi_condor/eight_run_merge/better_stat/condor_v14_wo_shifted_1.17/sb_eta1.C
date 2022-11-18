#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>
#include <vector>

void sb_eta1(const char * ifile="corr_v14_0.9.root")
{
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)

	gStyle->SetOptFit(1111);
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


	auto c1 = new TCanvas();
	c1->SetFillColor(42);
	c1->SetGrid();

	auto gr1 = new TGraph();
	auto gr2 = new TGraph();

	std::cout << "started looping on etas: " << std::endl;
	int x_index = 0;
	double even_sig;
	double even_bkg;
	for (int i=0; i<96; i++)
	{
		TF1 *f1 = new TF1();
		f1 = eta_hist[i]->GetFunction("total");
	
		float amp = f1->GetParameter(0);
		float amp_err = f1->GetParError(0);
		float peak_mean = f1->GetParameter(1);
		float peak_err = f1->GetParError(1);
		float sigma = f1->GetParameter(2);
		float sigma_err = f1->GetParError(2);
	
		int lowBin = eta_hist[i]->FindBin(peak_mean - 2.5*sigma);
		int highBin = eta_hist[i]->FindBin(peak_mean + 2.5*sigma);

		int N2 = eta_hist[i]->Integral(lowBin, highBin);	
	
		int numberBins = highBin - lowBin + 1;

		int N1 = eta_hist[i]->Integral(lowBin-numberBins+1, lowBin);


		int N3 = eta_hist[i]->Integral(highBin, highBin+numberBins-1);
		double b = (N1+N3)/2.0;
		double s = N2 - b;
			
		if (i%2==0){
			even_sig=s;
			even_bkg=b;
		}

		else{
			double avg_sig = (even_sig+s)/2.0;
			double avg_bkg = (even_bkg+b)/2.0;
			gr1->AddPoint(i, avg_sig);
			gr2->AddPoint(i, avg_bkg);
		}
	
	}
	gr1->GetHistogram()->SetMaximum(6500.);
	gr1->GetHistogram()->SetMinimum(0.);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(20);
	gr1->SetTitle("signal");
	gr1->GetXaxis()->SetTitle("eta");
	gr1->GetYaxis()->SetTitle("counts");
	gr1->Draw("AP");

	gr2->SetMarkerColor(2);
	gr2->SetTitle("bkg");
	gr2->SetMarkerStyle(29);
	gr2->Draw("P same");

	gPad->BuildLegend();

	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}


