./src/build/src ./tests/QuickSort/quicksort.c
gcc -no-pie Compiler.o lib/io.so -o tests/QuickSort/quickSort.out
./Ref/tester/quicksort/quicksort-linux-amd64 ./tests/QuickSort/quickSort.out