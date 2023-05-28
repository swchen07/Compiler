./build/Compiler ./tests/QuickSort/quicksort.c
gcc -no-pie Compiler.o lib/io.so -o tests/QuickSort/quicksort.out
../tester/quicksort-linux-amd64 ./tests/QuickSort/quicksort.out