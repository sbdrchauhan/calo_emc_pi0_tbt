void get_corr2(const char *incorr="")
{
	TFile *file = new TFile(incorr, "READ");
	TH2F *hist2d = (TH2F*)file->Get("fitp1_eta_phi2d");
	TH1F *h = new TH1F("h", "", 100, 0.13, 0.14);
	
	//hist2d->Draw("colz");

	for (int ieta=0; ieta<96; ieta++)
	{
		for (int iphi=0; iphi<256; iphi++)
		{
			if (ieta>15 || iphi>15) continue;
			float mass = hist2d->GetBinContent(ieta+1, iphi+1);
			h->Fill(mass);
		}
	}
	
	h->Draw();
}
