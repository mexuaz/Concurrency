package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type supply_agent struct {
	ingreds *ingredients
}

func makeSupply_agent(ings *ingredients) supply_agent {
	return supply_agent{ings}
}

func (s supply_agent) prepare() {
	time.Sleep(time.Duration(rand.Intn(1500)) * time.Millisecond)
}

func (s supply_agent) set(tabacco bool, paper bool, matches bool) {
	cond_supply_used.L.Lock()
	defer cond_supply_used.L.Unlock()
	for func() bool { return (s.ingreds.tabacco || s.ingreds.paper || s.ingreds.matches) }() {
		cond_supply_used.Wait()
	}
	s.ingreds.tabacco = tabacco
	s.ingreds.paper = paper
	s.ingreds.matches = matches
	cond_supply_ready.Broadcast()
}

func (s supply_agent) run(wg *sync.WaitGroup) {
	defer func() {
		if wg != nil {
			wg.Done()
		}
	}()
	for {
		s.prepare()
		switch rand.Intn(3) {
		case 0:
			s.set(true, true, false)
			fmt.Println("Agent supplied: tabacco and paper")
			fmt.Println("T:", s.ingreds.tabacco, ", P:", s.ingreds.paper, ", M:", s.ingreds.matches)
		case 1:
			s.set(true, false, true)
			fmt.Println("Agent supplied: tabacco and matches")
		default:
			s.set(false, true, true)
			fmt.Println("Agent supplied: matches and paper")
		}

	}
}
