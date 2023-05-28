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
mkdir build
cd build
cmake ..
make