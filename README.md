<a href="https://www.sphenix.bnl.gov/">
   <img src="https://github.com/sbdrchauhan/calo_emc_pi0_tbt/blob/main/images/sphenix-logo-black-bg.png" align="right" height="60" />
</a>

# sPHENIX Electromagnetic Calorimeter Calibration

[sPHENIX](https://www.sphenix.bnl.gov/) is an experiment, a collaboration of the RHIC collider located at Brookhaven National Laboratory facility in Long Island, New York. sPHENIX is primarily dedicated to studying a dense matter which is formed when two particle beams of heavy-ions collide at ultra-relativistic speeds. The dense matter created during a collision is called "Quark-Gluon Plasma". This state of matter is supposed to be formed durin the early universe. To understand the interactions of the matter at the fundamental levels is the primary goal of sPHENIX.

In order to achieve such a loafty goals, all the subsystems of the detector has to be well functioning and well calibrated. By calibration, I mean when the particles of certain energies hit one of the energy measuring detector, namely "Electromagnetic calorimeter" EMCal, it needs to read that energies correctly. As you might guess, the detectors doesn't initially record the true energies of particles energies. This is when calibration comes in.

Calibration of EMCal is done using several techniques and methods, one such method I worked on is called "**pi0 tower-by-tower method**". In this method, we use neutral pions, which decays into two photons almost immediately, as a means to calibrate the detector as they are produced in large amounts and so our statistics will be better. The idea is the EMCal detector records the two decay photons from the pi0 meson and we need to reconstruct from the decay photons into pi0 meson and calculate the invariant mass which should come equal to the true pi0 mass value. Since detector, initially, is not calibrated, it doesn't output correct energy value. Then, we calculate the ratio of the true (truth) to the output reconstructed value (reco) to find the correction value which we re-apply in the next iterations to gradually bring the reco to truth region. To completely do the calibration, we require about 6-7 iterations, and each iteration takes about 4 hours to complete. For complete documentation on how we do pi0 method calibration, please refer [here](https://www.overleaf.com/read/yxsdjvgjsbfp).


## Table of Content

- [Method](#method)
- [Process](#process)
- [Results](#results)
- [Conclusions](#conclusions)










## Method


## Process


## Results


## Conclusions

