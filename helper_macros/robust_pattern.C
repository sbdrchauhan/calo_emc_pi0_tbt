void robust_pattern()
{
	TH2F *hist = new TH2F("hist","", 96,0,96,256,0,256);

	for (int ieta=0; ieta<96; ieta++)
	{
		for (int iphi=0; iphi<256; iphi++)
		{
			float e=1.00;
			int ir = -999;
			int jr = -999;

			// first 16 plain pattern
			if (ieta<16)
			{
				e *= 0.95;
			}

			// 1L1P 16x16 pattern
			else if (ieta>=16 && ieta<32
				&& iphi <16)
			{
				if (ieta>=24&&ieta<32)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}
			// 1L2P 16x16 pattern
			else if (ieta>=16 && ieta<32
				&& iphi >=64 && iphi <80)
			{
				if (ieta>=24&&ieta<32)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}
			// 1L3P 16x16 pattern
			else if (ieta>=16 && ieta<32
				&& iphi >=128 && iphi <144)
			{
				if (ieta>=24&&ieta<32)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}
			
			// 2L1P 16x16 pattern
			else if (ieta>=48 && ieta<64
				&& iphi <16)
			{
				if (ieta>=56&&ieta<64)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}
		// 2L3P 16x16 pattern
			else if (ieta>=48 && ieta<64
				&& iphi >=128 && iphi<144)
			{
				if (ieta>=56&&ieta<64)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}
	
			// 3L1P 16x16 pattern
			else if (ieta>=80 && ieta<96
				&& iphi <16)
			{
				if (ieta>=88&&ieta<96)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}

			// 3L3P 16x16 pattern
			else if (ieta>=80 && ieta<96
				&& iphi >=128 && iphi <144)
			{
				if (ieta>=88&&ieta<96)
				{
					ir = ieta%8;
					jr = iphi%8;
					e *= 0.885+ir*0.025+jr*0.025;
				}
				else
				{
					int ib2 = ieta/2;
					ir = ib2%4;
					int jb2 = iphi/2;
					jr = jb2%8;				
					e *= 0.86+ir*0.030+jr*0.030;
				}
			}






	
			else{
				// bigger JF pattern
				int ket = ieta/8;
				int llet = ket%6;
				int pket = iphi/8;
				int ppkket = pket%3;

				e *= 0.88+llet*0.04-0.01+0.01*ppkket;
			}


			hist->SetBinContent(ieta+1, iphi+1, e);
		}

	}
	hist->Draw("colz");
}
