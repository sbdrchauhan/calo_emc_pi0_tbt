void estimator_eta94_p0()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = {0.0485990637130, 0.0519132815977,0.0555083073228,
		0.0562190781908, 0.0643637807196, 0.0754742739772 	  };// comparison for p0
    auto gr = new TGraph(n, x, y);
		auto axis1 = gr->GetXaxis();
		gr->SetTitle("estimator of p0 eta94");
	  axis1->SetTitle("leading photon pT");
		gr->GetYaxis()->SetTitle("relative error");
		gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
		axis1->SetLimits(0.1, 2.0);
        
    // paramters from signal and background plots
    float p0_1 = 4.834e+04;  
    float p1_1 = 1.326; 
    float p2_1 = 4.733;
		 
    float p0_2 = 4170; 
		float p1_2 = 0.3858;
    float p2_2 = 5.609;

    TF1 *fa = new TF1("fa", "sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 2.0);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);
    
    gr->Draw("AP");
		//gr->GetYaxis()->SetRangeUser(0., 0.012);
    fa->Draw("same"); 

}
