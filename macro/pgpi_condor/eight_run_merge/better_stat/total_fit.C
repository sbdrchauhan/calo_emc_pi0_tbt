void total_fit()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    //Double_t y[n] = {0.037073, 0.038195, 0.040179, 0.054416}; for p0
    Double_t y[n] = {0.003047709,0.003093044,0.003314233,0.003332350,0.003519108,0.004265135};// comparison for p1
    //Double_t ex[n] = {0.0};
    //Double_t ey[n] = {0.0};  //{0.050817, 0.052735, 0.062865};
    auto gr = new TGraph(n, x, y); //, ex, ey);
    auto axis = gr->GetXaxis();
    //axis->SetLimits(1.1, 1.7);
    //gr->SetTitle("Signal plot");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    //gr->Draw("AP");
    
    // paramters from signal and background plots
    float p0_1 = 5.716e+05;  //3.248e+04; // 2.515e+04;
    float p1_1 = 1.563; //-3.637e+04; // -2.655e+04;
    float p2_1 = 5.129; // 1.034e+04;

    float p0_2 = 2.577e+05; //2.333e+04; // 4.343e+04;
    float p1_2 = 0.6978;
    float p2_2 = 6.797; //-17.51;

    // there is 0.1*sqrt(...
    TF1 *fa = new TF1("fa", "0.1*sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 1.75);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);
    
    gr->Draw("AP");
    fa->Draw("same"); 

}
