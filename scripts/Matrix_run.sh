./build/Compiler ./tests/Matrix/Matrix.c
gcc -no-pie Compiler.o lib/io.so -o tests/Matrix/Matrix.out
../tester/matrix-linux-amd64 ./tests/Matrix/Matrix.out