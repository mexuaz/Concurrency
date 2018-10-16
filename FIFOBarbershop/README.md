# The FIFO Barbershop Problem

The problem explanation is adopted from [The Little Book of Semaphores][book_semaphores] 
A waiting room with n chairs, and the barber room containing the barber chair. If there are no customers to be served, the barber goes to sleep. If a customer enters the barbershop and all chairs are occupied, then the customer leaves the shop. If the barber is busy, but chairs are available, then the customer sits in one of the free chairs. If the barber is asleep, the customer wakes up the barber. The waiting customers should be served in the order they arrive.

This is very interesting problem and has many application in computer you can imagine video stream processing applications. In case of real-time processing if your processing task is too slow you need to drop some frames when the buffer is full. This way you are not delayed by processing. At the same time while your processing task is working the other one is reading the video stream which saves a lot of time.

## Performance evaluation
For performance evaluation of this problem you should grantee that if there is a customer in the waiting room the barber is not asleep and at the same time if there is no one in the waiting room and the barber is asleep when some one arrives the barber immediately start to work. This may look the only possible way thinking of synchronizing with threads. However if someone tries to implement this with timers and time-out approach might not get the same performance of synchronizing tasks event though that the solution could work correctly.

## implementation
In order to implement this problem a thread safe queue has been implemented first so the barber sleeps when the queue is empty and whenever there is and enqueue to the FIFO a wake up signal is triggered.






[book_semaphores]: http://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf


