#include <stdio.h>
#include <stdarg.h>

void printk(int addr, int a){
    va_list valist; 
    printf((char*)addr, a);
}