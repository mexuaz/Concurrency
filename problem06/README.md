# Problem 06

This problem is implementing a semi-parallel sort, the procedure is as follow:
1. Break the list of integers in to n portion
2. Sort each portion in a different thread
3. When all the sorts are done merge them to one list

Some parts could be done more in parallel like when at least two threads finished sorting start merging them but in order to keep the source a little more comprehensible I skip that approach.

## performance Evaluation

performance for both C++ and Go are measured by timing in milli seconds units for a list of 100,000,000 integers


| n-spilits |  C++  |   Go  |
| ----------|:-----:| -----:|
| 2         | 8464  | 27859 |
| 4         | 6344  | 19686 |
| 8         | 5965  | 17450 |
| 16        | 6708  | 18621 |
| 32        | 7486  | 21773 |

Best time for both languages was for 8 splits which I think happened because of my CPU core numbers in notebook.

If you look at the source code the Go implementation is similar to C++ one this means C++ was faster for this problem.













