<a href="https://www.sphenix.bnl.gov/">
   <img src="https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/images/sphenix-logo-black-bg.png" align="right" height="60" />
</a>

# sPHENIX Electromagnetic Calorimeter Calibration

## Table of Content

- [Description](#description)
- [Analysis Codes](#analysis-codes)
- [Macros](#macros)
- [Presentations](#presentations)
- [Results](#results)


## Description:

[sPHENIX](https://www.sphenix.bnl.gov/) is an experiment, a collaboration in the RHIC collider located at Brookhaven National Laboratory facility in Long Island, New York. sPHENIX is primarily dedicated to studying a dense matter which is formed when two particle beams of heavy-ions collide at ultra-relativistic speeds. The dense matter created during a collision is called "Quark-Gluon Plasma". This state of matter is supposed to be formed during the early universe. In nutshell, to understand the interactions of the matter at the fundamental levels is the primary goal of sPHENIX.

In order to achieve such a lofty goals, all the subsystems of the detector has to be well functioning and well calibrated. By calibration, I mean when the particles of certain energies hit one of the energy measuring detector, namely "Electromagnetic calorimeter" EMCal, it needs to read those particle's energies correctly. As you might guess, the detectors doesn't initially record the true energies of particle. This is when calibration task comes in.

Calibration of EMCal is done using several techniques and methods, one such method I worked on is called "**pi0 tower-by-tower method**". In this method, we use neutral pions, which decays into two photons almost immediately, as a means to calibrate the detector as they are produced in large amounts and so our statistics will be better. The idea is the EMCal detector records the two decay photons from the pi0 meson and we need to reconstruct from the decay photons into pi0 meson and calculate the invariant mass which should come equal to the true pi0 mass value. Since detector, initially, is not calibrated, it doesn't output correct energy value. Then, we calculate the ratio of the true (truth) to the output reconstructed value (reco) to find the correction value which we re-apply in the next iterations to gradually bring the reco to truth region.

To complete the calibration, we require about 6-7 iterations, and each iteration takes about 4 hours to complete. For complete documentation on how we do pi0 method calibration, please refer [here](https://www.overleaf.com/read/yxsdjvgjsbfp).

## Analysis Codes:

Codes are written in C++ and [ROOT](https://root.cern/) (usually, used by high-energy physics group) languages. A class is created which contains the methods to perform analysis on the data. Primarily, what it does is, it finds required nodes class available in the `Fun4All` framework; then gets the calorimeter nodes which has the clusters information in CEMC. Once we have the clusters information, then we can iterate on them to do our analysis i.e. make necessary cuts, make pairs, and calculate pi0 mass and then fill histograms for the later view, and further analyze the outcome results.

### Main Codes:

* [CaloCalibEmc_Pi0.cc](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/CaloCalibEmc_Pi0.cc) class implementaion
* [CaloCalibEmc_Pi0.h](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/CaloCalibEmc_Pi0.h) class declaration

## Macros:

Macros are also a C++ program that runs above class using the methods of the same class to perform specific operations.

macros:

* [Loop macro](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/macro/runLCELoop.C)
* [Saving correction values macro](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/macro/save_correc_value.C)

## Presentations:

I presented my initial results in one of the collaboration internal meetings describing how my analysis codes are working as expected.

slides:

* [August 2022](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/pi0_tbt_photon_cut_presentation.pdf)
* [September 2022](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/UPDATED_optimal%20photon%20cuts_v2_UPDATED_AFTER_PRESENTATION.pdf)
* [September 13, 2022](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/optimal%20cut%20update%203_shyam_chauhan_sphenix_caloCalibMtg.pdf)

## Results:

<hr>
<hr>

### Calibrating the EMCal (small section) towers

<hr>

With the calibration codes almost completed, the first result here shows how the initial decalibration of the small part of EMCal (16x16 parts of total 96x256 parts) can be corrected. In the iteration 0, EMCal readings are not closer to the pi0 truth value of 0.135, with the gradual itertions and applying corrections each time, the EMCal readings comes closer to the pi0 truth values. Details see [presentation](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/pi0_tbt_photon_cut_presentation.pdf) first part.

![Pi0 pattern image](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/images/pi0_patternv14.png)

<hr>
<hr>

### $\pi^0$ Photon Cuts:

<hr>

This next study aims to find the optimal $\pi^0$ photon's $p_T$ cut, which helps to stay in the best trade-off between the relative error and the background noise need to include for the analysis. Although the minimum shown here would be the best spot to choose if we want to lower our relative error during the analysis later with collected data, we can see that the relative error is not decreasing by any significant amount for us to go there and in return get lots of background noise. So, better would be to stay within $10-15\%$ of the minimum. Details in the [presentation slides](https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/UPDATED_optimal%20photon%20cuts_v2_UPDATED_AFTER_PRESENTATION.pdf).

<p align="center">
<img src="https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/images/estimator%20of%20eta%2094.png">
</p>

<hr>
<hr>

<br/>
<br/>
<br/>

>**P.S.** The codes located here is just a small part of a giant framework of codes behind the [sPHENIX official github page](https://github.com/sPHENIX-Collaboration), which contains all the codes required for all other detectors subsystems to correctly record data which are further analyzed for any physics related work.



