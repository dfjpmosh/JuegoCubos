#include <stdio.h>
#include <stdlib.h>

void captura(int *dato, int n);
void imprime(int *dato, int n);

int main()
{
    int *dato;
    int n;
    
    printf("Teclea el tamaño del arreglo: ");
    scanf("%d",&n);
    dato=(int*)malloc(sizeof(int)*n);
    
    captura(dato, n);
    imprime(dato, n);

}

void captura(int *dato, int n)
{
   int a;

   for (a=0;a<n;a++)
   {
     printf("teclea el valor %d: ",a+1);
     scanf("%d",(dato+a));
   }
}

void imprime(int *dato, int n)
{
   int a;

   printf("\n\n");
   for (a=0;a<n;a++)
   {
     printf("El valor %d Es = %d\n",a+1, *(dato+a));
   }
   putchar('\n');
   system("pause");
}
