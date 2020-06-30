/*   Tutorial de Lenguaje C      Dr. Roberto Gómez   ITESM  Campus Estado de México
APUNTADORES A FUNCIONES

Un apuntador a una función contiene la dirección de la función en memoria 
El nombre de la una función es realmente la direcci'on inicial en memoria del código que ejecuta la tarea de dicha función. 
Estos apuntadores pueden ser pasados a funciones, refresado de las funciones, almacenados en arreglos, y asignados a otros apuntadores de función 
Se debe tener cuidado con la declaración: 
    |                                                int * f1() 
            f1 es una función sin parámetros que regresa un apuntador a un entero 

                                                      int (*f1)() 

            f1 es un apuntador a una función sin parámetros que regresa un entero 
  

La aritmética de apuntadores no tiene sentido en los apuntadores a funciones 
Los apuntadores normales se pueden inicializar a través de otra variable del mismo tipo, (parasitaje), o por asignación de memoria, los apuntadores de funciones solo pueden inicializarse por parasitaje. 

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
