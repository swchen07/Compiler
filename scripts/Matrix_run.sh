./build/zjuc ./tests/Matrix/Matrix.c
gcc -no-pie io/Matrix.o lib/io.so -o io/Matrix.out
../tester/matrix-linux-amd64 ./io/Matrix.out