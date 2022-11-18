#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>
#include "GetTChainMacro.C"

void runLCELoop(int nevents = -1, const char *ifile="", const char *ofile="",const char *incorr="")
{
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)	
	CaloCalibEmc_Pi0 obj_LCE("CaloCalibEmc_Pi0", ofile);
  obj_LCE.InitRun(0);
	TTree * intree1 =  GetTChainMacro(ifile);
  obj_LCE.Loop(nevents, ifile, intree1, incorr);
  obj_LCE.End(0);        
}
