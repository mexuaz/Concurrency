# The Santa Claus Problem

The problem explanation is adopted from [The Little Book of Semaphores][book_semaphores] 

Santa Claus sleeps in his shop at the North Pole and can only be awakened by either:
1. All nine reindeer being back from their vacation in the South Pacific, or 
2. Some of the elves having difficulty making toys;

To allow Santa to get some sleep, the elves can only wake him when three of them have problems. When three elves are having their problems solved, any other elves wishing to visit Santa must wait for those elves to return. If Santa wakes up to find three elves waiting at his shop’s door, along with the last reindeer having come back from the tropics, Santa has decided that the elves can wait until after Christmas, because it is more important to get his sleigh ready. (It is assumed that the reindeer do not want to leave the tropics, and therefore they stay there until the last possible moment.) The last reindeer to arrive must get Santa while the others
wait in a warming hut before being harnessed to the sleigh.

The program should satisfies the following constraints:
* After the ninth reindeer arrives, Santa must invoke prepare Sleigh, and then all nine reindeer must invoke getHitched.
* After the third elf arrives, Santa must invoke helpElves. Concurrently, all three elves should invoke getHelp.
* All three elves must invoke getHelp before any additional elves enter (increment the elf counter).

## Performance Evalution

Santa Claus should not be asleep when all the deers have returned or three elves are waiting.







[book_semaphores]: greenteapress.com/semaphores/LittleBookOfSemaphores.pdf


