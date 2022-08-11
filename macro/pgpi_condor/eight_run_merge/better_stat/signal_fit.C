void signal_fit()
{
    const Int_t n = 3; // number of points in our graph

    Double_t x1[n] = {1.2, 1.35, 1.65};
    Double_t y1[n] = {3498, 2227.5, 643.5};
    Double_t ex1[n] = {0.01, 0.01, 0.01};
    Double_t ey1[n] = {sqrt(y1[0]), sqrt(y1[1]), sqrt(y1[2])};
    auto gr = new TGraphErrors(n, x1, y1, ex1, ey1);
    auto axis = gr->GetXaxis();
    axis->SetLimits(0., 5.);
    gr->SetTitle("Signal Fit plot");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->Draw("AP");
    TF1 *f1 = new TF1("f1", "pol2", 0., 5.);
    gr->Fit("f1");

}
