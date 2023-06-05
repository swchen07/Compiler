./build/zjuc ./tests/QuickSort/quicksort.c
gcc -no-pie io/quicksort.o lib/io.so -o io/quicksort.out
../tester/quicksort-linux-amd64 ./io/quicksort.out