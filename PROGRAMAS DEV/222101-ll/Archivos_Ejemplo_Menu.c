#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int puntos;
	char nombre[50];
}record;

void pide_nombre(char nom[]);
void crear_arch_bin(char nom[], int n);
void escribir_arch_bin(char nom[], int n);
void leer_arch_bin(char nom[], int n);
void crear_archivo(char nom[], int n);
void escribir_archivo(char nom[], int n);
void leer_archivo(char nom[]);

int main()
{
  int opcion, n;
  char nombre[50];
	do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Crear Archivo Binario");
		 printf("\n  2.- Guardar Archivo Binario");
		 printf("\n  3.- Leer Archivo Binario");
		 printf("\n  4.- Crear Archivo De Texto");
		 printf("\n  5.- Guardar Archivo De Texto");
		 printf("\n  6.- Leer Archivo De Texto");
		 printf("\n\n  7.- Salir");
		 printf("\n\n  Opcion: ");
		 scanf("%d",&opcion);
		 switch(opcion)
		 {
			case 1: pide_nombre(nombre);
			        crear_arch_bin(nombre, n);
			        break;
			case 2: pide_nombre(nombre);
			        printf("Numero de Arreglos: ");
                    scanf("%d", &n);
                    escribir_arch_bin(nombre, n);
			        break;
			case 3: pide_nombre(nombre);
                    leer_arch_bin(nombre, n);
                    break;
            case 4: pide_nombre(nombre);
                    printf("Numero de Arreglos: ");
                    scanf("%d", &n);
                    crear_archivo(nombre, n);
			        break;
			case 5: pide_nombre(nombre);
			        printf("Numero de Arreglos: ");
                    scanf("%d", &n);
                    escribir_archivo(nombre, n);
			        break;
			case 6: pide_nombre(nombre);
                    leer_archivo(nombre);
                    break;
         }
	}while(opcion!=7);
}

void pide_nombre(char nom[])
{
    FILE *f;
        
    system("cls");
    
    printf("Nombre del Archivo: ");
    scanf("%s", nom);
}

void crear_arch_bin(char nom[], int n)
{
     FILE *f;
     
     f=fopen(nom,"wb");
     if(f==NULL)
	 {
	   printf("\n Error de archivo.");
	   exit(1);
	 }
	 fclose(f);
}
void escribir_arch_bin(char nom[], int n)
{
    FILE *f;
    record a[n];
    int c=0, i=0;
    
    system("cls");
    f=fopen(nom, "wb");
   
    while(c<n)
    {
              printf("\n Dame Nombre: ");
              scanf("%s", a[i].nombre);
              printf("\n Dame Puntos: ");
              scanf("%d", &a[i].puntos);
              c++;
              i++;
    }
    fwrite(&a, sizeof(record), n, f);
    
    fclose(f);
}

void leer_arch_bin(char nom[], int n)
{
    FILE *f;
    record a[n];
    int c=0, i=0;
    
    system("cls");
    f=fopen(nom, "rb");
    if(f==NULL)
    {
               printf("\n Error de Archivo. \n\n");
               system("pause");
               exit(1);
    }
     
    rewind(f);
    while(!feof(f))
    {
                  fread(&a, sizeof(record)*n, 1, f);
                  if(!feof(f))
                  for(i=0;i<n;i++)
                  printf("\n El Nombre es: %s, puntos=%d   ", a[i].nombre, a[i].puntos);
    }
    
    fclose(f);
    printf("\n\n");
    system("pause");
}

void crear_archivo(char nom[], int n)
{
     FILE *f;
     
     f=fopen(nom,"w");
     if(f==NULL)
	 {
	   printf("\n Error de archivo.");
	   exit(1);
	 }
}

void escribir_archivo(char nom[], int n)
{
    FILE *f;
    record a[n];
    int c=0, i=0;
    
    system("cls");
    f=fopen(nom,"w");
    while(c<n)
    {
              printf("\n Dame Nombre: ");
              scanf("%s", a[i].nombre);
              printf("\n Dame Puntos: ");
              scanf("%d", &a[i].puntos);
              fprintf(f, "Nombre: %s, Puntos: %d\n", a[i].nombre, a[i].puntos);
              c++;
              i++;
              
    }
    
    fclose(f);
}
void leer_archivo(char nom[])
{
    FILE *f;
    char a[255];
    
    f=fopen(nom,"r");
    if(f==NULL)
    {
               printf("No se encontro el archivo\n");
               system("pause");
    }
    while(!feof(f))
    {
               fgets(a,255,f);
               printf("%s",a);
    }
    fclose(f);
    printf("\n\n");
    system("pause");
}
