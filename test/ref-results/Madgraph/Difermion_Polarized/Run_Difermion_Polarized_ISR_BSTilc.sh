#!/usr/bin/env bash
if [ -z "${KEY4HEP_STACK}" ]; then
    source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh
fi

mg5_aMC Difermion_Polarized_ISR_BSTilc.dat
gunzip Output/Events/run_01/unweighted_events.lhe.gz
ln -sf Output/Events/run_01/unweighted_events.lhe unweighted_events.lhe
sed -i '/<header>/,/<\/header>/{//!d}' unweighted_events.lhe
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i lhe -o hepmc3 unweighted_events.lhe Difermion_Polarized_ISR_BSTilc.hepmc
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i hepmc3 -o edm4hep Difermion_Polarized_ISR_BSTilc.hepmc Difermion_Polarized_ISR_BSTilc.edm4hep
analyze2f -a 13 -b -13 -i Difermion_Polarized_ISR_BSTilc.edm4hep -f Difermion_Polarized_ISR_BSTilc.root
