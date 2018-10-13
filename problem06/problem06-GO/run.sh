#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
for i in 1 2 4 8 16 32 64
	do 
		echo Running with spilits: $i and size: 100000000
		"$DIR/problem06-GO" $i 100000000 >> "$DIR/out.txt"
	done
