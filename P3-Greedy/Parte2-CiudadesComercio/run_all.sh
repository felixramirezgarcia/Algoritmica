#!/bin/bash

path="datosTSP/tsp/"

array=( "a280.tsp" "att48.tsp" "bayg29.tsp" "berlin52.tsp" "ch130.tsp" "ch150.tsp" "eil51.tsp" "eil76.tsp" "eil101.tsp" "gr96.tsp" "gr120.tsp" "gr202.tsp" "gr666.tsp" "kroA100.tsp" "kroC100.tsp" "kroD100.tsp" "lin105.tsp" "pa561.tsp" "pcb442.tsp" "pr76.tsp" "pr1002.tsp" "rd100.tsp" "st70.tsp" "tsp225.tsp" "ulysses16.tsp" "ulysses22.tsp" )

for i in `seq 1 3`;
do
    for j in "${array[@]}"
    do
        touch ./soluciones/parte$i/salida-parte$i-$j.dat
        ./parte$i/parte$i $path$j >> ./soluciones/parte$i/salida-parte$i-$j.dat
        var="./soluciones/parte$i/salida-parte$i-$j.dat"
        touch ./soluciones/parte$i/graficas/salida-parte$i-$j.png
        out="./soluciones/parte$i/graficas/salida-parte$i-$j.png"
        echo "set terminal png
        set output '$out'
        plot '$var' using 2:3 title 'ruta $j' with lines, 'soluciones/parte1/salida-parte1-$j.dat' using 2:3 title 'ciudades $j' with points" | gnuplot
    done
done

# Para ejecutar el script hay que tener el siguiente arbol de directorios
# Comando de ejecucion ./script.sh

#├── datosTSP
#│   └── tsp
#│       ├── a280.tsp
#│       ├── att48.tsp
#│       ├── bayg29.tsp
#│       ├── berlin52.tsp
#│       ├── ch130.tsp
#│       ├── ch150.tsp
#│       ├── desktop.ini
#│       ├── eil101.tsp
#│       ├── eil51.tsp
#│       ├── eil76.tsp
#│       ├── gr120.tsp
#│       ├── gr202.tsp
#│       ├── gr666.tsp
#│       ├── gr96.tsp
#│       ├── kroA100.tsp
#│       ├── kroC100.tsp
#│       ├── kroD100.tsp
#│       ├── lin105.tsp
#│       ├── pa561.tsp
#│       ├── pcb442.tsp
#│       ├── pr1002.tsp
#│       ├── pr2392.tsp
#│       ├── pr76.tsp
#│       ├── rd100.tsp
#│       ├── st70.tsp
#│       ├── tsp225.tsp
#│       ├── ulysses16.tsp
#│       └── ulysses22.tsp
#├── parte1
#│   ├── parte1
#│   └── parte1.cpp
#├── parte2
#│   ├── parte2
#│   └── parte2.cpp
#├── parte3
#│   ├── parte3
#│   └── parte3.cpp
#├── script.sh
#└── soluciones
#    ├── parte1
#    │   ├── graficas
#    ├── parte2
#    │   ├── graficas
#    └── parte3
#        └── graficas