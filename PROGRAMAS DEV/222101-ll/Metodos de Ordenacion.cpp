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
void burbujaRec(Persona *Arreglo, int numElem);
void seleccion(Persona *A, int N);
void insercion(Persona *A, int N);
void shell(Persona *A, int N);

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
		 printf("\n  4.- Ordena Burbuja Recursiva");
		 printf("\n  5.- Ordena Por Seleccion");
		 printf("\n  6.- Ordena Por Insercion");
		 printf("\n  7.- Ordena Por Shell");
		 printf("\n  8.- Salir");
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
            
            case 4: burbujaRec(p, n);
	                break;
            case 5: seleccion(p, n);
	                break;
            case 6: insercion(p, n);
	                break;
            case 7: shell(p, n);
	                break;
            }
	}while(opcion!=8);
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
          if( strcmp(Arreglo[i].clave, Arreglo[i+1].clave ) > 0)
		  {
                  p = Arreglo[i];
                  Arreglo[i] = Arreglo[i+1];
                  Arreglo[i+1] = p;
	      }
}

void burbujaRec(Persona *Arreglo, int numElem)
{
    int i;
    Persona p;
    
    if(numElem>1)
    {
       for(i = 0; i < numElem-1; i++)
          if( strcmp(Arreglo[i].clave, Arreglo[i+1].clave ) > 0)
		  {
                  p = Arreglo[i];
                  Arreglo[i] = Arreglo[i+1];
                  Arreglo[i+1] = p;
	      }
       burbujaRec(Arreglo, numElem-1);
    }
}

void seleccion(Persona *A, int N)
{
    int i, j, k;
    Persona MENOR;
    
    for(i=0; i<N-1; i++)
    {
      MENOR=A[i];
      k=i;
      for(j=i+1; j<N; j++)
      {
          if(strcmp(A[j].clave,MENOR.clave) < 0)
          {
             MENOR=A[j];
             k=j;
          }
      }
      A[k]=A[i];
      A[i]=MENOR;
    }
}

void insercion(Persona *A, int N)
{
    int i, j;
    Persona key;
    
    for(j=1; j<N; j++)
    {
      key=A[j];
      i=j-1;
      while(i>=0 && strcmp(A[i].clave,key.clave) > 0)
      {
         A[i+1]=A[i];        
         i=i-1;
         A[i+1]=key;
      }
    }
}

void shell(Persona *A, int N)
{
     Persona AUX;
     int INT, I, BAND=0;
     
     INT=N+1;
     
     while(INT > 1)
     {
         INT=INT/2;
         BAND=1;
         
         while(BAND == 1)      
         {
             BAND=0;
             I=0;
             
             while((I+INT)<=N)
             {
                  if((strcmp(A[I].clave,A[I+INT].clave)) > 0)            
                  {
                        AUX=A[I];  
                        A[I]=A[I+INT];
                        A[I+INT]=AUX;
                        BAND=1;
                  }
                  I=I+1;
             }      
         }
     }
}
