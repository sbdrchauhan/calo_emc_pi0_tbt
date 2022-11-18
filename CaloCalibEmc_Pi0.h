// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef CALOCALIBEMC_PI0_H
#define CALOCALIBEMC_PI0_H

#include <fun4all/SubsysReco.h>

#include <string>

class PHCompositeNode;
class TFile;
class TH1F;
class TH2F;
class TH3F;
class TH1;
class TTree;
class TString;
class TCanvas;

class CaloCalibEmc_Pi0 : public SubsysReco
{
 public:
  CaloCalibEmc_Pi0(const std::string &name = "CaloCalibEmc_Pi0", const std::string &fnm = "outJF");

  virtual ~CaloCalibEmc_Pi0() {}

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

  void Loop(int nevts, TString _filename, TTree * intree = 0, const char * ifileCorr = "");

	 void Loop_new_cuts(int nevts, TString _filename, TTree * intree = 0, const char * ifileCorr = "");


  void Fit_Histos_Etas96(const char * infilent = "");

	void Fit_Histos_Eta_Phi_Add96(const char *infilent="");

	void Fit_Histos_Eta_Phi_Add32(const char *infilent="");

  void Get_Histos(const char * infile, const char * outfile);

	void Add_32();

	void Add_96();

 private:
  int _ievent = 0;
  TFile *cal_output = nullptr;
  std::string _caloname = "CEMC";
  std::string _filename;

  // histos lists
  TH1 *cemc_hist_eta_phi[96][258];
  TH1 *eta_hist[96] = {0};
  TH2F *mass_eta = nullptr;
  TH3F *mass_eta_phi = nullptr;
	TH3F *pt1_ptpi0_alpha = nullptr;
	//TH3F *cemc_p1_eta_phi = nullptr;
	//TH2F *fitp0_eta_phi2d = nullptr;
	TH2F *fitp1_eta_phi2d = nullptr;
  TH1F *pairInvMassTotal = nullptr;

	TH1F *e1_hist_wo_alpha = nullptr;
	TH1F *e2_hist_wo_alpha = nullptr;
	TH1F *e1_hist_w_alpha = nullptr;
	TH1F *e2_hist_w_alpha = nullptr;

  TTree *_eventTree = nullptr;
  // TTree variables
  int _eventNumber = -1;
  int _nClusters = -1;
  float _clusterIDs[10000] = {0};
  float _clusterEnergies[10000] = {0};
  float _clusterPts[10000] = {0};
  float _clusterEtas[10000] = {0};
  float _clusterPhis[10000] = {0};

  int maxTowerEta = -1;
  int maxTowerPhi = -1;

  int _maxTowerEtas[10000] = {0};
  int _maxTowerPhis[10000] = {0};

  float alphaCut = -1.;
};

#endif  //   CALOCALIBEMC_PI0_H

