#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    char nombre[20];
    int puntos;
}record;

int tam(char cad[]);
void crea(void **a, int n, int tipo);
void captura(void *a, int n, int tipo);
void guarda_bin(void *a, int n, int tipo, char nom[]);
void guarda_txt(void *a, int n, int tipo, char nom[]);
void abrir_txt(char nom[]);
void abrir_bin(char nom[]);
void imprime(void *a, int n, int tipo);
void pide_nombre(char nom[]);

int main()
{
    void *arr;
    int num=3;
    int t, opcion;
    char nombre[30];
    
    do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Crear Archivo Binario");
		 printf("\n  2.- Abrir Archivo Binario");
		 printf("\n  3.- Crear Archivo De Texto");
		 printf("\n  4.- Abrir Archivo De Texto");
		 printf("\n\n  5.- Salir");
		 printf("\n\n  Opci¢n: ");
		 scanf("%d",&opcion);
		 switch(opcion)
		 {
            case 1: pide_nombre(nombre);
                    num=tam("Dame el Tamaño del Arreglo: ");
                    t=tam("Tipo de Datos (0->char; 1->int;  2->float; 3->cadena; 4->record): ");
                    crea(&arr, num, t);
                    captura(arr, num, t);
                    guarda_bin(arr, num, t, nombre);
                    break;
            case 2: pide_nombre(nombre);
                    abrir_bin(nombre);
                    break;
            case 3: pide_nombre(nombre);
                    num=tam("Dame el Tamaño del Arreglo: ");
                    t=tam("Tipo de Datos (0->char; 1->int;  2->float; 3->cadena; 4->record): ");
                    crea(&arr, num, t);
                    captura(arr, num, t);
                    guarda_txt(arr, num, t, nombre);
                    break;
            case 4: pide_nombre(nombre);
                    abrir_txt(nombre);
                    break;
			 
         }
      }while(opcion!=5);
      
      free(arr);
}

void crea(void **a, int n, int tipo)
{
     int tamcad;
     
     switch(tipo)
     {
         case 0: *a=malloc(sizeof(char)*n);
                 break;
         case 1: *a=malloc(sizeof(int)*n);
                 break;
         case 2: *a=malloc(sizeof(float)*n);
                 break;
         case 3: printf("Tamaño de la Cadena: ");
                 scanf("%d", &tamcad);
                 *a=malloc(tamcad*n);
                 break;
         case 4: *a=malloc(sizeof(record)*n);
                 break;
     }
}

void guarda_bin(void *a, int n, int tipo, char nom[])
{
    FILE *f;
        
    f=fopen(nom,"wb");
    fwrite(&n, sizeof(int), 1, f);
    fwrite(&tipo, sizeof(int), 1, f);
    switch(tipo)
     {
         case 0: fwrite(a, sizeof(char), n, f);
                 break;
         case 1: fwrite(a, sizeof(int), n, f);
                 break;
         case 2: fwrite(a, sizeof(float), n, f);
                 break;
         case 3: //fwrite(&a, sizeof(), n, f);
                 break;
         case 4: fwrite(a, sizeof(record), n, f);
                 break;
     }
    
    fclose(f);
}

void guarda_txt(void *a, int n, int tipo, char nom[])
{
    FILE *f;
    int i=0;
    
    f=fopen(nom,"w");
    fprintf(f, "%d ", n);      
    fprintf(f, "%d", tipo);      
    switch(tipo)
     {
         case 0: for(i=0; i<n; i++) //char
                 {
                    fprintf(f, "%c", *(char*)a);      
                    a=(char*)a + sizeof(char);  //Mover Apuntador
                 }
                 break;
         case 1: for(i=0; i<n; i++) //char
                 {
                    fprintf(f, " %d ", *(int*)a);      
                    a=(char*)a + sizeof(int);  //Mover Apuntador
                 }
                 break;
         case 2: for(i=0; i<n; i++) //char
                 {
                    fprintf(f, " %f ", *(float*)a);      
                    a=(char*)a + sizeof(float);  //Mover Apuntador
                 }
                 break;
         case 3: for(i=0; i<n; i++) //cadena
                 {
                    
                 }
                 break;
         case 4: for(i=0; i<n; i++) //char
                 {
                    fprintf(f, "%s", (char*)a);      
                    a=(char*)a + 20;  //Mover Apuntador
                    fprintf(f, " %d ", *(int*)a);      
                    a=(char*)a + sizeof(int);  //Mover Apuntador
                 }
                 break;
     }
    
    fclose(f);
}

void abrir_bin(char nom[])
{
    FILE *f;
    void *a, *b;
    int i=0, n, tipo;
    
    f=fopen(nom,"rb");
    fread(&n, sizeof(int), 1, f);
    fread(&tipo, sizeof(int), 1, f);
    
    crea(&a, n, tipo);
    b=a;
    
    switch(tipo)
     {
         case 0: fread(a, sizeof(char), n, f);
                 break;
         case 1: fread(a, sizeof(int), n, f);
                 break;
         case 2: fread(a, sizeof(float), n, f);
                 break;
         case 3: //fwrite(&a, sizeof(), n, f);
                 break;
         case 4: fread(a, sizeof(record), n, f);
                 break;
     }
     
     a=b;
     imprime(a, n, tipo);
     system("pause");
     fclose(f);
}

   

void abrir_txt(char nom[])
{
    FILE *f;
    void *a, *b;
    int i=0, n, tipo;
    
    f=fopen(nom,"r");
    fscanf(f, "%d", &n);      
    fscanf(f, "%d", &tipo);      
    
    crea(&a, n, tipo);
    b=a;
    
    switch(tipo)
     {
         case 0: for(i=0; i<n; i++) //char
                 {
                    fscanf(f, "%c", (char*)a);      
                    a=(char*)a + sizeof(char);  //Mover Apuntador
                 }
                 break;
         case 1: for(i=0; i<n; i++) //char
                 {
                    fscanf(f, "%d", (int*)a);      
                    a=(char*)a + sizeof(int);  //Mover Apuntador
                 }
                 break;
         case 2: for(i=0; i<n; i++) //char
                 {
                    fscanf(f, "%f", (float*)a);      
                    a=(char*)a + sizeof(float);  //Mover Apuntador
                 }
                 break;
         case 3: for(i=0; i<n; i++) //cadena
                 {
                    
                 }
                 break;
         case 4: for(i=0; i<n; i++) //char
                 {
                    fscanf(f, "%s", (char*)a);      
                    a=(char*)a + 20;  //Mover Apuntador
                    fscanf(f, "%d", (int*)a);      
                    a=(char*)a + sizeof(int);  //Mover Apuntador
                 }
                 break;
     }
     
     a=b;
     imprime(a, n, tipo);
     system("pause");
     fclose(f);
}

void captura(void *a, int n, int tipo)
{
     int i;
     
     switch(tipo)
     {
         case 0: for(i=0; i<n; i++) //Int
                 {
                    printf("Capturando Caracter %d: ", i+1);
                    fflush(stdin); //No Toma El Caracter de Enter
                    scanf("%c", (char*)a);
                    a=(char*)a + sizeof(char);  //Mover Apuntador
                 }
                 break;
         case 1: for(i=0; i<n; i++) //Int
                 {
                    printf("Capturando Entero %d: ", i+1);
                    scanf("%d", (int*)a);
                    a=(char*)a + sizeof(int);  //Mover Apuntador
                 }
                 break;
         case 2: for(i=0; i<n; i++) //float
                 {
                    printf("Capturando Flotante %d: ", i+1);
                    scanf("%f", (float*)a);
                    a=(char*)a + sizeof(float);
                 }
                 break;
         case 3: for(i=0; i<n; i++) //cadena
                 {
                    printf("Capturando cadena %d: ", i+1);
                    fflush(stdin);
                    scanf("%s",(char*)a);
                    a=(char*)a + 20;
                 }
                 break;
         case 4: for(i=0; i<n; i++) //cadena
                 {
                    printf("Nombre %d: ", i+1);
                    fflush(stdin);
                    gets((char*)a);
                    a=(char*)a + 20;
                    printf("Puntos %d: ", i+1);
                    fflush(stdin);
                    scanf("%d",(int*)a);
                    a=(char*)a + sizeof(int);
                 }
                 break;
     }
}

void imprime(void *a, int n, int tipo)
{
     int i;
     
     switch(tipo)
     {
         case 0: for(i=0; i<n; i++) //Int
                 {
                    printf("Dato [%d]= %c ", i+1, *(char*)a);
                    a=(char*)a + sizeof(char);  //Mover Apuntador
                    putchar('\n');
                 }
                 break;
         case 1: for(i=0; i<n; i++) //Int
                 {
                    printf("Dato [%d]= %d ", i+1, *(int*)a);
                    a=(char*)a + sizeof(int);  //Mover Apuntador
                    putchar('\n');
                 }
                 break;
         case 2: for(i=0; i<n; i++) //Float
                 {
                    printf("Dato [%d]= %f ", i+1, *(float*)a);
                    a=(char*)a + sizeof(float);  //Mover Apuntador
                    putchar('\n');
                 }
                 break;
         case 3: for(i=0; i<n; i++) //Float
                 {
                    printf("Dato [%d]= %s ", i+1, *(char*)a);
                    a=(char*)a + sizeof(char);  //Mover Apuntador
                    putchar('\n');
                 }
                 break;
         case 4: for(i=0; i<n; i++) //cadena
                 {
                    printf("Nombre %d: %s", i+1, (char*)a);
                    a=(char*)a + 20;
                    printf("     Puntos %d: %d", i+1, *(int*)a);
                    a=(char*)a + sizeof(int);
                    putchar('\n');
                 }
                 break;
     }     
}

int tam(char cad[])
{
    int temp;
    printf("%s", cad);
    scanf("%d", &temp);
    return temp;
}
void pide_nombre(char nom[])
{
    system("cls");
    
    printf("Nombre del Archivo: ");
    scanf("%s", nom);
}
