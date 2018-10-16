package main

import (
	"math/rand"
	"time"
)

type deer struct {
}

func (d deer) vacation() {
	time.Sleep(time.Duration(rand.Intn(2000)) * time.Millisecond)
}
