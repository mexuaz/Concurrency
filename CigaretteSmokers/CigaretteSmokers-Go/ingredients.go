package main

import (
	"fmt"
	"sync"
)

var mutex sync.Mutex
var cond_supply_ready = sync.NewCond(&mutex)
var cond_supply_used = sync.NewCond(&mutex)

type ingredients_t int

const (
	TABACCO ingredients_t = iota
	PAPER
	MATCHES
)

type ingredients struct {
	tabacco bool
	paper   bool
	matches bool
}

func makeIngredients() ingredients {
	return ingredients{false, false, false}
}

func (g ingredients) complete_with_internal_supply(internal_supply ingredients_t) bool {
	fmt.Println("T:", g.tabacco, ", P:", g.paper, ", M:", g.matches, ", infinit:", internal_supply)
	switch internal_supply {
	case TABACCO:
		return g.matches && g.paper
	case PAPER:
		return g.tabacco && g.matches
	case MATCHES:
		return g.tabacco && g.paper
	}
	return false
}

func (g ingredients) wait_for_complete_with_internal_supply(internal_supply ingredients_t) {
	cond_supply_ready.L.Lock()
	defer cond_supply_ready.L.Unlock()
	for !g.complete_with_internal_supply(internal_supply) {
		cond_supply_ready.Wait()
	}
}

func (g ingredients) reset() {
	mutex.Lock()
	defer mutex.Unlock()
	g.tabacco = false
	g.paper = false
	g.matches = false
	cond_supply_used.Broadcast()
}
