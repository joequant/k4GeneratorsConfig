#!/usr/bin/env bash
source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh
Sherpa -f Run_Muon.dat
$CONVERTHEPMC2EDM4HEP/convertHepMC2EDM4HEP -i hepmc2 -o edm4hep Muon.hepmc2g Muon.edm4hep
