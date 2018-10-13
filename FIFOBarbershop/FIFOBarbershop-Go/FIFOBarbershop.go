package main

import (
	"fmt"
	"math/rand"
	"time"
)

func barber(waitingRoom <-chan int) {
	for {
		Customer := <-waitingRoom
		fmt.Println("Customer#", Customer, " started the haircut.")
		time.Sleep(time.Duration(rand.Intn(2500)) * time.Millisecond)
		fmt.Println("Customer#", Customer, " finished the haircut.")
		fmt.Println("Customer#", Customer, " left the barbershop after haircut.")
	}
}

func main() {

	waitingRoom := make(chan int, 3)

	var Customer int = 0

	go barber(waitingRoom)

	for {
		Customer++
		fmt.Println("Customer#", Customer, " entered the barbershop.")

		if len(waitingRoom) < 3 {
			waitingRoom <- Customer
		} else {
			fmt.Println("Customer#", Customer, " left the barbershop without haircut.")
		}
		time.Sleep(time.Duration(rand.Intn(2000)) * time.Millisecond)
	}

}
