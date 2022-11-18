void estimator_eta50_p1()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = {0.003328165, 0.003568821, 0.004103364, 0.004361431, 0.004427523, 0.005441649};// comparison for p1

    auto gr = new TGraph(n, x, y);
		auto axis1 = gr->GetXaxis();
		gr->SetTitle("estimator of p1(pi0 mean) in etabin 50");
		
	  axis1->SetTitle("photon1 pT");
		gr->GetYaxis()->SetTitle("relative statistical error");
		gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
		axis1->SetLimits(0.1, 2.0);
        
    // paramters from signal and background plots
    float p0_1 = 1.459e+07;  
    float p1_1 = 1.67; 
    float p2_1 = 7.788;
		 
    float p0_2 = 3.691e+08; 
		float p1_2 = 1.361;
    float p2_2 = 11.12;

    
    TF1 *fa = new TF1("fa", "0.104*sqrt(([0]/([1]+x)^[2]) + 2*([3]/([4]+x)^[5]))/([0]/([1]+x)^[2])", 0.2, 2.0);
    fa->SetParameters(p0_1, p1_1, p2_1, p0_2, p1_2, p2_2); //, p0_1, p1_1, p2_1);


		// resolution effect--------------
		// sigmaE/E = a/sqrt(E)+b ; with a = 13.9%, b=5.8%
		TF1 *f1 = new TF1("f1", "sqrt(0.139*0.139/x+0.058*0.058)", 0.1,3.);

		// sigma_m/m
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
		h3->Scale(0.9);
    
    gr->Draw("AP");
		gr->GetYaxis()->SetRangeUser(0., 0.012);
    fa->Draw("same");
		h3->SetMarkerStyle(kOrange);
		h3->SetMarkerStyle(6);
		h3->Draw("HIST, same"); 
}
