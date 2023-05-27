Use `gcc -shared -fPIC -o xxx.so xxx.c` to create dynamic lib. 
Then Compile with `gcc -no-pie simpledemo.o xxx.so`. 

gcc -shared -fPIC -o lib/io.so lib/io.c