#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>
#include <vector>

void sb_eta(const char * ifile="")
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

	double signals[96];
	double bkg[96];
	double etas[96];

	double even_sig;
	double even_bkg;

std::cout << "started looping on etas: " << std::endl;
for (int i=0; i<96; i++)
{
	etas[i] = i;
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
		signals[i] = avg_sig;
		bkg[i] = avg_bkg;
	}
	
}

	auto c1 = new TCanvas("c1", "c1", 200,10, 600,400);
	c1->SetFillColor(42);
	c1->SetGrid();

	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle("signal/bkg vs eta");

	auto gr = new TGraph(48, etas, signals);
	gr->SetTitle("signal");
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(20);

	auto gr2 = new TGraph(48, etas, bkg);
	gr2->SetTitle("bkg");
	gr2->SetMarkerColor(2);
	gr2->SetMarkerStyle(29);
	
	mg->Add(gr);
	mg->Add(gr2);
	mg->Draw("AP");
	mg->GetXaxis()->SetTitle("eta");
	mg->GetYaxis()->SetTitle("counts");

	gPad->BuildLegend();

	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}

