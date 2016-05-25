#!/bin/bash

rm log/*.txt
cd log

COUNTER=$1
while [ $COUNTER -lt $2 ]
do
	../bin/wlan $3 $COUNTER 1
	let COUNTER=COUNTER+1 
done
