#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct
{
  int numDatos;
  void *datos;
  int tam;
}Datos;

typedef struct
{
  int noDatos;
  void *arreglo;
  int tam;
}TDatos;

void pide_nombre(char nom[]);
void crear(Diccionario *dic);
void leer(Diccionario *dic);
void imprime(Diccionario dic);
void guarda_texto(Diccionario dic, char nom[]);
void abrir_texto(Diccionario *dic, char nom[]);
void guarda_bin(Diccionario dic, char nom[]);
void abrir_bin(Diccionario *dic, char nom[]);
void capturaDatos(Diccionario d, Datos *dat);
int tamRegistro(Diccionario d);
void capturaRegistro(Diccionario d, void *dir);
void imprimeDatos(Diccionario d, Datos dat);
void imprimeRegistro(Diccionario d, void *dir);
int tamArch(char nom[]);
void guarda_archivo(Diccionario dic, char nom[]);
void abrir_archivo(Diccionario *dic, char nom[]);
void guarda_datos_txt(Diccionario dic, char nom[], char nomdat[], Datos dat);
void abrir_datos_txt(Diccionario *dic, char nom[], char nomdat[], Datos *dat);
void guarda_datos_bin(Diccionario dic, char nom[], char nomdat[], Datos dat);
void abrir_datos_bin(Diccionario *dic, char nom[], char nomdat[], Datos *dat);
void guarda_archivo_datos(Diccionario dic, char nom[], char nomdat[], Datos dat);
void abrir_archivo_datos(Diccionario *dic, char nom[], char nomdat[], Datos *dat);
void guarda_claves(Diccionario d, Datos dat);
void generarArr(Diccionario d, Datos dat, char id[], TDatos *datos);

int main()
{
   Diccionario  m_dic;
   Datos dat;
   TDatos datos;
   
   int opcion;
   char nom_arch[50];
   char nom_arch_dat[50];
   char id[50];
   
   do
   {
       system("cls");
	   printf("\n\n   M  E  N  U\n");
       printf("\n 1.- Crear Diccionario");
       printf("\n 2.- Imprimir Diccionario");
       printf("\n 3.- Guardar Diccionario");
       printf("\n 4.- Abrir Diccionario");
       printf("\n 5.- Capturar Datos");
       printf("\n 6.- Imprime Datos");
       printf("\n 7.- Guardar Archivo Datos");
       printf("\n 8.- Abrir Archivo Datos");
       printf("\n 9.- Guarda Claves");
       printf("\n 10.- Generar Arreglo");
       printf("\n 11.- Salir\n\n"); 
       printf("Opcion: ");
       scanf("%d", &opcion);
       
       switch(opcion)
       {
          case 1: crear(&m_dic);
                  leer(&m_dic);
                  break;
          
          case 2: imprime(m_dic);
                  break;
          
          case 3: system("cls");
                  printf("\nNombre Archivo Diccionario\n");
                  pide_nombre(nom_arch);
                  guarda_archivo(m_dic, nom_arch);
                  break;
          
          case 4: system("cls");
                  printf("\nNombre Archivo Diccionario\n");
                  pide_nombre(nom_arch);
                  abrir_archivo(&m_dic, nom_arch);
                  imprime(m_dic);
                  break;
          
          case 5: system("cls");
                  printf("\nNombre Archivo Diccionario\n");
                  pide_nombre(nom_arch);
                  abrir_archivo(&m_dic, nom_arch);
                  imprime(m_dic);
                  capturaDatos(m_dic, &dat);
                  break;
          
          case 6: imprimeDatos(m_dic, dat);
                  system("pause");
                  break;
          
          case 7: system("cls");
                  printf("\nNombre Archivo Datos\n");
                  pide_nombre(nom_arch_dat);
                  guarda_archivo_datos(m_dic, nom_arch, nom_arch_dat, dat);
                  break;
          
          case 8: system("cls");
                  printf("\nNombre Archivo Datos\n");
                  pide_nombre(nom_arch_dat);
                  abrir_archivo_datos(&m_dic, nom_arch, nom_arch_dat, &dat);
                  imprimeDatos(m_dic, dat);
                  system("pause");
                  break;
          case 9: guarda_claves(m_dic, dat);
                  break;
          case 10: printf("Dame Nombre Del Campo: ");
                   scanf("%s", id);
                   generarArr(m_dic, dat, id, &datos); 
                   break;
        }
     }while(opcion!=11);
}

void crear(Diccionario *dic)
{   
    system("cls");
    printf("\n Introduzca el numero de datos del diccionario: ");
    scanf("%d", &dic->numDatos);
    
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

void guarda_archivo(Diccionario dic, char nom[])
{
     char tipo;
     printf("Tipo de Archivo (B->Binario o T->Texto): ");
     fflush(stdin);
     scanf("%c", &tipo);
     
     if(tipo=='T' || tipo=='t')
        guarda_texto(dic, nom);
     else
        guarda_bin(dic, nom);
}

void abrir_archivo(Diccionario *dic, char nom[])
{
     char tipo;
     printf("Tipo de Archivo (B->Binario o T->Texto): ");
     fflush(stdin);
     scanf("%c", &tipo);
     
     if(tipo=='T' || tipo=='t')
        abrir_texto(dic, nom);
     else
        abrir_bin(dic, nom);
}

void guarda_texto(Diccionario dic, char nom[])
{
    FILE *f;
    int c=0, i=0;
    
    system("cls");
    
    f=fopen(nom,"w");
    fprintf(f, "%d ", dic.numDatos);
    for(i=0; i<dic.numDatos; i++)
    {
              fprintf(f, "%s ", dic.metaDato[i].nombre);
              fprintf(f, "%d ", dic.metaDato[i].tipo);
              fprintf(f, "%d ", dic.metaDato[i].tam);
              fprintf(f, "%d ", dic.metaDato[i].clave);
    }
    
    fclose(f);
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nom);
    system("pause");
}

void abrir_texto(Diccionario *dic, char nom[])
{
    FILE *f;
    char a[500];
    int i;
    
    f=fopen(nom,"r");
    printf("\n\n");
    if(f==NULL)
    {
               printf("No se encontro el archivo\n");
               system("pause");
    }
    
    rewind(f);
    fscanf(f, "%d", &dic->numDatos);
    dic->metaDato = (MetaDato *) malloc(dic->numDatos * sizeof(MetaDato));
    for(i=0; i<dic->numDatos; i++)
    {
              fscanf(f, "%s", dic->metaDato[i].nombre);
              fscanf(f, "%d", &dic->metaDato[i].tipo);
              fscanf(f, "%d", &dic->metaDato[i].tam);
              fscanf(f, "%d", &dic->metaDato[i].clave);
    }
    
    fclose(f);
    
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

void abrir_bin(Diccionario *dic, char nom[])
{
    FILE *f;
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
    dic->numDatos = tamArch(nom);
    dic->metaDato = (MetaDato *) malloc(dic->numDatos * sizeof(MetaDato));
    
    fread(dic->metaDato, sizeof(MetaDato), dic->numDatos, f);
    
    fclose(f);
    printf("\n\n");
}

void pide_nombre(char nom[])
{
    printf("Nombre del Archivo: ");
    scanf("%s", nom);
}

void capturaDatos(Diccionario d, Datos *dat)
{ 
     int i;
     void *dir;
     
     system("cls");
     printf("Capturando Datos:");
     printf("\nNo de Datos a Capturar: ");
     scanf("%d",&dat->numDatos);
     dat->tam = tamRegistro(d); /* ver abajo la función */
     dat->datos = malloc(dat->tam * dat->numDatos);
     dir = dat->datos;
     for(i=0; i<dat->numDatos; i++)
     {
        printf("\nCaptura[%d]\n", i+1);      
        capturaRegistro(d, dir);
        dir = (char *)dir + dat->tam;
     }
}


int tamRegistro(Diccionario d)
{
    int i, tam = 0;
    for(i = 0; i< d.numDatos; i++)
    {
      tam+=d.metaDato[i].tam;
    }
  
    return(tam);
}

void capturaRegistro(Diccionario d, void *dir)
{ 
   int i;
   for(i = 0; i<d.numDatos; i++)
   {    
        printf("%s: ", d.metaDato[i].nombre);
        switch(d.metaDato[i].tipo)
        {
           case 0: //char
               scanf("%c", (char *) dir);
               break;
           case 1: //int
               scanf("%d",(int *) dir);
               break;
           case 2: // float
               scanf("%f",(float*)dir);
               break;
           case 3: //string
               scanf("%s", (char *)dir);
        }
        dir = (char *)dir + d.metaDato[i].tam;
   }
}

void imprimeDatos(Diccionario d, Datos dat)
{ 
     int i;
     void *dir;
     
     system("cls");
     printf("\nDatos:\n");
     dir = dat.datos;
     for(i=0; i<dat.numDatos; i++)
     {
        printf("\nDato[%d]\n", i+1);      
        imprimeRegistro(d, dir);
        dir = (char *)dir + dat.tam;
     }
     printf("\n\n");
}

void imprimeRegistro(Diccionario d, void *dir)
{ 
   int i;
   for(i = 0; i<d.numDatos; i++)
   {    
        printf("%s: ", d.metaDato[i].nombre);
        switch(d.metaDato[i].tipo)
        {
           case 0: //char
               printf("%c\n", *(char *) dir);
               break;
           case 1: //int
               printf("%d\n", *(int *) dir);
               break;
           case 2: // float
               printf("%.2f\n", *(float*)dir);
               break;
           case 3: //string
               printf("%s\n", (char *)dir);
               break;
        }
        dir = (char *)dir + d.metaDato[i].tam;
   }
}

int tamArch(char nom[])
{
   FILE *stream;
   long curpos, length;
   int tam; 
   
   stream = fopen(nom, "rb+");
   curpos = ftell(stream);  /* regresa la posición actual del apuntador */
   fseek(stream, 0L, SEEK_END); /* coloca el apuntador al final */
   length = ftell(stream);  /* regresala la posición actual de apuntador */
   fseek(stream, curpos, SEEK_SET); /*coloca apuntador en "curpos" */
   tam=length / sizeof(MetaDato);
   fclose(stream);
   return tam;
}

void guarda_archivo_datos(Diccionario dic, char nom[], char nomdat[], Datos dat)
{
     char tipo;
     printf("Tipo de Archivo (B->Binario o T->Texto): ");
     fflush(stdin);
     scanf("%c", &tipo);
     
     if(tipo=='T' || tipo=='t')
        guarda_datos_txt(dic, nom, nomdat, dat);
     else
        guarda_datos_bin(dic, nom, nomdat, dat);
}

void abrir_archivo_datos(Diccionario *dic, char nom[], char nomdat[], Datos *dat)
{
     char tipo;
     printf("Tipo de Archivo (B->Binario o T->Texto): ");
     fflush(stdin);
     scanf("%c", &tipo);
     
     if(tipo=='T' || tipo=='t')
        abrir_datos_txt(dic, nom, nomdat, dat);
     else
        abrir_datos_bin(dic, nom, nomdat, dat);
}

void guarda_datos_txt(Diccionario dic, char nom[], char nomdat[], Datos dat)
{
    FILE *f;
    int i, j;
    void *dir;
    
    system("cls");
    
    f=fopen(nomdat,"w");
    fprintf(f, "%s ", nom);
    fprintf(f, "%d ", dat.numDatos);
    fprintf(f, "%d ", dat.tam);
    
    dir = dat.datos;
    for(i=0; i<dat.numDatos; i++)
    {
        for(j=0; j<dic.numDatos; j++)
        {
            switch(dic.metaDato[j].tipo)
            {
               case 0: fprintf(f, "%c ", *(char *) dir);
                       break;
               case 1: fprintf(f, "%d ", *(int *) dir);
                       break;
               case 2: fprintf(f, "%f ", *(float*)dir);
                       break;
               case 3: fprintf(f, "%s ", (char *)dir);
                       break;
            }
            dir = (char *)dir + dic.metaDato[j].tam;
        }
    }
    fclose(f);
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nomdat);
    system("pause");
}

void abrir_datos_txt(Diccionario *dic, char nom[], char nomdat[], Datos *dat)
{
    FILE *f;
    int i, j;
    void *dir;
    
    system("cls");
    
    f=fopen(nomdat,"r");
    printf("\n\n");
    if(f==NULL)
    {
               printf("No se encontro el archivo\n");
               system("pause");
    }
    rewind(f);
    fscanf(f, "%s", nom);
    fscanf(f, "%d", &dat->numDatos);
    fscanf(f, "%d", &dat->tam);
    
    abrir_texto(dic, nom);
    dat->datos = malloc(dat->tam * dat->numDatos);
    
    dir = dat->datos;
    for(i=0; i<dat->numDatos; i++)
    {
        for(j=0; j<dic->numDatos; j++)
        {
            switch(dic->metaDato[j].tipo)
            {
               case 0: fscanf(f, "%c", (char *) dir);
                       break;
               case 1: fscanf(f, "%d", (int *) dir);
                       break;
               case 2: fscanf(f, "%f", (float *)dir);
                       break;
               case 3: fscanf(f, "%s", (char *)dir);
                       break;
            }
            dir = (char *)dir + dic->metaDato[j].tam;
        }
    }
    fclose(f);
}

void guarda_datos_bin(Diccionario dic, char nom[], char nomdat[], Datos dat)
{
    FILE *f;
    
    system("cls");
    
    f=fopen(nomdat,"wb");
    fwrite(nom, 50, 1, f);
    fwrite(&dat.numDatos, sizeof(int), 1, f);
    fwrite(&dat.tam, sizeof(int), 1, f);
    
    fwrite(dat.datos, dat.tam, dat.numDatos, f);    
    
    fclose(f);
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nomdat);
    system("pause");
}

void abrir_datos_bin(Diccionario *dic, char nom[], char nomdat[], Datos *dat)
{
    FILE *f;
    system("cls");
    
    f=fopen(nomdat,"r");
    printf("\n\n");
    if(f==NULL)
    {
               printf("No se encontro el archivo\n");
               system("pause");
    }
    rewind(f);
    
    fread(nom, 50, 1, f);
    fread(&dat->numDatos, sizeof(int), 1, f);
    fread(&dat->tam, sizeof(int), 1, f);
    
    abrir_bin(dic, nom);
    
    dat->datos = malloc(dat->tam * dat->numDatos);
    
    fread(dat->datos, dat->tam, dat->numDatos, f); 
    
    fclose(f);
}

void guarda_claves(Diccionario d, Datos dat)
{
     FILE *f;
     int i, j;
     void *dir;
          
     f=fopen("claves.txt","w");
     dir = dat.datos;
     for(j=0; j<dat.numDatos; j++)
     {
       for(i=0; i<d.numDatos; i++)
       {    
        if(d.metaDato[i].clave == 1)
        switch(d.metaDato[i].tipo)
        {
           case 0: //char
                   fprintf(f,"%c\n", *(char *) dir);
                   break;
           case 1: //int
                   fprintf(f,"%d\n", *(int *) dir);
                   break;
           case 2: // float
                   fprintf(f,"%.2f\n", *(float*)dir);
                   break;
           case 3: //string
                   fprintf(f,"%s\n", (char *)dir);
                   break;
        }
        dir = (char *)dir + d.metaDato[i].tam;
       }
     }
     fclose(f);
     printf("El Archivo se a Creado Exitosamente con el Nombre: claves.txt\n\n");
     system("pause");
}

void generarArr(Diccionario d, Datos dat, char id[], TDatos *datos)
{
     int i, j;
     void *dir, *arr;
     
     for(i=0; i<d.numDatos; i++)
     {
         datos->tam = dat.tam;
         datos->noDatos = dat.numDatos;
     }
     
     datos->arreglo = malloc(datos->tam * datos->noDatos);
          
     dir = dat.datos;
     arr = datos->arreglo;
     for(j=0; j<dat.numDatos; j++)
     {
       for(i=0; i<d.numDatos; i++)
       {    
        if(strcmp(d.metaDato[i].nombre, id) == 0)
         switch(d.metaDato[i].tipo)
         {
           case 0: //char
                   *(char *) arr = *(char *) dir;
                   arr = (char *)arr + datos->tam;
                   break;
           case 1: //int
                   *(int *) arr = *(int *) dir;
                   arr = (char *)arr + datos->tam;
                   break;
           case 2: // float
                   *(float *) arr = *(float*)dir;
                   arr = (char *)arr + datos->tam;
                   break;
           case 3: //string
                   strcpy((char *)arr, (char *) dir);
                   arr = (char *)arr + datos->tam;
                   break;
        }
        dir = (char *)dir + d.metaDato[i].tam;
       }
     }
     /*printf("El Arreglo TDatos se a Creado Exitosamente\n\n");
     system("pause");*/
     
     for(j=0; j<dat.numDatos; j++)
     {
       for(i=0; i<d.numDatos; i++)
       {    
        if(strcmp(d.metaDato[i].nombre, id) == 0)
         switch(d.metaDato[i].tipo)
         {
           case 0: //char
                   printf("%c\n", (char *) arr);
                   arr = (char *)arr + datos->tam;
                   break;
           case 1: //int
                   printf("%d\n", (int *) arr);
                   arr = (char *)arr + datos->tam;
                   break;
           case 2: // float
                   printf("%f\n", (char *) arr);
                   arr = (char *)arr + datos->tam;
                   break;
           case 3: //string
                   printf("%s\n", (char *) arr);
                   arr = (char *)arr + datos->tam;
                   break;
         }
         dir = (char *)dir + d.metaDato[i].tam;
       }
     }
     system("pause");
}
