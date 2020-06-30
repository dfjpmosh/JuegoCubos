#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int numero;
    char nombre[25];
    float sueldo;
}persona;

void captura(persona *empleado, int n);
void imprime(persona *empleado, int n);

int main()
{
    persona *empleado;
    int n;
    
    printf("Teclea el tamaño del arreglo: ");
    scanf("%d",&n);
    putchar('\n');
    empleado=(persona*)malloc(sizeof(persona)*n);
    
    captura(empleado, n);
    imprime(empleado, n);

}

void captura(persona *empleado, int n)
{
   int a;

   for (a=0;a<n;a++)
   {
     printf("Numero del Empleado %d: ",a+1);
     //scanf("%d",(empleado->numero + a));
     scanf("%d",&empleado[a].numero);
     printf("Nombre del Empleado %d: ",a+1);
     //scanf("%s",(empleado->nombre + a));
     scanf("%s",empleado[a].nombre);
     printf("Sueldo del Empleado %d: ",a+1);
     //scanf("%f",(empleado->sueldo + a));
     scanf("%f",&empleado[a].sueldo);
     putchar ('\n');
   }
}

void imprime(persona *empleado, int n)
{
   int a;

   printf("\n\n");
   for (a=0;a<n;a++)
   {
     //printf("Numero del Empleado %d Es = %d\n",a+1, *((empleado.numero) + a));
     printf("Numero del Empleado %d Es = %d\n",a+1, empleado[a].numero);
     //printf("El Dato %d Es = %s\n",a+1, *(empleado->nombre + a));
     printf("Nombre del Empleado %d Es = %s\n",a+1, empleado[a].nombre);
     //printf("El Dato %d Es = %.2f\n",a+1, *(empleado.sueldo+a));
     printf("Sueldo del Empleado %d Es = %.2f\n\n",a+1, empleado[a].sueldo);
   }
   putchar('\n');
   system("pause");
}
