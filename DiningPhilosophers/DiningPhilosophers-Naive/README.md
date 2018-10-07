# Naive Implementation of Dining Philosophers Problem

The problem explanation is adopted from [The Little Book of Semaphores][book_semaphores] 
A table with five plates, five forks (resources) and a big bowl of spaghetti (task). Five philosophers (threads), come to the table start to think and eat from spaghetti. Each philosopher needs two forks to eat, so a hungry philosopher might have to wait for a neighbour to put down a fork to eat. There is no assumption about how long eat and think take, except that eating has to terminate eventually.

The program should satisfies the following constraints:
* Only one philosopher can hold a fork at a time.**Safety (accuracy)**
* It must be impossible for a deadlock to occur: **Safety (accuracy)**
* It must be impossible for a philosopher to starve waiting for a fork: **Resource Starvation (accuracy)**
* It must be possible for more than one philosopher to eat at the same time: **Maximum possible concurrency or efficiency (performance)**.

Deadlock is possible in this implementation


[book_semaphores]: greenteapress.com/semaphores/LittleBookOfSemaphores.pdf


