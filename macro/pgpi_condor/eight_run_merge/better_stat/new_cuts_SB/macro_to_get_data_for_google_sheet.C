#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>

void macro_to_get_data_for_google_sheet(const char * ifile="", int h=0)
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

	eta_hist[h]->Draw();
	TF1 *f1 = new TF1();
	f1 = eta_hist[h]->GetFunction("total");
	
	float amp = f1->GetParameter(0);
	float amp_err = f1->GetParError(0);
	float peak_mean = f1->GetParameter(1);
	float peak_err = f1->GetParError(1);
	float sigma = f1->GetParameter(2);
	float sigma_err = f1->GetParError(2);
	
	int lowBin = eta_hist[h]->FindBin(peak_mean - 2.5*sigma);
	int highBin = eta_hist[h]->FindBin(peak_mean + 2.5*sigma);

	std::cout << "low bin# of signal: " << lowBin << std::endl;
	std::cout << "high bin# of signal: " << highBin << std::endl;

	int N2 = eta_hist[h]->Integral(lowBin, highBin);	
	
	int numberBins = highBin - lowBin + 1;
	std::cout << "total bins to include: " << numberBins << std::endl;
	
	int N1 = eta_hist[h]->Integral(lowBin-numberBins+1, lowBin);
	std::cout << "left bkg start from: " << eta_hist[h]->GetXaxis()->GetBinCenter(lowBin-numberBins+1) << std::endl;
	std::cout << "left bkg ends in: " << eta_hist[h]->GetXaxis()->GetBinCenter(lowBin) << std::endl;

	int N3 = eta_hist[h]->Integral(highBin, highBin+numberBins-1);
	std::cout << "right side bkg start from: " << eta_hist[h]->GetXaxis()->GetBinCenter(highBin) << std::endl;
	std::cout << "right side bkg ends in: " << eta_hist[h]->GetXaxis()->GetBinCenter(highBin+numberBins-1) << std::endl;


	double b = (N1+N3)/2.0;
	double s = N2 - b;
	
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
