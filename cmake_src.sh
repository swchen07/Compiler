cd src
rm lexer.cp
rm paser.cpp
rm parser.hpp
rm -rf build
mkdir build
cd build
cmake ..
make