#!/usr/bin/env bash
if [ -z "${KEY4HEP_STACK}" ]; then
    source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh
fi

whizard Muon350_ISR.sin
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i hepmc3 -o edm4hep proc.hepmc Muon350_ISR.edm4hep
analyze2f -a 13 -b -13 -i Muon350_ISR.edm4hep -f Muon350_ISR.root
