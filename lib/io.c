// printk and scank lib

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void scank(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;

            switch (*format) {
                case 'd': {
                    int* value = va_arg(args, int*);
                    scanf("%d", value);
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char*);
                    scanf("%s", value);
                    break;
                }
                case 'c': {
                    char* value = va_arg(args, char*);
                    scanf("%c", value);
                    break; 
                }
                default:
                    break;
            }
        }

        format++;
    }

    va_end(args);
}

void printk(const char* format, ...) {
    va_list args;
    va_start(args, format);
    // printf(format);

    while (*format != '\0') {
        if (*format == '%') {
            char formats[10];
            int index = 0;
            int loop = 1; 
            formats[0] = '%'; 

            while (loop){
                format++;
                index++;
                formats[index] = *format; 
                formats[index+1] = '\0';

                switch (*format) {
                    case 'd': {
                        int value = va_arg(args, int);
                        printf(formats, value);
						loop = 0;
                        break;
                    }
                    case 's': {
                        char* value = va_arg(args, char*);
                        printf(formats, value);
						loop = 0;
                        break;
                    }
                    case 'c': {
                        int value = va_arg(args, int);
                        printf(formats, value);
						loop = 0;
                        break; 
                    }
                    default:
                        if (!(*format >= '0' && *format <= '9')) {
                            loop = 0; 
                            putchar(*format);
                        }
                        
                        break;
                }
                if (!loop) break;
            }
        } else {
            putchar(*format);
        }

        format++;
    }

    va_end(args);
}

// void printInt(int addr, int a){
//     printf((char*)(long int)addr, a);
// }

// void printStr(int addr, int a){
//     printf((char*)(long int)addr, (char*)a);
// }

// void printDouble(int addr, double a){
//     printf((char*)(long int)addr, a);
// }

// void scanInt(int addr, int a){
//     scanf((char*)(long int)addr, (int*)(long int)a);
// }

// void scanStr(int addr, int a){
//     scanf((char*)(long int)addr, (char*)a);
// }

// void scanDouble(int addr, int a){
//     scanf((char*)(long int)addr, (double*)(long int)a);
// }

// int printk(int format, ...); 
// int scank(int format, ...); 
// static void Ita(char * pStr, int nNum);
// static char * Itoa(char * pStr, int rInt);
// static void GetString(char * pStr); 
// static int Atoi(char * pStr); 

// int printk(int format, ...) { 
//     char * pFormat = (char*)(long int)format;
//     if(pFormat != NULL) { 
//         int * pMove = (int *)(&pFormat + 1); 
//         char SzBuff[512] = ""; 
//         char * pSzBuff = SzBuff; 
//         while(*pFormat != '\0') { 
//             if(*pFormat == '%' ) { 
//                 ++pFormat; 
//                 switch(*pFormat) { 
//                     case 'a': { 
//                         *pSzBuff++ = *((char *)pMove++); 
//                         break; 
//                         } 
//                     case 's': { 
//                         for(char * pTemp = (char *)(*pMove++); '\0' != (*pSzBuff++ = *pTemp++);); 
//                         --pSzBuff; 
//                         break; 
//                         } 
//                     case 'd': { 
//                         char Szbuff[32] = ""; 
//                         Itoa(Szbuff, *pMove++); 
//                         char * pTemp = Szbuff; 
//                         while(*pTemp != '\0') { 
//                             *pSzBuff++ = *pTemp++; 
//                         } 
//                         break; 
//                         } 
//                     case '%': { 
//                         *pSzBuff++ = '%'; 
//                         } 
//                     default: { 
//                         *pSzBuff++ = *pFormat; 
//                         break; 
//                         } 
//                 } 
//             } 
//             else { 
//                 *pSzBuff++ = *pFormat; 
//             } 
//             ++pFormat; 
//         } 
//         pSzBuff = SzBuff; 
//         while(*pSzBuff != '\0') { 
//             putchar(*pSzBuff++); 
//         } 
//         return 0; 
//     } 
//     return -1; 
// } 

// static void Ita(char * pStr, int nNum) { 
//     // static char * pTemp; 
//     // pTemp =pStr; 
//     if(nNum > 0) { 
//         Ita(pStr, nNum / 10); 
//         *pStr++ = nNum % 10 + '0'; 
//     } 
//     *pStr = '\0'; 
// } 

// static char * Itoa(char * pStr, int rInt) { 
//     if(rInt == 0) { 
//         *pStr++ = '0'; 
//         *pStr = '\0'; 
//     } 
//     else if(rInt > 0) { 
//         Ita(pStr, rInt); 
//     } 
//     else { 
//         *pStr = '-'; 
//         Ita(pStr + 1, -rInt); 
//     } 
//     return pStr; 
// }

// int scank(int format, ...) { 
//     char * pFormat = (char*)(long int)format;
//     if(pFormat != NULL) { 
//         int * pMove = (int *)(&pFormat + 1); 
//         while('\0' != *pFormat) { 
//             if('%' == *pFormat) { 
//                 ++pFormat; 
//                 switch(*pFormat) { 
//                     case 'a': { **((char **)pMove++) = getchar(); break; } 
//                     case 'd': { char Szbuff[32] = ""; GetString(Szbuff); **((int **)pMove++) = Atoi(Szbuff); break; } 
//                     case 's': { 
//                         char Szbuff[128] = ""; 
//                         GetString(Szbuff); 
//                         char * pRcs = Szbuff; 
//                         char * pTemp = (char *)(*pMove++); 
//                         while('\0' != (*pTemp++ = *pRcs++)); 
//                         break; 
//                     } 
//                     default: { ++pFormat; break; } 
//                 } 
//             } 
//             ++pFormat; 
//         } 
//         return 0; 
//     } 
//     return -1; 
// } 

// static void GetString(char * pStr) { 
//     if(pStr != NULL) { 
//         char ch = ' '; 
//         while('\n' == ch || ' ' == ch) { 
//             ch = getchar(); 
//         } 
//         *pStr++ = ch; 
//         ch = getchar(); 
//         while(ch != '\n' && ch != ' ') { 
//             *pStr++ = ch; 
//             ch = getchar(); 
//         } 
//         *pStr = '\0'; 
//     } 
// } 

// static int Atoi(char * pStr) { 
//     int nSum = 0; 
//     int Is_Negative = 0; 
//     if(pStr != NULL) { 
//         if(*pStr == '-') { 
//             Is_Negative = 1; 
//             ++pStr; 
//         } 
//         while(*pStr != NULL) { 
//             nSum = nSum * 10 + *pStr - '0'; 
//             ++pStr; 
//         } 
//     } 
    
//     if(Is_Negative) { 
//         return -nSum; 
//     } 
//     else { 
//         return nSum; 
//     } 
// }
