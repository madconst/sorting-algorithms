Comparison of Sorting Algorithms
================================

The project includes:

* implementations of classic sorting algorithms
* a tool generating random data to test sorting
* and a bash script running all the stuff for various sizes of input data and saving results into a text file

Provided algorithms:

- system default:
  + std::sort
  + qsort()
- O(N^2) algorithms:
  + selection sort
  + insertion sort
- O(N*log(N)) algorithms:
  + quick sort
  + quick sort + insertion sort hybrid
  + quick_sort + selection sort (just for fun)
  + merge sort (iterative and recursive versions)
  + heap sort
- non-comparison sorting algorithms:
  + radix sort (base 16)
  + bucket sort

Compiling
---------

    cd build
    cmake ..
    make

Running
-------

    ./run_test.sh

This will print the testing progress to the standard output and save the results (running time in ms for each dataset size / algorithm) as a tab-separated table to `results.tsv`.

