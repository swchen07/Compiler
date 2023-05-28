./src/build/src ./tests/Advisor/Advisor.c
gcc -no-pie Compiler.o lib/io.so -o tests/Advisor/Advisor.out
./Ref/tester/advisor/advisor-linux-amd64 ./tests/Advisor/Advisor.out #&> output.txt
# ./tests/Advisor/Advisor.out < input.txt &> output.txt
# ./tests/Advisor/Advisor.out