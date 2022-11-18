void estimator_for_p0()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = {0.0291949519965,0.0312770900844,0.0337512888062,0.0357174746637,
		0.0401856595976,0.0516123621212};// comparison for p0
    auto gr = new TGraph(n, x, y);
		auto axis1 = gr->GetXaxis();
		gr->SetTitle("");
	  axis1->SetTitle("leading photon pT");
		gr->GetYaxis()->SetTitle("relative error");
		gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
		axis1->SetLimits(0.1, 2.0);
        
    // paramters from signal and background plots
    float p0_1 = 6.674e+05;  
    float p1_1 = 1.571; 
    float p2_1 = 5.908;
		 
    float p0_2 = 2.997e+04; 
		float p1_2 = 0.5099;
    float p2_2 = 6.424;

    TF1 *fa = new TF1("fa", "sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 2.0);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2);
    
    gr->Draw("AP");
		//gr->GetYaxis()->SetRangeUser(0., 0.012);
    fa->Draw("same"); 

}

