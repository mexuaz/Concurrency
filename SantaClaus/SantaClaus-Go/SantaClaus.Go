package main

import (
	"fmt"
)

var elves_with_problems = make(chan elve, 3)
var deers_returned = make(chan deer, 9)
var elves_making_toys = make(chan elve, 7)
var deers_on_vacation = make(chan deer, 9)

var santa_retired chan bool

func deer_task(d deer) {
	for {
		d.vacation()
		deers_returned <- d
		d = <-deers_on_vacation
	}
}

func elve_task(e elve) {
	for {
		e.make_toys()
		elves_with_problems <- e
		e = <-elves_making_toys
	}
}

func main() {

	var deers [9]deer

	for _, d := range deers {
		go deer_task(d)
	}

	var elves [10]elve

	for _, e := range elves {
		go elve_task(e)
	}

	santa := makeSanta()

	go santa.run()

	<-santa_retired

	fmt.Println("==END==")
}
