#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void numero(int n,int n2); 


int main()
 {
   int n=0,n2=0;      
   printf("damen un numero");
   scanf("%d",&n);
   numero(n,n2);
   system("pause");
   return (1);
 }


void numero(int n,int n2)
 {
     if(n==n2)
     {
      return;       
     }
   else  
   {
   printf("%d",n2);
   printf("\n");
   numero(n,n2+1);
   }
 }
