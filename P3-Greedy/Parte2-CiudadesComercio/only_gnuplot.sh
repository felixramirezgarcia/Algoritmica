#!/bin/bash

array=( "a280.tsp" "att48.tsp" "bayg29.tsp" "berlin52.tsp" "ch130.tsp" "ch150.tsp" "eil51.tsp" "eil76.tsp" "eil101.tsp" "gr96.tsp" "gr120.tsp" "gr202.tsp" "gr666.tsp" "kroA100.tsp" "kroC100.tsp" "kroD100.tsp" "lin105.tsp" "pa561.tsp" "pcb442.tsp" "pr76.tsp" "pr1002.tsp" "rd100.tsp" "st70.tsp" "tsp225.tsp" "ulysses16.tsp" "ulysses22.tsp" )


for j in "${array[@]}"
do
    gnuplot -e "plot 'soluciones/parte1/salida-parte1-$j.dat' using 2:3 title 'ruta $j' with lines, 'soluciones/parte1/salida-parte1-$j.dat' using 2:3 title 'ciudades $j' with points; pause -1;"
done
