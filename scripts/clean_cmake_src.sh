if [ -f ./src/lexer.cpp ]
then
	rm lexer.cpp
fi
if [ -f ./src/parser.cpp ]
then
	rm parser.cpp
fi
if [ -f ./src/parser.cpp ]
then
	rm parser.hpp
fi
rm -rf build
cd ..

if [ -f ./Compiler.o ]
then
	rm Compiler.o
fi
if [ -f ./tests/Matrix/matrix.out ]
then
	rm ./tests/Matrix/matrix.out
fi
if [ -f ./tests/QuickSort/quickSort.out ]
then
	rm ./tests/QuickSort/quickSort.out
fi