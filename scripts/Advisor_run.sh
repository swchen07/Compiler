./build/zjuc ./tests/Advisor/Advisor.c
gcc -no-pie io/Advisor.o lib/io.so -o io/Advisor.out
../tester/advisor-linux-amd64 ./io/Advisor.out