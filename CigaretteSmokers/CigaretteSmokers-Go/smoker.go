package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type smoker struct {
	ID              uint64
	infinite_supply ingredients_t
	ag_supply       *ingredients
}

func makeSmoker(id uint64, inf_supp ingredients_t, ingreds *ingredients) smoker {
	fmt.Println("T:", ingreds.tabacco, ", P:", ingreds.paper, ", M:", ingreds.matches)
	return smoker{id, inf_supp, ingreds}
}

func (s smoker) make_cigarettes() {
	s.ag_supply.reset()
}

func (s smoker) smoke() {
	fmt.Println("Somker#", s.ID, " is smoking")
	time.Sleep(time.Duration(rand.Intn(2000)) * time.Millisecond)
}

func (s smoker) run(wg *sync.WaitGroup) {
	defer func() {
		if wg != nil {
			wg.Done()
		}
	}()

	for {

		//fmt.Println(s.ag_supply.complete_with_internal_supply(s.infinite_supply))
		//s.ag_supply.wait_for_complete_with_internal_supply(s.infinite_supply)
		//s.make_cigarettes()
		//s.smoke()

		cond_supply_ready.L.Lock()

		for !s.ag_supply.complete_with_internal_supply(s.infinite_supply) {
			cond_supply_ready.Wait()
		}
		cond_supply_ready.L.Unlock()
		s.make_cigarettes()
		s.smoke()
	}

}
