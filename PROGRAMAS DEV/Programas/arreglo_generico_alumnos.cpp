/* arreglo dinámico con void*    jcct 2009 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
        int puntos;
        char nombre [50];
        }record;
        
int tam(char cad[]);
void crea(void **a, int n, int tipo);
void captura(void *a,int n, int tipo);
void imprime(void *a, int n,int tipo);
void guardar_archivo(void *a, int n,int tipo);
void leer_Archivo();
int main()
{
 void *arr;
 int num=3;
 int t; 
  /* num = tam("Dame el tamaño del arreglo: ");
   t = tam("Dame el tipo de datos del arreglo ( 0->int; 1->float 2->char; 3-> record): ");
   crea(&arr,num,t);
   captura(arr,num,t);
   guardar_archivo(arr,num,t);
   imprime(arr,num,t);
   free(arr);*/
  
 leer_Archivo();  
   
   
   
   system("pause");
}    

void crea(void **a, int n, int tipo)
{
switch(tipo)
 {
   case 0: *a=malloc(sizeof(int)*n);  //int
            break;
   case 1: *a=malloc(sizeof(float)*n);  //float
            break;  
   case 2: *a=malloc(sizeof(char)*n);
            break;
   case 3: *a=malloc(sizeof(record)*n);
            break;           
 }    
}

void captura(void *a, int n, int tipo)
{int i;
 switch(tipo)
 {
   case 0: //int
           for(i=0;i<n;i++)
           {
             printf("capturando entero %d:",i);
             scanf("%d",(int*) a);
             a = (char*) a + sizeof(int);
           }    
           break;
   case 1: //float
           for(i=0;i<n;i++)
           {
             printf("capturando flotante %d:",i);
             scanf("%f", (float*) a);
             a = (char*) a + sizeof(float);
           }  
           break; 
   case 2: //char
            for(i=0; i<n;i++)
            {
               printf("capturando caracter %d:",i);
               fflush(stdin);
               scanf("%c",(char*) a);
               a = (char*) a + sizeof(char);         
            }  
   case 3: //record
            for(i=0; i<n;i++)
            {
               printf("capturando puntos %d:",i);
               fflush(stdin);
               scanf("%d",(int*) a);
               a = (char*) a + sizeof(int);
               printf("capturando nombre %d :",i);
               fflush(stdin);
               scanf("%s",(char*)a);
               a= (char*) a + sizeof (char)*50;
                       
            }        
 }               
}

void imprime(void *a, int n,int tipo)
{int i;
     
 switch(tipo)
 {
   case 0: //int
           for(i=0;i<n;i++)
           {
             printf("%d ",*(int*) a);
             a = (char*) a + sizeof(int);
           }    
           break;
   case 1: //float
           for(i=0;i<n;i++)
           {
             printf("%.2f ",*(float*)a);
             a = (char*) a + sizeof(float);
           }         
   case 2: //char
            for(i=0; i<n;i++)
            {
               printf("%c ",*(char*)a);
               a = (char*) a + sizeof(char);         
            }  
    case 3: //record
            for(i=0; i<n;i++)
            {
               printf("\n puntos= %d:",*(int*)a);
               a = (char*) a + sizeof(int);
               printf("\n nombre= %s :",(char*)a);
               a= (char*) a + sizeof (char)*50;
                       
            }        
        
 }            
}

int tam(char cad[])
{
int temp;
    printf("%s",cad);
    scanf("%d",&temp);
    return(temp);
}

void guardar_archivo(void *a, int n,int tipo)
{ 
int i;
  FILE *f;
  
  f=fopen("puntos.txt","w");
  fprintf(f,"%d %d",n,tipo);    
 switch(tipo)
 {
   case 0: //int
           for(i=0;i<n;i++)
           {
             fprintf(f,"\n%d ",*(int*) a);
             a = (char*) a + sizeof(int);
           }    
           break;
   case 1: //float
           for(i=0;i<n;i++)
           {
             fprintf(f,"\n%.2f ",*(float*)a);
             a = (char*) a + sizeof(float);
           }         
   case 2: //char
            for(i=0; i<n;i++)
            {
               fprintf(f,"\n%c ",*(char*)a);
               a = (char*) a + sizeof(char);         
            }  
    case 3: //record
            for(i=0; i<n;i++)
            {
               fprintf(f,"\n puntos= %d:",*(int*)a);
               a = (char*) a + sizeof(int);
               fprintf(f,"\n nombre= %s :",(char*)a);
               a= (char*) a + sizeof (char)*50;
                       
            }        
        
 }            
}
void leer_Archivo()
{ 
  void *a,*b;
  int n ,i ,tipo;
  FILE *f;
  
  f = fopen("puntos.txt","r" );
  
  
  if( f!= NULL )
  { 
   fscanf( f, "%d", &n );
   fscanf( f, "%d", &tipo );
   
   printf( "n = %d ", n );
   printf( " tipo = %d ", tipo );
    
   crea( &a , n, tipo );
   
   b = a;
   
   switch(tipo)
   {
     case 0: //int
           for(i=0;i<n;i++)
           {
             fscanf(f, "%d",(int*) a);
             printf( " a = %d" , *(int*)a );
             a = (char*) a + sizeof(int);
           }    
           break;
     case 1: //float
           for(i=0;i<n;i++)
           {
             fscanf(f,"%f", (float*) a);
             a = (char*) a + sizeof(float);
           }  
           break; 
     case 2: //char
            for(i=0; i<n;i++)
            {
               fscanf(f,"%c",(char*) a);
               a = (char*) a + sizeof(char);         
            }
            break;
   case 3: //record
            for(i=0; i<n;i++)
            {
               fscanf(f,"%d",(int*) a);
               a = (char*) a + sizeof(int);
               
               fscanf(f,"%s",(char*)a);
               a= (char*) a + sizeof (char)*50;
            }
       
   }
   imprime( b , n, tipo );                
  }
}
