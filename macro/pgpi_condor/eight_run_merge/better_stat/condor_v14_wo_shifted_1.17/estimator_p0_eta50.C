void estimator_p0_eta50()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = {0.03580126770,0.03565956057, 0.03846565715, 0.04112455174, 0.04479774676, 0.05627967490    };// comparison for p0
    auto gr = new TGraph(n, x, y);
		auto axis1 = gr->GetXaxis();
		gr->SetTitle("estimator of p0 eta50");
	  axis1->SetTitle("leading photon pT");
		gr->GetYaxis()->SetTitle("relative error");
		gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
		axis1->SetLimits(0.1, 2.0);
        
    // paramters from signal and background plots
    float p0_1 = 1.192e+06;  
    float p1_1 = 1.73; 
    float p2_1 = 6.068;
		 
    float p0_2 = 2.692e+05; 
		float p1_2 = 0.7897;
    float p2_2 = 7.283;

    // there is 0.1*sqrt(...
    TF1 *fa = new TF1("fa", "sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 2.0);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);
    
    gr->Draw("AP");
	//	gr->GetYaxis()->SetRangeUser(0., 0.012);
    fa->Draw("same"); 

}
