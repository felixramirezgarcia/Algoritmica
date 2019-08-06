#!/bin/bash

touch salida$1.dat

i=$2

while (( $i <= $3 )) ; do
	./$1 $i >> salida$1.dat
	let i+=$4
done
