./build/zjuc ./tests/MicroDef/MicroDef.c
gcc -no-pie io/MicroDef.o lib/io.so -o io/MicroDef.out
../tester/quicksort-linux-amd64 ./io/MicroDef.out