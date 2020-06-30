#include <stdio.h>
#include <stdlib.h>

void captura(char *dato, int n);
void imprime(char *dato, int n);

int main()
{
    char *dato;
    int n;
    
    printf("Teclea el tamaño del arreglo: ");
    scanf("%d",&n);
    dato=(char*)malloc(sizeof(char)*n);
    
    captura(dato, n);
    imprime(dato, n);

}

void captura(char *dato, int n)
{
   int a;

   for (a=0;a<n;a++)
   {
     printf("Teclea el Dato %d: ",a+1);
     //scanf("%c",(dato+a));
     scanf("%c",&dato[a]);
   }
}

void imprime(char *dato, int n)
{
   int a;

   printf("\n\n");
   for (a=0;a<n;a++)
   {
     //printf("El Dato %d Es = %c\n",a+1, *(dato+a));
     printf("El Dato %d Es = %c\n",a+1, dato[a]);
   }
   putchar('\n');
   system("pause");
}
