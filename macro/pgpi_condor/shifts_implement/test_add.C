#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>

void test_add(const char *ifile="", const char *ofile="")
{
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)
	CaloCalibEmc_Pi0 obj_LCE("CaloCalibEmc_Pi0", ofile);
	obj_LCE.Get_Histos(ifile, ofile);
	obj_LCE.Add_96();

	
}
