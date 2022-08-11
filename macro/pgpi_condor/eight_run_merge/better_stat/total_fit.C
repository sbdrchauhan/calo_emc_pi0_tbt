void total_fit()
{
    const Int_t n = 3;
    Double_t x[n] = {1.2, 1.35, 1.65};
    Double_t y[n] = {0.050817, 0.052735, 0.062865};
    //Double_t ex[n] = {0.0};
    //Double_t ey[n] = {0.0};  //{0.050817, 0.052735, 0.062865};
    auto gr = new TGraph(n, x, y); //, ex, ey);
    auto axis = gr->GetXaxis();
    axis->SetLimits(1.1, 1.7);
    //gr->SetTitle("Signal plot");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    //gr->Draw("AP");
    
    float p0_1 = 2.515e+04;
    float p1_1 = -2.655e+04;
    float p2_1 = 7089;

    float p0_2 = 4.343e+04;
    float p1_2 = 1.75;
    float p2_2 = 16.87;

    TF1 *fa = new TF1("fa", "sqrt(([0]+[1]*x+[2]*x*x) + 2*([3]*(x-[4])*(x-[4])+[5]))/([0]+[1]*x+[2]*x*x)", 0.2, 1.66);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);

    fa->Draw(); 
    gr->Draw("P");

    std::cout << fa->GetMinimum(1.5, 1.7) << std::endl;
    std::cout << fa->GetMinimumX(1.5, 1.7) << std::endl;
}
