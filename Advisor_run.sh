./src/build/src ./tests/Advisor/Advisor.c
gcc -no-pie Compiler.o lib/io.so -o tests/Advisor/Advisor.out
# ../tester/advisor-linux-amd64 ./tests/Advisor/Advisor.out
./tests/Advisor/Advisor.out < input.txt &> output.txt
# ./tests/Advisor/Advisor.out