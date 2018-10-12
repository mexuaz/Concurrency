# Cigarette Smokers Problem (The interesting version)

The problem explanation is adopted from [The Little Book of Semaphores][book_semaphores] 

Four threads are involved: an agent and three smokers. The smokers loop forever, first waiting for ingredients, then making and smoking cigarettes. The ingredients are tobacco, paper, and matches. We assume that the agent has an infinite supply of all three ingredients, and each smoker has an infinite supply of one of the ingredients; that is, one smoker has matches, another has paper, and the third has tobacco.

The agent repeatedly chooses two different ingredients at random and makes them available to the smokers. Depending on which ingredients are chosen, the smoker with the complementary ingredient should pick up both resources and proceed.


The interesting version constrain:
* You are not allowed to modify the agent code.

## Performance evaluation
There should be always at least one smoker smoking. If the agent is fast enough it would be possible to have more than one smoker.

You can change the random sleep time within the program and verify that this is possible with this implementation





[book_semaphores]: greenteapress.com/semaphores/LittleBookOfSemaphores.pdf


