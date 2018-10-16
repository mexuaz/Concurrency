package main

import (
	"fmt"
	"math/rand"
	"time"
)

type santa struct {
}

func makeSanta() santa {
	return santa{}
}

func (s santa) deliver_presents() {
	fmt.Println("Santa is delivering the presents")
	time.Sleep(time.Duration(rand.Intn(2000)) * time.Millisecond)
}

func (s santa) solve_problems() {
	fmt.Println("Santa is solving the problems")
	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)
}

func (s santa) run() {

	var deers []deer
	var elves []elve

	for {
		for len(deers) < 9 && len(elves) < 3 {
			select {
			case d := <-deers_returned:
				deers = append(deers, d)
			case e := <-elves_with_problems:
				elves = append(elves, e)
			}
		}

		if len(deers) == 9 {
			s.deliver_presents()

			for _, d := range deers {
				deers_on_vacation <- d
			}
			deers = deers[:0]
		}

		if len(elves) == 3 {
			s.solve_problems()

			for _, e := range elves {
				elves_making_toys <- e
			}
			elves = elves[:0]
		}
	}

}
