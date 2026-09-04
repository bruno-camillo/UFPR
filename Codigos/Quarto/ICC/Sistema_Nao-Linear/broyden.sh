#!/bin/bash

if [ $# -eq 0 ]; then
    SIZES=" 10 32 50 64 100 128 200 250 256 300 400 512 600 1000 1024 2000 2048 3000 4096"
else
    SIZES="$*"
fi

for N in ${SIZES}
do
	echo $N
 	echo "(3-2*x1)*x1-2*x2+1"
	for i in $(seq 2 $((N-1)))
	do
		echo "(3-2*x$((i)))*x$((i))-x$((i-1))-2*x$((i+1))+1"
	done
 	echo "(3-2*x$((N)))*x$((N))-x$((N-1))+1"
 	for i in $(seq 1 $N)
	do
		echo -n "-1 "
	done
 	echo -e "\n0 15\n"
done
