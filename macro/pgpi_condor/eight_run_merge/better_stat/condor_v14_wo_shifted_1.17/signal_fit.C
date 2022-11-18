void signal_fit()
{
    auto c = new TCanvas();
    //c->SetGridy();
    c->SetLogy();

    const Int_t n = 6; // number of points in our graph

    Double_t x1[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y1[n] = {5161, 3168, 2070.5, 1679.5, 1189, 632};
    Double_t ex1[n] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    Double_t ey1[n] = {sqrt(y1[0]), sqrt(y1[1]), sqrt(y1[2]), sqrt(y1[3]),
												 sqrt(y1[4]), sqrt(y1[5])};
    auto gr = new TGraphErrors(n, x1, y1, ex1, ey1);
    auto axis1 = gr->GetXaxis();
    axis1->SetLimits(0.1, 5.);
    axis1->SetTitle("leading photon pt");
    gr->SetTitle("Signal Fit eta_75 plot");
    gr->GetYaxis()->SetTitle("log-scale");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->Draw("AP");
    //TF1 *f1 = new TF1("f1", "pol2", 0., 5.);
    TF1 *f1 = new TF1("f1", "[0]/([1]+x)^[2]", 0.1, 5.);
		// here no need to set paramters

    gr->Fit("f1");

}
