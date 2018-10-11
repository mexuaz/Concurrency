package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func main() {

	sidls := makeSIDList(rand.Perm(1e7))
	var wg sync.WaitGroup
	wg.Add(3)
	for {
		time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
		go sidls.search(rand.Intn(1e7), &wg)
		go sidls.insert(rand.Intn(1e7), &wg)
		go sidls.del(rand.Intn(1e7), &wg)
	}
	wg.Wait()

	fmt.Println("==END==")
}
