# Problem 06

This problem is implementing a semi-parallel sort, the procedure is as follow:
1. Break the list of integers in to n portion
2. Sort each portion in a different thread
3. When all the sorts are done merge them to one list

Some parts could be done more in parallel like when at least two threads finished sorting start merging them but in order to keep the source a little more comprehensible I skip that approach.

## Performance Evaluation

Performance for both C++ and Go are measured by timing. The timing results are in milli-seconds for a vector of 100,000,000 integers. I used std::vector for C++ and Slice for Golang. The generated binary file using Go Standard compiler is optimized by default and Go doesn't have different level of optimization[(Golang Compiler)][golang_compiler]. In fact if you want to disable optimization you should use -N flag, instead of that the C++ version measured in different level of optimization. I used an [Asus N43JQ][ausus_n43jq_specs] equipped to an Intel Core i7 (8 cores) with 8 GB of after market RAM installed on it for this benchmark.



| Splits  |   C++ O  |   C++ O1 |   C++ O2  |  C++ O3  |   Go  |
|:-------:|:--------:|:--------:|:---------:|:--------:|:-----:|
| 1       |  11426   |   11440  |   11687   |   12643  | 40006 |
| 2       |  7423    |   7501   |    7320   |   7717   | 26081 |
| 4       |  5926    |   5954   |    5618   |   5899   | 19637 |
| 8       |  5089    |   5142   |    4681   |   4806   | 16727 |
| 16      |  5897    |   5883   |    5302   |   5656   | 18036 |
| 32      |  6689    |   6701   |    5963   |   6099   | 18990 |
| 64      |  7471    |   7480   |    6594   |   6751   | 20407 |
| 128     |  8302    |   8329   |    7244   |   7425   |  |
| 256     |  9088    |   9099   |    7908   |   8104   |  |
| 512     |  9891    |   9942   |    8531   |   8770   |  |
| 1024    |  10748   |  10723   |    9274   |   9405   |  |
| 2046    |  11482   |  11465   |    9803   |   10044  |  |
| 4096    |  12399   |  12437   |   10575   |   10850  |  |
| 8192    |  13340   |  13345   |   11365   |   11663  |  |
| 16382   |  14347   |  14608   |   12221   |   12506  |  |

 

## Observations:

* Best time for both languages was for 8 splits which I think this happened because of my notebook has 8 Cores in CPU. 

* The best time achived for C++ was in L2 Optimization 4681 and for Go was 16727. The best result of C++ was 3.6 times faster than Go.

* Increasing number of threads affected C++ program more than Go, this could be happened because Go threads are lighter than C++.

* The interesting fact is that C++ sequential version (1 split) is faster than Go's best result for 8 split!

* Optimization doesn't contribute much to C++ except in case of increased thread numbers.

* Multi-threading improved C++ time in best case 2.5 times and Go 2.4 times


If you look at the source code the Go implementation is similar to C++ one this means C++ was faster for this problem.






[golang_compiler]: https://golang.org/cmd/compile/
[ausus_n43jq_specs]: https://www.asus.com/Laptops/N43JQ/specifications/





