#!/usr/bin/env bash
if [ -z "${KEY4HEP_STACK}" ]; then
    source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh
fi

Sherpa -f MuonNeutrino350.dat
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i hepmc3 -o edm4hep MuonNeutrino350.hepmc3g MuonNeutrino350.edm4hep

$K4GENERATORSCONFIG/analyze2f -a 14 -b -14 -i MuonNeutrino350.edm4hep -f MuonNeutrino350.root
