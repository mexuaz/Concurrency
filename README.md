# Concurrency
This is series of some famous problems in concurrency including the following 5 problem from [The Little Book of Semaphores][book_semaphores] and one of my own named Problem06.

* Dining Philosophers
* Cigarette Smokers
* FIFO Barbershop
* Santa Claus
* Search-Insert-Delete

Currently most of these problems are implemented with C++ and Go. The C++ version of implementation used conditional variables and mutex for synchronizing multi-tasks. The code utilizes most recent update by [The C++ Standards Committee - ISOCPP][ISOCPP] such as new features added to C++ in C++11/14/17. So you might need a compiler supporting at least C++17 to compile them.

The Go versions also used Go routines, Channels and Conditional Synchronizations. I tried to implement them similar to their C++ versions.

The sources have not been verified completely so there might be some minor defects. Pull requests are always welcome.


[book_semaphores]: greenteapress.com/semaphores/LittleBookOfSemaphores.pdf
[ISOCPP]: https://isocpp.org/std/the-standard
