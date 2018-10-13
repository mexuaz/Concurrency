# Dining Philosophers Problem

The problem explanation is adopted from [The Little Book of Semaphores][book_semaphores] 
A table with five plates, five forks (resources) and a big bowl of spaghetti (task). Five philosophers (threads), come to the table start to think and eat from spaghetti. Each philosopher needs two forks to eat, so a hungry philosopher might have to wait for a neighbor to put down a fork to eat. There is no assumption about how long eat and think take, except that eating has to terminate eventually.

The program should satisfies the following constraints:
* Only one philosopher can hold a fork at a time.**Safety (accuracy)**
* It must be impossible for a deadlock to occur: **Safety (accuracy)**
* It must be impossible for a philosopher to starve waiting for a fork: **Resource Starvation (accuracy)**
* It must be possible for more than one philosopher to eat at the same time: **Maximum possible concurrency or efficiency (performance)**.

Two solutions are implemented here:
* Multiplex solution: Do not let more than 4 philosopher to acquire the resources (forks). So the maximum number of concurrent philosopher should be 4.
* Order solution: There should be at least one philosopher that uses a different order while picking up the fork which means if all the philosophers are picking the left fork first at least one of them should pick the right one first

Both of the above solutions are implemented in C++. Also the naive implementation is included which will result in deadlock.

## Performance Evaluation

One more interesting approach I did is to consider a time duration for bowl of spaghetti. In this case each thread (philosopher) dining consumes a portion of this time. So it means if a philosopher spend 10 seconds concurrently with another philosopher on the bowl after they left the bowl 20 seconds of the bowl is consumed in a duration of 10 seconds this is kind of performance benchmark for this problem.

Also amount of time each philosopher spend on the bowl is measured so this way we could understand if there was a resource starvation or not.

Here is a sample output of the program:

> Concurrent philosophers: 4 and spaghetti left 59 secs\
> Concurrent philosophers: 4 and spaghetti left 40 secs\
> Concurrent philosophers: 4 and spaghetti left 22 secs\
> Philosopher 2 finished eating Spend 17 secs in 1 attempts on dining.\
> Philosopher 1 finished eating Spend 18 secs in 1 attempts on dining.\
> Philosopher 4 finished eating Spend 9 secs in 1 attempts on > dining.\
> Philosopher 3 finished eating Spend 14 secs in 2 attempts on dining.\
> Philosopher 0 finished eating Spend 9 secs in 1 attempts on dining.\
> The total amount of spaghetti was: 60 secs\
> The amount spend on spaghetti was: 28 secs\
> Performance: Program runs 2.14286x times faster than its sequential version.\
> Program Ended without deadlock :-)\

This is sample output for multiplex version you can see the that the bowl of spaghetti consumed more than 2 times faster. However the amount each philosopher spend on the bowl was not equal. philosopher 1 and 2 dined almost twice more than philosopher 0 and 4 which means not a good result for resource starvation.
This situation could be controlled by conditional variables as well.



[book_semaphores]: greenteapress.com/semaphores/LittleBookOfSemaphores.pdf


