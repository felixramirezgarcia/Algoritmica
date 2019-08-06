#!/bin/bash

#################################################################
#									            				#
#	./macro.sh archivo inicio fin intervalo     				#
#									            				#
#	burbuja:       1000 a     25000 de     1000 en     1000     #
#   insercion:     1000 a     25000 de     1000 en     1000     #
#	floyd  :         50 a      1250 de       50 en       50     #
#	seleccion:     1000 a     25000 de     1000 en     1000		#
#	mergesort:  1000000 a  25000000 de  1000000	en  1000000		#
#	quicksort:  1000000 a  25000000 de  1000000	en  1000000		#
#	heapsort:   1000000 a  25000000 de  1000000	en  1000000		#
#									            				#
#################################################################



echo "" >> salida$1.dat

i=$2

while (( $i <= $3 )) ; do
	./$1 $i >> salida$1.dat
	let i+=$4
done
