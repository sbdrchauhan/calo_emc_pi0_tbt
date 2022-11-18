#include <calib_emc_pi0/CaloCalibEmc_Pi0.h>
#include "GetTChainMacro.C"


void runLCELoop(int nevents = -1, const char *ifile="", const char *ofile="",const char *incorr="")
{
  //gSystem->Load("libcalibCaloEmc_pi0.so");
	R__LOAD_LIBRARY(libcalibCaloEmc_pi0.so)	
	CaloCalibEmc_Pi0 obj_LCE("CaloCalibEmc_Pi0", ofile);
  obj_LCE.InitRun(0);

	//obj_LCE.Loop(nevents,ifile,0);

	//TTree * intree1 =  get_tchain();
  TTree * intree1 =  GetTChainMacro(ifile);

	//obj_LCE.Loop(nevents,"",intree1,"rerestart1_v7v1.root");
  obj_LCE.Loop(nevents, ifile, intree1, incorr);
	
	//----	obj_LCE.End(0);
  obj_LCE.End(0);
	//obj_LCE.FittingHistos();

        
}
