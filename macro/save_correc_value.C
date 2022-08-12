#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>
void save_correc_value(const char* ifile = "out_xg_combined_v1_g4cemc_eval.root", const char* ofile = "correc_values.root")
{
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)	

	CaloCalibEmc_Pi0 calo_obj("CaloCalibEmc_Pi0" /* this name goes to SubsysReco  */, ofile );
	calo_obj.InitRun(0); // to declare the eta_hist[96] 
	calo_obj.Get_Histos(ifile);	// open the fun4al file and Get eta_hist[96] histos
	calo_obj.Fit_Histos();	// do the fittings
	calo_obj.End(0);	// save the output file
}
