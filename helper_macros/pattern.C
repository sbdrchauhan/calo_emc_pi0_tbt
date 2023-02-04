void pattern()
{
    TH2F *hist = new TH2F("h", "", 96,0,96, 256,0,256);
    
    for (int i=0; i<96; i++)
    {
        for (int j=0; j<256; j++)
        {
            float e = 1.00;
            int ir = -999;
            int jr = -999;
            if ( (i>=8 && i<16) || (i>=24 && i<32) || (i>=40 && i<48) ||
              (i>=56 && i<64) || (i>=72 && i<80) || (i>=88 && i<96) )
            {
                ir = i%8;
                jr = j%8;
               
                e *= 0.885+ir*0.025+jr*0.025;

            }
            else
            {
                int ib2 = i/2;
                ir = ib2%4;
                int jb2 = j/2;
                jr = jb2%8;

                e *= 0.86+ir*0.030+jr*0.030;
            }

           // e *= 0.86+ir*0.03+jr*0.03;
            hist->SetBinContent(i+1, j+1, e);
        }
    }
    hist->Draw("colz");
    //    hist->Draw("text,same");
}
    /** working basic template
    TH2F *h = new TH2F("h", "", 96, 0,96, 256, 0, 256);

    for (int i=0; i<96; i++)
    {              
        for (int j=0; j<256; j++)
        {
            int k = i/8;
            int ll = k%6;
            
            double corr = 1.0/(0.9+ll*0.02);
  
            int jj = j/16;
            if (jj%2==0)
            {
                corr *= 1.03;
            }

            h->SetBinContent(i+1, j+1, corr);
        }
    }
    h->Draw("colz");
}
*/
