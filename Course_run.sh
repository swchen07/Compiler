./src/build/src ./tests/CourseSelector/courseSelector.c
gcc -no-pie Compiler.o lib/io.so -o tests/CourseSelector/courseSelector.out
../tester/quicksort-linux-amd64 ./tests/CourseSelector/courseSelector.out