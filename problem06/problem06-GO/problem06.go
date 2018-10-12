package main

import (
	"fmt"
	"math/rand"
	"os"
	"sort"
	"strconv"
	"sync"
	"time"
)

func mergeLists(ls1 []int, ls2 []int, dst *[]int) {

	for len(ls1) > 0 && len(ls2) > 0 {
		if ls1[0] < ls2[0] {
			*dst = append(*dst, ls1[0])
			ls1 = ls1[1:]
		} else if ls2[0] < ls1[0] {
			*dst = append(*dst, ls2[0])
			ls2 = ls2[1:]
		} else {
			*dst = append(*dst, ls1[0])
			ls1 = ls1[1:]
			ls2 = ls2[1:]
		}
	} // End of for

	if len(ls2) > 0 {
		*dst = append(*dst, ls2...)
	} else {
		*dst = append(*dst, ls1...)
	}

}

func main() {

	var nSpilit int = 4
	var sz int = 1e8

	argc := len(os.Args)

	if argc > 1 {
		nSpilit, _ = strconv.Atoi(os.Args[1])
	}

	if argc > 2 {
		sz, _ = strconv.Atoi(os.Args[2])
	}

	ilist := rand.Perm(sz) // Intitial list

	div := sz / nSpilit

	// initialization done
	start := time.Now()

	lss := make([][]int, nSpilit)

	for i := 0; i < nSpilit-1; i++ {
		lss[i] = ilist[i*div : (i+1)*div]
	}

	lss[nSpilit-1] = ilist[(nSpilit-1)*div:]

	var wg sync.WaitGroup

	for i := range lss {
		wg.Add(1)
		go func(idx int) { sort.Ints(lss[idx]); wg.Done() }(i)
	}

	wg.Wait()

	var results [][]int
	for len(lss) > 1 {
		for i := 0; i < len(lss); i += 2 {
			var t []int
			mergeLists(lss[i], lss[i+1], &t)
			results = append(results, t)
		}
		lss = nil
		lss, results = results, lss
	}

	fmt.Println(int64(time.Since(start) / time.Millisecond))

}
