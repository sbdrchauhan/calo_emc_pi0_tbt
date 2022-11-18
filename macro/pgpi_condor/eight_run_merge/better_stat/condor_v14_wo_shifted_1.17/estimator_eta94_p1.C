void estimator_eta94_p1()
{
    const Int_t n = 6;
    Double_t x[n] = {0.7, 0.9, 1.1, 1.2, 1.35, 1.65};
    Double_t y[n] = { 0.004639508, 0.005012354, 0.005435237, 0.005422753,0.006542580, 0.008561023   };// comparison for p1
    auto gr = new TGraph(n, x, y);
		auto axis1 = gr->GetXaxis();
		gr->SetTitle("estimator of p1 eta94");
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
