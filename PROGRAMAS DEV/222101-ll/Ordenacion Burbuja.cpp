#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct 
{
    char clave[5];
    char nombre[25];
    char genero;
}Persona;

void captura(Persona *p, int n);
void imprime(Persona *p, int n);
void burbujaIt(Persona *Arreglo, int numElem);

int main()
{
    Persona *p;
    int n, opcion;
    
    do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Captura");
         printf("\n  2.- Imprime");
		 printf("\n  3.- Ordena Burbuja");
		 printf("\n  4.- Salir");
		 printf("\n\n  Opci¢n: ");
		 scanf("%d",&opcion);
		 switch(opcion)
		 {
            case 1: system("cls");
                    printf("Tamaño del arreglo: ");
                    scanf("%d",&n);
                    putchar('\n');
                    p=(Persona*)malloc(sizeof(Persona) * n);
                    captura(p, n);
                    break;
          
            case 2: system("cls");
                    imprime(p, n);
    		        break;
			        
			case 3: burbujaIt(p, n);
	                break;
            }
	}while(opcion!=4);
}

void captura(Persona *p, int n)
{
   int i;

   for (i=0; i<n; i++)
   {
     printf("Clave %d: ",i+1);
     //scanf("%s",(p->clave + i));
     scanf("%s",p[i].clave);
     printf("Nombre %d: ",i+1);
     //scanf("%s",(p->nombre + i));
     scanf("%s",p[i].nombre);
     printf("Genero(M/F) %d: ",i+1);
     fflush(stdin);
     //scanf("%c",(p->genero + i));
     scanf("%c",&p[i].genero);
     putchar ('\n');
   }
}

void imprime(Persona *p, int n)
{
   int i;

   printf("\n\n");
   for (i=0; i<n; i++)
   {
     //printf("Clave %d Es = %d\n", i+1, *(p.clave + i));
     printf("Clave %d Es = %s\n", i+1, p[i].clave);
     //printf("Nombre %d Es = %s\n", i+1, *(p.nombre + i));
     printf("Nombre %d Es = %s\n", i+1, p[i].nombre);
     //printf("Genero %d Es = %c\n", i+1, *(p.genero + i));
     printf("Genero %d Es = %c\n\n", i+1, p[i].genero);
   }
   putchar('\n');
   system("pause");
}

void burbujaIt(Persona *Arreglo, int numElem)
{
    int i, it;
    Persona p;
    
    for(it =1; it < numElem; it++)
      for(i = 0; i < numElem-it; i++)
          if( strcmp(Arreglo[i].clave, Arreglo[i+1].clave ))
		  {
                  p = Arreglo[i];
                  Arreglo[i] = Arreglo[i+1];
                  Arreglo[i+1] = p;
	      }
}
