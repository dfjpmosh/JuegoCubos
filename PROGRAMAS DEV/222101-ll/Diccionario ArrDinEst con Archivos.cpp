#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   char nombre[20];
   int tipo;
   int tam;
   int clave;
}MetaDato;

typedef struct
{ 
   int numDatos;
   MetaDato *metaDato;
}Diccionario;

void pide_nombre(char nom[]);
void crear(Diccionario *dic);
void leer(Diccionario *dic);
void imprime(Diccionario dic);
void guarda_texto(Diccionario dic, char nom[]);
void abrir_texto(Diccionario dic, char nom[]);
void guarda_bin(Diccionario dic, char nom[]);
void abrir_bin(Diccionario dic, char nom[]);
int tam_arch(char nom[]);

int main()
{
   Diccionario  m_dic;
   
   int opcion, tam_ab;
   char nom_arch[50];
   
   
   do
   {
       system("cls");
	   printf("\n\n  M  E  N  U");
       printf("\n 1.- Crear Diccionario");
       printf("\n 2.- Leer Diccionario");
       printf("\n 3.- Imprimir Diccionario");
       printf("\n 4.- Guardar Archivo de Texto");
       printf("\n 5.- Abrir Archivo de Texto");
       printf("\n 6.- Guardar Archivo Binario");
       printf("\n 7.- Abrir Archivo Binario");
       printf("\n 8.- Salir\n\n"); 
       printf("Opción: ");
       scanf("%d", &opcion);
       
       switch(opcion)
       {
         case 1:  system("cls");
                  printf("\n Introduzca el numero de datos del diccionario: ");
                  scanf("%d", &m_dic.numDatos);
                  crear(&m_dic);
                  printf("\nLa estructura se ha creado con exito\n\n");
                  system ("pause");
                  break;
          case 2: leer(&m_dic);
                  break;
          case 3: imprime(m_dic);
                  break;
          case 4: pide_nombre(nom_arch);
                  guarda_texto(m_dic, nom_arch);
                  break;
          case 5: pide_nombre(nom_arch);
                  abrir_texto(m_dic, nom_arch);
                  break;
          case 6: pide_nombre(nom_arch);
                  guarda_bin(m_dic, nom_arch);
                  break;
          case 7: pide_nombre(nom_arch);
                  tam_ab = tam_arch(nom_arch);
                  m_dic.numDatos = tam_ab;
                  abrir_bin(m_dic, nom_arch);
                  break;
        }
     }while(opcion!=8);
}

void crear(Diccionario *dic)
{       
    dic->metaDato = (MetaDato *) malloc(dic->numDatos * sizeof(MetaDato));
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
                    dic->metaDato[i].tam=sizeof(char);
                    break;
            case 1: dic->metaDato[i].tipo=1;
                    dic->metaDato[i].tam=sizeof(int);
                    break;
            case 2: dic->metaDato[i].tipo=2;
                    dic->metaDato[i].tam=sizeof(float);
                    break;
            case 3: dic->metaDato[i].tipo=3;
                    printf("Tamaño de la cadena: ");
                    scanf("%d", &tipoAux);
                    dic->metaDato[i].tam=tipoAux;
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
   printf("\n\n Los datos del diccionario son:\n\n");
   printf("  Nombre      Tipo  Tamañio   Clave\n");
   
   for(i=0; i<dic.numDatos; i++)
   { 
     printf("\n %d.- %s\t", i+1, dic.metaDato[i].nombre);
     printf("%d\t", dic.metaDato[i].tipo);
     printf("%d\t", dic.metaDato[i].tam);
     printf("%d\t", dic.metaDato[i].clave);
   }
   printf("\n\n");
   system ("pause");
}

void guarda_texto(Diccionario dic, char nom[])
{
    FILE *f;
    int c=0, i=0;
    
    system("cls");
    
    f=fopen(nom,"w");
    while(c<dic.numDatos)
    {
              fprintf(f, "Nombre %d: %s\n", i+1, dic.metaDato[i].nombre);
              fprintf(f, "Tipo %d: %d\n", i+1,dic.metaDato[i].tipo);
              fprintf(f, "Tamaño %d: %d\n", i+1,dic.metaDato[i].tam);
              fprintf(f, "Clave %d: %d\n\n", i+1,dic.metaDato[i].clave);
              c++;
              i++;
    }
    
    fclose(f);
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nom);
    system("pause");
}

void abrir_texto(Diccionario dic, char nom[])
{
    FILE *f;
    char a[500];
    
    f=fopen(nom,"r");
    printf("\n\n");
    if(f==NULL)
    {
               printf("No se encontro el archivo\n");
               system("pause");
    }
    
    rewind(f);
    while(!feof(f))
    {
              fgets(a,500,f);
              printf("%s", a);
    }
    fclose(f);
    printf("\n");
    system("pause");
}

void guarda_bin(Diccionario dic, char nom[])
{
    FILE *f;
    int c=0, i=0;
    
    system("cls");
    f=fopen(nom, "wb");
   
    fwrite(dic.metaDato, sizeof(MetaDato), dic.numDatos, f);
    
    fclose(f);
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nom);
    system("pause");
}

void abrir_bin(Diccionario dic, char nom[])
{
    FILE *f;
    int c=0, i=0;
    
    crear(&dic);
    
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
                  fread(dic.metaDato, sizeof(MetaDato), dic.numDatos, f);
                  if(!feof(f))
                  for(i=0;i<dic.numDatos;i++)
                  {
                     printf("\nCampo Numero %d\n",i+1);
                     printf("Nombre: %s\n", dic.metaDato[i].nombre);
                     printf("Tipo: %d\n", dic.metaDato[i].tipo);
                     printf("Tamaño: %d\n", dic.metaDato[i].tam);
                     printf("Clave: %d\n", dic.metaDato[i].clave);
                  }
    }
    
    fclose(f);
    printf("\n\n");
    system("pause");
}

void pide_nombre(char nom[])
{
    system("cls");
    
    printf("Nombre del Archivo: ");
    scanf("%s", nom);
}

int tam_arch(char nom[])
{
   FILE *stream;
   long curpos, length; 
   int tam_ab;
   
   stream = fopen(nom, "rb+");
   curpos = ftell(stream);  /* regresa la posición actual del apuntador */
   fseek(stream, 0L, SEEK_END); /* coloca el apuntador al final */
   length = ftell(stream);  /* regresala la posición actual de apuntador */
   fseek(stream, curpos, SEEK_SET); /*coloca apuntador en "curpos" */
   fclose(stream);
   
   tam_ab = length / sizeof(MetaDato);
   return tam_ab;
}
