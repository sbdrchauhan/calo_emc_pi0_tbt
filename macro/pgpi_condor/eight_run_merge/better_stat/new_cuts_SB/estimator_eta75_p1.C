void estimator_eta75_p1()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = {0.002819863, 0.003053672, 0.003383454, 0.003455579, 0.003775109, 0.004716594};// comparison for p1

    auto gr = new TGraph(n, x, y);
		auto axis1 = gr->GetXaxis();
		gr->SetTitle("estimator of p1(pi0 mean) in etabin 75");
		
	  axis1->SetTitle("photon1 pT");
		gr->GetYaxis()->SetTitle("relative error");
		gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
		axis1->SetLimits(0.1, 2.0);
        
    // paramters from signal and background plots
    float p0_1 = 1.244e+06;  
    float p1_1 = 1.287; 
    float p2_1 = 6.446;
		 
    float p0_2 = 2.437e+07; 
		float p1_2 = 1.063;
    float p2_2 = 10.33;

    
    TF1 *fa = new TF1("fa", "0.104*sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 2.0);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);


		// resolution effect--------------
		TF1 *f1 = new TF1("f1", "sqrt(0.139*0.139/x+0.058*0.058)", 0.1,3.);
		TH1F *h2 = new TH1F("h2", "", 300, 0, 3);
		for (int i=10; i<300; i++)
		{
			if (i>60)
				h2->SetBinContent(i+1, sqrt(  0.25*f1->Eval(TMath::Max(0.6, 1.0/3.0*i*0.01))*
            f1->Eval(TMath::Max(0.6, 1.0/3.0*i*0.01)) +  0.25*f1->Eval(i*0.01)*
            f1->Eval(i*0.01)));
			else
				h2->SetBinContent(i+1, sqrt(2)*0.5*f1->Eval(i*0.01));
		}
		// ------------------------
		
		TH1F *h3 = new TH1F("h3", "", 300, 0, 3);
		for (int i=0; i<300; i++)
		{
			h3->SetBinContent( i+1, fa->Eval(i*0.01)*h2->GetBinContent(i+1)/0.1 );
		}
    
    gr->Draw("AP");
		gr->GetYaxis()->SetRangeUser(0., 0.012);
		f1->Draw("same");
    fa->Draw("same");
		h3->SetMarkerStyle(kOrange);
		h3->SetMarkerStyle(6);
		h3->Draw("P, same"); 
}
