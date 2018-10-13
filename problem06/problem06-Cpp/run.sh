#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
for i in 1 2 4 8 16 32 64
	do 
		echo Running with spilits: $i and size: 100000000
		"$DIR/../"build-*-Release/problem06 $i 100000000 false >> "$DIR/out.txt"
	done
