void background_fit()
{
    const Int_t n = 6;

    Double_t x2[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y2[n] = {26386.5, 10781.5, 4750, 3222, 2035, 772.5};
    Double_t ex2[n] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    Double_t ey2[n] = {sqrt(y2[0]), sqrt(y2[1]), sqrt(y2[2]), sqrt(y2[3])
                      ,sqrt(y2[4]), sqrt(y2[5])};
    auto gr2 = new TGraphErrors(n, x2, y2, ex2, ey2);
    auto axis2 = gr2->GetXaxis();
    axis2->SetLimits(0., 5.);
    gr2->SetTitle("Background eta_75 Plot");
    gr2->SetMarkerColor(4);
    gr2->SetMarkerStyle(23);
    gr2->Draw("AP");

    TF1 *f1 = new TF1("f1", "[0]/([1]+x)^[2]", 0.1, 5.);

    //TF1 *mypol2 = new TF1("mypol2", "[2]+[1]*x+[0]*x*x", 0.5, 3.);
    //TF1 *mypol2 = new TF1("mypol2", "[0]*(x-[1])*(x-[1])+[2]", 0.5, 3.);
    //TF1 *mypol2 = new TF1("mypol2", "[0]*(x-[1])*(x-[1])+[2]", 0., 5.);
    //TF1 *mypol2 = new TF1("mypol2", "pol2", 0., 5.);
    
    //mypol2->SetParameter(0, 80000.);
    //mypol2->SetParameter(1, 1.75);
    //mypol2->SetParameter(2, 30);
  
    
    //mypol2->SetParLimits(1, 1.75, 1.75);
    //mypol2->SetParLimits(2, 0, 0);
    // mypol2->SetParLimits(0, 1., 2.);
   
    gr2->Fit("f1");
}
