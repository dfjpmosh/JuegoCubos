/*  Tutorial de Lenguaje C       Dr. Roberto Gómez 
http://homepage.cem.itesm.mx/rogomez/Tutorial-LengC/apun_fun.html
*/
#include <math.h> 
#include <stdlib.h>

int main() 
{ 
   double (*action[3])(double) = {fabs, sqrt, exp}; 
   int i; 
   double x,y; 

   x=-9; 
   printf("De un numero (0-2): "); 
   scanf("%d",&i); 
   y = (*action[i])(x); 
   printf("\n\n encontramos: %lf \n\n",y); 
   system("pause");
} 
