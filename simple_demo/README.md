
在本目录实现一个简单的demo:

~~~
int main() {
    return 1+2; 
}
~~~

CFG: 

function -> type funcname lpa rpa block

block -> lba stmt rba

stmt -> return expr

expr -> int op int