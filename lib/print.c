#include <stdio.h>
#include <stdarg.h>

void printk(int addr, ...){
    va_list valist; 
    printf((char*)addr, valist);
}