./src/build/src ./tests/quicksort.c
gcc -no-pie simpledemo.o lib/io.so
./a.out < input.txt &> output.txt