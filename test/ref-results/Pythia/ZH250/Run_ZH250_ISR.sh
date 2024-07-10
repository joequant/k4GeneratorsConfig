#!/usr/bin/env bash
if [ -z "${KEY4HEP_STACK}" ]; then
    source /cvmfs/sw-nightlies.hsf.org/key4hep/setup.sh
fi

$K4GENERATORSCONFIG/pythiaRunner -f ZH250_ISR.dat
$K4GENERATORSCONFIG/convertHepMC2EDM4HEP -i hepmc3 -o edm4hep ZH250_ISR.hepmc3 ZH250_ISR.edm4hep

$K4GENERATORSCONFIG/analyze2f -a 23 -b 25 -i ZH250_ISR.edm4hep -o ZH250_ISR.root
