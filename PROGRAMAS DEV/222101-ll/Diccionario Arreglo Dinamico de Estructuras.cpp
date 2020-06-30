#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   char nombre[20];
   int tipo;
   int tamanio;
   int clave;
}MetaDato;

typedef struct
{ 
   int numDatos;
   MetaDato *metaDato;
}Diccionario;

void crear(Diccionario *);
void leer(Diccionario *);
void imprime(Diccionario);

int main()
{
   Diccionario  m_diccionario;
   
   int opcion;
   
   do
   {
       system("cls");
	   printf("\n\n  M  E  N  U");
       printf("\n 1.- Crear Diccionario");
       printf("\n 2.- Leer Diccionario");
       printf("\n 3.- Imprimir Diccionario");
       printf("\n 4.- Salir\n\n"); 
       printf("Opción: ");
       scanf("%d", &opcion);
       
       switch(opcion)
       {
         case 1:  crear(&m_diccionario);
                  break;
          case 2: leer(&m_diccionario);
                  break;
          case 3: imprime(m_diccionario);
                  break;
        }
     }while(opcion!=4);
}

void crear(Diccionario *dic)
{   
    system("cls");
    printf("\n Introduzca el numero de datos del diccionario :");
    scanf("%d", &dic->numDatos);
    
    dic->metaDato = (MetaDato *) malloc(dic->numDatos * sizeof(MetaDato));
    
    printf("\nLa estructura se ha creado con exito\n\n");
    system ("pause");
}
    
void leer(Diccionario *dic)     
{
    int tipoAux, i;
    
    system("cls");
    printf("\n Introduzca los datos del diccionario...\n");
    
    for(i=0; i<dic->numDatos; i++)
    {
      printf("\n Datos del elemento %d \n", i+1);
 
      printf("Nombre: ");
      fflush(stdin);
      gets(dic->metaDato[i].nombre);
          
      printf("Tipo 0->char  1->int  2->float  3->string: ");
      scanf("%d", &tipoAux);
      
      switch(tipoAux)
      {
            case 0: dic->metaDato[i].tipo=0;
                    dic->metaDato[i].tamanio=sizeof(char);
                    break;
            case 1: dic->metaDato[i].tipo=1;
                    dic->metaDato[i].tamanio=sizeof(int);
                    break;
            case 2: dic->metaDato[i].tipo=2;
                    dic->metaDato[i].tamanio=sizeof(float);
                    break;
            case 3: dic->metaDato[i].tipo=3;
                    printf("Tamaño de la cadena: ");
                    scanf("%d", &tipoAux);
                    dic->metaDato[i].tamanio=tipoAux;
                    break;
      }
      printf("Es un campo Clave? 1->SI 0->NO: ");
      scanf ("%d", &dic->metaDato[i].clave);
    }
    printf("\n\n");
    system ("pause");
}

void imprime( Diccionario dic )
{
   int i;
   
   system("cls");
   printf("\n\n Los datos del diccionario son\n\n:");
   printf("  Nombre      Tipo  Tamañio   Clave\n");
   
   for(i=0; i<dic.numDatos; i++)
   { 
     printf("\n %d.- %s\t", i+1, dic.metaDato[i].nombre);
     printf("%d\t", dic.metaDato[i].tipo);
     printf("%d\t", dic.metaDato[i].tamanio);
     printf("%d\t", dic.metaDato[i].clave);
   }
   printf("\n\n");
   system ("pause");
}
