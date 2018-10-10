package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var numConcurrentSearches uint64 = 0
var numConcurrentInsertes uint64 = 0
var numConcurrentDels uint64 = 0

var mutex = sync.Mutex{}
var cond = sync.NewCond(&mutex)

type SIDList struct {
	list []int
}

func makeSIDList(list []int) SIDList {
	return SIDList{list}
}

func (e SIDList) search(value int, wg *sync.WaitGroup) int {
	if wg != nil {
		defer wg.Done()
	}
	cond.L.Lock()
	for numConcurrentDels > 0 {
		cond.Wait()
	}
	numConcurrentSearches++
	e.print_status()
	cond.L.Unlock()
	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
	for i := range e.list {
		if e.list[i] == value {
			cond.L.Lock()
			numConcurrentSearches--
			cond.L.Unlock()
			cond.Broadcast()
			return i
		}
	}
	cond.L.Lock()
	numConcurrentSearches--
	cond.L.Unlock()
	cond.Broadcast()
	return -1
}

func (e SIDList) insert(value int, wg *sync.WaitGroup) {
	if wg != nil {
		defer wg.Done()
	}
	cond.L.Lock()
	for numConcurrentDels > 0 || numConcurrentInsertes > 0 {
		cond.Wait()
	}
	numConcurrentInsertes++
	e.print_status()
	cond.L.Unlock()
	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
	e.list = append(e.list, value)
	cond.L.Lock()
	numConcurrentInsertes--
	cond.L.Unlock()
	cond.Broadcast()
}

func (e SIDList) del(idx int, wg *sync.WaitGroup) bool {
	if wg != nil {
		defer wg.Done()
	}
	if idx > len(e.list) {
		return false
	}
	cond.L.Lock()
	for numConcurrentDels > 0 ||
		numConcurrentInsertes > 0 ||
		numConcurrentSearches > 0 {
		cond.Wait()
	}
	numConcurrentDels++
	e.print_status()
	cond.L.Unlock()
	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
	//e.list = append(e.list[:idx], e.list[idx+1:]...)
	cond.L.Lock()
	numConcurrentDels--
	cond.L.Unlock()
	cond.Broadcast()
	return true
}

func (e SIDList) empty() bool {
	return len(e.list) == 0
}

func (e SIDList) print_status() {

	fmt.Print("Searches: ", numConcurrentSearches,
		", Inserts: ", numConcurrentInsertes,
		", Deletes: ", numConcurrentDels)

	if numConcurrentDels > 0 && (numConcurrentSearches > 0 || numConcurrentInsertes > 0) {

		fmt.Println("\n--Error Caught--")
	}

	if numConcurrentInsertes > 1 {
		fmt.Println("\n--Error Caught--")
	}

	if numConcurrentSearches > 1 && numConcurrentInsertes == 1 {
		fmt.Println("\n**We are good (just to make sure things like this happens)**")
	}

	if numConcurrentDels == 1 {
		fmt.Println("\n**We are good (just to make sure things like this happens)**")
	}

	fmt.Print("\r")
}
