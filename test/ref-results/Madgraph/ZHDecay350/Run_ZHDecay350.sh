#!/usr/bin/env bash
if [ -z "${KEY4HEP_STACK}" ]; then
    source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh
fi

mg5_aMC ZHDecay350.dat
gunzip Output/Events/run_01/unweighted_events.lhe.gz
ln -sf Output/Events/run_01/unweighted_events.lhe unweighted_events.lhe
sed -i '/<header>/,/<\/header>/{//!d}' unweighted_events.lhe
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i lhe -o hepmc3 unweighted_events.lhe ZHDecay350.hepmc
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i hepmc3 -o edm4hep ZHDecay350.hepmc ZHDecay350.edm4hep
analyze2f -a 23 -b 25 -i ZHDecay350.edm4hep -f ZHDecay350.root
