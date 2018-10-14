# The Santa Claus Problem

The problem explanation is adopted from [The Little Book of Semaphores][book_semaphores] 

Santa Claus sleeps in his shop at the North Pole and can only be awakened by either:
1. All nine reindeer being back from their vacation in the South Pacific, or 
2. Some of the elves having difficulty making toys;

To allow Santa to get some sleep, the elves can only wake him when three of them have problems. When three elves are having their problems solved, any other elves wishing to visit Santa must wait for those elves to return. If Santa wakes up to find three elves waiting at his shop’s door, along with the last reindeer having come back from the tropics, Santa has decided that the elves can wait until after Christmas, because it is more important to get his sleigh ready. (It is assumed that the reindeer do not want to leave the tropics, and therefore they stay there until the last possible moment.) The last reindeer to arrive must get Santa while the others
wait in a warming hut before being harnessed to the sleigh.

The program should satisfies the following constraints:
* After the ninth reindeer arrives, Santa must invoke prepare Sleigh, and then all nine reindeer must be hitched to the sleigh.
* After the third elf arrives, Santa must help Elves. Concurrently, all three elves should get help.
* All three elves must get the required help before any additional elves enter.

## Performance Evaluation

Santa Claus should not be asleep when all the deers have returned or three elves are waiting to solve their problem.

### Note on correctness:
It is impossible that nine deers and three elves want to wake up Santa at the same time. So this condition from the book does not make any sens. But to keep the conformance with the book we keep the conditional block of delivering presents before solving elves problem in the code.


## Comprehensibility

The Go version of code is implemented completely with channels and without using any synchronization, so the Go version seems to be more comprehensible since we just used 4 buffered channels with select block in Santa action but the comprehensibility achievement was with a cost. Since we have used buffered channels this implies there is a order in deers returning and going to vacation and also with elves making toys and facing problems. However the original problem do not mention such order. In C++ version since we used conditional variables such order does not exist. It was possible to implement the Go version with conditional synchronization but  then we will loose this comprehensibility.

A sample output of the program is as follow:

> Santa is asleep ...\
> Santa is waked up to deliver presents: done!\
> Santa is back to sleep ...\
> Santa is waked up to solve elves problem: done!\
> Santa is back to sleep ...\
> Santa is waked up to solve elves problem: done!\
> Santa is back to sleep ...





[book_semaphores]: http://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf


