#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
OUTFILE = "$DIR/out.txt"

echo "C++ version benchmark with optimization" >> $OUTFILE
for i in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384
	do 
		echo Running with spilits: $i and size: 100000000
		echo -n "$i,100000000," >> $OUTFIL
		"$DIR/../"build-*-Release/problem06 $i 100000000 false >> $OUTFIL
	done


