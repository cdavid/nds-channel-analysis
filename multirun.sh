#! /bin/bash

##
## Example usage:
## ./multirun.sh 8 ../../bellhop.exe
##

MAXCPU=$1;
BELLHOP=$2;
COUNTER=0;
DIRECTIONS=( "bn.bty" "be.bty" "bne.bty" "bnw.bty" "bs.bty" "bse.bty" "bsw.bty" "bw.bty");
declare -a PID
let MAX=60000;

rm -rf ./run*/
rm -rf ./output/*

while [ $COUNTER -lt $MAX ];
do
    i=0;
    while [ $i -lt 8 ]; do
	j=0;
	while [ $j -lt $MAXCPU ]; do
	    mkdir run$j
	    cp ./input/$COUNTER.env ./run$j/
	    cp ${DIRECTIONS[$i]} ./run$j/$COUNTER.bty
	    cd run$j
	    ../$BELLHOP $COUNTER &
	    PID[$j]=$!
	    echo "File $COUNTER, direction $i, CPU $j"
	    cd ..
	    let i=i+1;
	    let j=j+1;
	done
	j=0;
	while [ $j -lt $MAXCPU ]; do
	    wait ${PID[$j]}
	    mv ./run$j/$COUNTER.arr ./output/${COUNTER}_${j}.arr
	    mv ./run$j/$COUNTER.prt ./output/${COUNTER}_${j}.prt
	    rm -rf ./run$j/
	    let j=j+1;
	done
    done
    let COUNTER=COUNTER+250;
done
