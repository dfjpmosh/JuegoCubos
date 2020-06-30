/* arreglo dinámico con void*    jcct 2009 */

#include <stdio.h>
#include <stdlib.h>

int tam(char cad[]);
void crea(void **a, int n, int tipo);
void captura(void *a,int n, int tipo);
void imprime(void *a, int n,int tipo);

int main()
{
void *arr;
int num=3;
int t; 
   num = tam("Dame el taño del arreglo: ");
   t = tam("Dame el tipo de datos del arreglo ( 0->int; 1->float ): ");
   crea(&arr,num,t);
   captura(arr,num,t);
   imprime(arr,num,t);
   free(arr);
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
 }            
}

int tam(char cad[])
{
int temp;
    printf("%s",cad);
    scanf("%d",&temp);
    return(temp);
}
