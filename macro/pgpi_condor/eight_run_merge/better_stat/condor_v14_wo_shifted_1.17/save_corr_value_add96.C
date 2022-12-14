#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>

void save_corr_value_add96(const char* ifile = "", const char* ofile = "",const char * infilent = "")
{
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)	
	  
	CaloCalibEmc_Pi0 calo_obj("CaloCalibEmc_Pi0" /* this name goes to SubsysReco  */, ofile );
	//	calo_obj.InitRun(0); // to declare the eta_hist[96] 
	calo_obj.Get_Histos(ifile,ofile);	// open the fun4al file and Get eta_hist[96] histos
	calo_obj.Add_96();
	//calo_obj.Add_32();
	calo_obj.Fit_Histos_Eta_Phi_Add96(infilent);	// do the fittings
	calo_obj.End(0);	// save the output file
}
