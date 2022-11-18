void total_fit()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = {0.003158972, 0.003435632, 0.003722600, 0.003864298, 0.004466335, 0.005473587};// comparison for p1
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

    // there is 0.1*sqrt(...
    TF1 *fa = new TF1("fa", "0.1*sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 2.0);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);
    
    gr->Draw("AP");
		gr->GetYaxis()->SetRangeUser(0., 0.012);
    fa->Draw("same"); 

}
