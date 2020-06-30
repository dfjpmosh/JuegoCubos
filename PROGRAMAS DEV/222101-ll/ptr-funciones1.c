/*   Tutorial de Lenguaje C      Dr. Roberto G�mez   ITESM  Campus Estado de M�xico
APUNTADORES A FUNCIONES

Un apuntador a una funci�n contiene la direcci�n de la funci�n en memoria 
El nombre de la una funci�n es realmente la direcci'on inicial en memoria del c�digo que ejecuta la tarea de dicha funci�n. 
Estos apuntadores pueden ser pasados a funciones, refresado de las funciones, almacenados en arreglos, y asignados a otros apuntadores de funci�n 
Se debe tener cuidado con la declaraci�n: 
    |                                                int * f1() 
            f1 es una funci�n sin par�metros que regresa un apuntador a un entero 

                                                      int (*f1)() 

            f1 es un apuntador a una funci�n sin par�metros que regresa un entero 
  

La aritm�tica de apuntadores no tiene sentido en los apuntadores a funciones 
Los apuntadores normales se pueden inicializar a trav�s de otra variable del mismo tipo, (parasitaje), o por asignaci�n de memoria, los apuntadores de funciones solo pueden inicializarse por parasitaje. 

*/

#include <stdio.h>
#include <stdlib.h>
int f(); 
int main() 
{ 
     int (*p)(); 
     int i = 1; 
     p = f; /* parasitaje: p apunta hacia f */ 
     //p = f(); /* INVALIDO */ 
     i = p(); /* aplicando operador llamada() a p */ 
     printf("i = %d, llamando i=p()\n",i);
     i = 10;
     i = f(); /* aplicando opreador llamada() a f */
     printf("i = %d, llamando i=f()\n",i);      
     i = 20;
     i = (*p)(); /* equivalente a i=f() */      
     printf("i = %d, llamando i=(*p)()\n",i);
     system("pause");
} 

int f()
{
 return 5;   
}     
