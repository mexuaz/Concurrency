package main

import (
	"fmt"
	"sync"
)

func main() {

	ings := makeIngredients()

	agent := makeSupply_agent(&ings)

	var Smoker = [3]smoker{
		smoker{0, TABACCO, &ings},
		smoker{1, PAPER, &ings},
		smoker{2, MATCHES, &ings}}

	var wg sync.WaitGroup

	wg.Add(4)

	go agent.run(&wg)
	go Smoker[0].run(&wg)
	go Smoker[1].run(&wg)
	go Smoker[2].run(&wg)

	wg.Wait()

	fmt.Println("==END==")
}
