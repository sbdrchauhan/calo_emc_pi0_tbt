void background_fit()
{
	auto c = new TCanvas();
	c->SetLogy();

    const Int_t n = 6;

    Double_t x2[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y2[n] = {8771, 3325, 1406.5, 959.5, 547, 216}; 
		Double_t ex2[n] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    Double_t ey2[n] = {sqrt(y2[0]), sqrt(y2[1]), sqrt(y2[2]), sqrt(y2[3])
                      ,sqrt(y2[4]), sqrt(y2[5])};
    auto gr2 = new TGraphErrors(n, x2, y2, ex2, ey2);
    auto axis2 = gr2->GetXaxis();
    axis2->SetLimits(0.1, 5.);
    gr2->SetTitle("Background eta_75 Plot");
		gr2->GetXaxis()->SetTitle("leading photon pT");
		gr2->GetYaxis()->SetTitle("log-scale");
    gr2->SetMarkerColor(4);
    gr2->SetMarkerStyle(23);
    gr2->Draw("AP"); //"AP");

    TF1 *f1 = new TF1("f1", "[0]/([1]+x)^[2]", 0.1, 5.);
		// had to set parameters else it won't fit
		// borrowed the parameters from the 1.17 shifted case
		f1->SetParameters(2.57e+05, 0.7, 6.8);

       
    gr2->Fit("f1");
}
