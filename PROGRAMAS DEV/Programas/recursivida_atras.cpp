#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void numero(int n); 


int main()
 {
   int n=0,n2=0;      
   printf("damen un numero");
   scanf("%d",&n);
   numero(n);
   system("pause");
   return (1);
 }


void numero(int n)
 {
     if(n==0)
     {
      return;       
     }
   else  
   {
   printf("%d",n);
   printf("\n");
   numero(n-1);
   }
 }
