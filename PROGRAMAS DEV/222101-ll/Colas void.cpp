#include<stdio.h>
#include<stdlib.h>

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
    void *cola;
    int inicio, final;
    int tam;
    int tamDatos;
}Cola;

void crear(Diccionario *dic);
void leer(Diccionario *dic);
void imprime(Diccionario dic);
void guarda_archivo(Diccionario dic, char nom[]);
void abrir_archivo(Diccionario *dic, char nom[]);
void guarda_texto(Diccionario dic, char nom[]);
void abrir_texto(Diccionario *dic, char nom[]);
void guarda_bin(Diccionario dic, char nom[]);
void abrir_bin(Diccionario *dic, char nom[]);
void pide_nombre(char nom[]);
int tamArch(char nom[]);
int tamRegistro(Diccionario d);
int inicializaCola(Diccionario dic, Cola *c, int tam);
int colaVacia(Cola c);
int colaLlena(Cola c);
int enqueue(Diccionario dic, Cola *c);
int dequeue(Diccionario dic, Cola *c);
void imprimeCola(Diccionario d, Cola c);
void capturaRegistro(Diccionario d, void *dir);
void imprimeRegistro(Diccionario d,void *dir);

int main()
{
     int opcion, n, d;
     Diccionario  m_dic;
     Cola c;
     char nom_arch[50];
          
     do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Crear y Guardar Diccionario");
         printf("\n  2.- Crear Cola");
		 printf("\n  3.- Insertar en Cola");
		 printf("\n  4.- Sacar de Cola");
		 printf("\n  5.- Imprimir Cola");
		 printf("\n  6.- Salir");
		 printf("\n\n  Opci¢n: ");
		 scanf("%d",&opcion);
		 switch(opcion)
		 {
            case 1: crear(&m_dic);
                    leer(&m_dic);
                    system("cls");
                    printf("\nNombre Archivo Diccionario\n");
                    pide_nombre(nom_arch);
                    guarda_archivo(m_dic, nom_arch);
                    break;
          
            case 2: system("cls");
                    printf("\nNombre Archivo Diccionario\n");
                    pide_nombre(nom_arch);
                    abrir_archivo(&m_dic, nom_arch);
                    imprime(m_dic);
                    printf("\n\n    CREANDO COLA\n");
                    printf("Cuantos Datos: ");
			        scanf("%d", &n);
                    inicializaCola(m_dic, &c, n);
			        break;
			        
			case 3: system("cls");
			        if(enqueue(m_dic, &c)==0)
			        {
                       printf("\nCola Llena\n");   
                       system("pause");
                    }
			        break;
                    
            case 4: system("cls");
                    if(dequeue(m_dic, &c)==0)
			        {
                       printf("\nCola Vacia\n");   
                    }
                    system("pause");
                    break;
                    
            case 5: system("cls");
                    imprimeCola(m_dic, c); 
                    putchar('\n');
                    system("pause");
			        break;
			}
	}while(opcion!=6);
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

int tamRegistro(Diccionario d)
{
    int i, tam = 0;
    for(i = 0; i< d.numDatos; i++)
    {
      tam+=d.metaDato[i].tam;
    }
  
    return(tam);
}

void pide_nombre(char nom[])
{
    printf("Nombre del Archivo: ");
    scanf("%s", nom);
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

int inicializaCola(Diccionario dic, Cola *c, int tam)
{  
     int res=0;
     
     c->tam = tam; 
     c->tamDatos = tamRegistro(dic);	 
     c->cola = malloc(c->tamDatos * c->tam);
     
     if(c->cola)
     {
         c->inicio =c->final = 0;   
         res = 1;
     }
     return (res);
}

int colaVacia(Cola c)
{
      int reg;
      
      reg = c.inicio == c.final ? 1 : 0;			
		
      return(reg);			
}

int colaLlena(Cola c)
{
      int reg;

      reg = (c.final + 1) % c.tam == c.inicio? 1:0;		
      
      return(reg);			
}

int enqueue(Diccionario dic, Cola * c)
{
      int reg = 0;
      void *dir;
      dir=c->cola;
      
      if( ! colaLlena(*c) )                 		//  1
      {
             dir=(char*)dir+(c->final)*c->tamDatos;
             capturaRegistro(dic,dir);
             c->final = (c->final + 1) % c->tam;
             reg = 1;
      }
}

int dequeue(Diccionario dic, Cola * c)
{
      int reg = 0;	
      void *dir;
      dir=c->cola;
      					// 2.1
      if( ! colaVacia(*c))                			 	//  1
      { 
           dir=(char*)dir+(c->inicio)*c->tamDatos;
           imprimeRegistro(dic,dir);
           c->inicio = (c->inicio + 1) % c->tam;			// 1.1	
           reg = 1;
      }
      return(reg);
}

void imprimeCola(Diccionario d, Cola c)
{
     int i;
     void *dir;
     
     dir=c.cola;
     
     if(colaVacia(c) == 1)
         printf("Pila Vacia");
     else
         for(i=c.inicio; i<c.final; i++)
         {
            dir=(char*)c.cola + i*c.tamDatos;
            imprimeRegistro(d,dir);
         }
}

