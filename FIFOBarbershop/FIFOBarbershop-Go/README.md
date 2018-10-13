# The FIFO Barbershop Problem

## Go version

Waiting Room (variable name: waitingRoom) is considered like a buffered channel with the capacity of 3, integers represents  customers each with a unique ID as an integer value. An interesting thing about this program is that we don't need any variable from synchronization package for multi-tasking, channels will do every thing for us.

Problem! The only thing that might be a problem is that while we are reading the channel length in main thread it is possible that the barber thread is reading from the channel at the same time, so as a result a new customer might left the barbershop without knowing that there was an empty room for one person.

Since the barber thread is only reading and the main thread only writes to the buffered channel if it is not full, we are not expecting any data races here.



Sample output for the program:

> Customer# 1  entered the barbershop.\
> Customer# 1  started the haircut.\
> Customer# 2  entered the barbershop.\
> Customer# 1  finished the haircut.\
> Customer# 1  left the barbershop after haircut.\
> Customer# 2  started the haircut.\
> Customer# 3  entered the barbershop.\
> Customer# 2  finished the haircut.\
> Customer# 2  left the barbershop after haircut.\
> Customer# 3  started the haircut.\
> Customer# 4  entered the barbershop.\
> Customer# 5  entered the barbershop.\
> Customer# 6  entered the barbershop.\
> Customer# 3  finished the haircut.\
> Customer# 3  left the barbershop after haircut.\
> Customer# 4  started the haircut.\
> Customer# 7  entered the barbershop.\
> Customer# 4  finished the haircut.\
> Customer# 4  left the barbershop after haircut.\
> Customer# 5  started the haircut.\
> Customer# 8  entered the barbershop.\
> Customer# 9  entered the barbershop.\
> Customer# 9  left the barbershop without haircut.\
> Customer# 5  finished the haircut.\
> Customer# 5  left the barbershop after haircut.\
> Customer# 6  started the haircut.\
> Customer# 10  entered the barbershop.\
> Customer# 11  entered the barbershop.\
> Customer# 11  left the barbershop without haircut.\
> Customer# 6  finished the haircut.\
> Customer# 6  left the barbershop after haircut.\
> Customer# 7  started the haircut.\
> Customer# 12  entered the barbershop.\
