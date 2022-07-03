#include<stdio.h>

int fac(int n) __attribute__((noinline));


void main()  
{  
  int number = 10;  
  int fact;
   
   
  fact = fac(number); 
  //printf("%d\n", fact);
  
}

int fac(int n)  
{  
  if (n == 0)  
    return 1;  
  else  
    return(n * fac(n-1));  
}  
   
   //0x375F00