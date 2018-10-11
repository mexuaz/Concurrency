package main

import (
	"fmt"
	"math/rand"
	"sort"
	"sync"
)

func main() {

	var nSpilit int = 4
	var sz int = 40

	ilist := rand.Perm(sz) // Intitial list

	div := sz / nSpilit

	lss := make([][]int, nSpilit)

	for i := 0; i < nSpilit-1; i++ {
		lss[i] = ilist[i*div : (i+1)*div]
	}

	lss[nSpilit-1] = ilist[(nSpilit-1)*div:]

	var wg sync.WaitGroup

	for i := range lss {
		wg.Add(1)
		go func() { sort.Ints(lss[i]); wg.Done() }()
	}

	wg.Wait()

	for i := range lss {
		fmt.Println(lss[i])
	}

	fmt.Println("==END==")
}
