package main

import (
	"math/rand"
	"time"
)

type elve struct {
}

func (e elve) make_toys() {
	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
}
