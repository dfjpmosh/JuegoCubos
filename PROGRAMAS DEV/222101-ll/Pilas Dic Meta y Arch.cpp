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
    void *pila;
    int tope;
    int tam;
    int tamDatos;
}Pila;

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
int push(Diccionario dic, Pila *p); //Insertar en la Pila
int pop(Diccionario dic, Pila *p); //Sacar de la Pila
int pilaVacia(Pila p);
int pilaLlena(Pila p);
int inicializaPila(Diccionario dic, Pila *p, int tam);
void imprimePila(Diccionario d, Pila p); 
void capturaRegistro(Diccionario d, void *dir);
void imprimeRegistro(Diccionario d,void *dir);
void guarda_pila_txt(Diccionario dic, char nom[], char nompil[], Pila p);
void abrir_pila_txt(Diccionario *dic, char nom[], char nompil[], Pila *p);
void guarda_pila_bin(Diccionario dic, char nom[], char nompil[], Pila p);
void abrir_pila_bin(Diccionario *dic, char nom[], char nompil[], Pila *p);
void guarda_archivo_pila(Diccionario dic, char nom[], char nompil[], Pila p);
void abrir_archivo_pila(Diccionario *dic, char nom[], char nompil[], Pila *p);

int main()
{
     int opcion, n;
     Diccionario  m_dic;
     Pila p;
     char nom_arch[50];
     char nom_arch_pila[50];
          
     do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Crear y Guardar Diccionario");
         printf("\n  2.- Crear Pila");
		 printf("\n  3.- Insertar en Pila");
		 printf("\n  4.- Sacar de Pila");
		 printf("\n  5.- Imprimir Pila");
		 printf("\n  6.- Guardar Pila");
		 printf("\n  7.- Abrir Pila");
		 printf("\n  8.- Salir");
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
                    system("cls");
                    printf("\n\n    CREANDO PILA\n");
                    printf("Cuantos Datos: ");
			        scanf("%d", &n);
                    inicializaPila(m_dic, &p, n);
			        break;
			        
			case 3: system("cls");
                    if(push(m_dic,&p)==0)
			        {
                       printf("\nPila Llena\n");   
                       system("pause");
                    }
			        break;
			
            case 4: system("cls");
                    if(pop(m_dic,&p)==0)
			        {
                       printf("\nPila Vacia\n");   
                    }
                    system("pause");
                    break;
            
            case 5: system("cls");
                    imprimePila(m_dic, p); 
                    putchar('\n');
                    system("pause");
			        break;
			        
            case 6: system("cls");
                    printf("\nNombre Archivo Datos\n");
                    pide_nombre(nom_arch_pila);
                    guarda_archivo_pila(m_dic, nom_arch, nom_arch_pila, p);
                    break;
          
            case 7: system("cls");
                    printf("\nNombre Archivo Datos\n");
                    pide_nombre(nom_arch_pila);
                    abrir_archivo_pila(&m_dic, nom_arch, nom_arch_pila, &p);
                    imprimePila(m_dic, p);
                    system("pause");
                    break;  
		}
	}while(opcion!=8);
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

int pilaVacia(Pila p)
{
      // 1 Quiere decir que la pila esta vacia y un 0 si no esta
      int reg = 1;			
      if(p.tope > 0)                          			
               reg = 0;			
      return(reg);			
}

int pilaLlena(Pila p)
{
      //Regresa un 1 si esta llena, esto es, tope == tam
      int reg = 1;			
      if(p.tope < p.tam)                          			
               reg = 0;			
      return(reg);			
    	}

int inicializaPila(Diccionario dic, Pila *p, int tam)
{  
     int res=0;
     
     p->tam = tam; 
     p->tamDatos = tamRegistro(dic);	 
     p->pila = malloc(p->tamDatos * p->tam); 
      
     if(p->pila) 
     { 
         p->tope = 0;    
         res = 1; 
     } 
     return (res);
}

//insercion de nuevo dato
int push(Diccionario dic, Pila *p)
{
      int reg = 0;
      void *dir;
      dir=p->pila;
      
      if( ! pilaLlena(*p) )                 //  1
      {
             dir=(char*)dir+(p->tope)*p->tamDatos;
             capturaRegistro(dic,dir);
             p->tope++;            
             reg = 1;
      }
      return(reg);			//1.3, 2.1
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

//sacar o eliminar el dato
int pop(Diccionario dic, Pila *p)
{
      int reg = 0;
      void *dir;
      dir=p->pila;
      
      if( ! pilaVacia(*p))
      {
             dir=(char*)dir+(p->tope-1)*p->tamDatos;
             imprimeRegistro(dic,dir);			// 1.1	
             p->tope--; 
             reg = 1;
      }
      return(reg);
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

void imprimePila(Diccionario d, Pila p) 
{
     int i;
     void *dir;
     
     dir=p.pila;
     
     if(pilaVacia(p) == 1)
         printf("Pila Vacia");
     else
         printf("DATOS DE LA PILA\n\n");
         for(i=p.tope-1; i>=0; i--)
         {
            dir=(char*)p.pila + i*p.tamDatos;
            imprimeRegistro(d,dir);
         }
     printf("\n\n");
}

void guarda_archivo_pila(Diccionario dic, char nom[], char nompil[], Pila p)
{
     char tipo;
     printf("Tipo de Archivo (B->Binario o T->Texto): ");
     fflush(stdin);
     scanf("%c", &tipo);
     
     if(tipo=='T' || tipo=='t')
        guarda_pila_txt(dic, nom, nompil, p);
     else
        guarda_pila_bin(dic, nom, nompil, p);
}

void abrir_archivo_pila(Diccionario *dic, char nom[], char nompil[], Pila *p)
{
     char tipo;
     printf("Tipo de Archivo (B->Binario o T->Texto): ");
     fflush(stdin);
     scanf("%c", &tipo);
     
     if(tipo=='T' || tipo=='t')
        abrir_pila_txt(dic, nom, nompil, p);
     else
        abrir_pila_bin(dic, nom, nompil, p);
}

void guarda_pila_txt(Diccionario dic, char nom[], char nompil[], Pila p)
{
    FILE *f;
    int i, j;
    void *dir;
    
    system("cls");
    
    f=fopen(nompil,"w");
    fprintf(f, "%s ", nom);
    fprintf(f, "%d ", p.tamDatos);
    fprintf(f, "%d ", p.tam);
    fprintf(f, "%d ", p.tope);
    
    dir = p.pila;
    for(i=0; i<p.tamDatos; i++)
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
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nompil);
    system("pause");
}

void abrir_pila_txt(Diccionario *dic, char nom[], char nomdat[], Pila *p)
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
    fscanf(f, "%d", &p->tamDatos);
    fscanf(f, "%d", &p->tam);
    fscanf(f, "%d", &p->tope);
    
    abrir_texto(dic, nom);
    p->pila = malloc(p->tam * p->tamDatos);
    
    dir = p->pila;
    for(i=0; i<p->tamDatos; i++)
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

void guarda_pila_bin(Diccionario dic, char nom[], char nompil[], Pila p)
{
    FILE *f;
    
    system("cls");
    
    f=fopen(nompil,"wb");
    fwrite(nom, 50, 1, f);
    fwrite(&p.tamDatos, sizeof(int), 1, f);
    fwrite(&p.tam, sizeof(int), 1, f);
    fwrite(&p.tope, sizeof(int), 1, f);
    
    fwrite(p.pila, p.tam, p.tamDatos, f);    
    
    fclose(f);
    
    printf("El Archivo se a Creado Exitosamente con el Nombre: %s\n\n", nompil);
    system("pause");
}

void abrir_pila_bin(Diccionario *dic, char nom[], char nompil[], Pila *p)
{
    FILE *f;
    system("cls");
    
    f=fopen(nompil,"rb");
    printf("\n\n");
    if(f==NULL)
    {
               printf("No se encontro el archivo\n");
               system("pause");
    }
    rewind(f);
    
    fread(nom, 50, 1, f);
    fread(&p->tamDatos, sizeof(int), 1, f);
    fread(&p->tam, sizeof(int), 1, f);
    fread(&p->tope, sizeof(int), 1, f);
    
    abrir_bin(dic, nom);
    
    p->pila = malloc(p->tam * p->tamDatos);
    
    fread(p->pila, p->tam, p->tamDatos, f); 
    
    fclose(f);
}
