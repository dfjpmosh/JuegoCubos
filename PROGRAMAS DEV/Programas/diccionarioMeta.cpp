#include<stdio.h>
#include<stdlib.h>
typedef struct
{
        char nom[15];
        int tipo;
        int tam;
        int clave;
}Metadatos;
typedef struct
{
        Metadatos *arreglo;
        int numMet;
}Diccionario;
int Cuantos();
void creaDicc(Diccionario *dic,int nMet);
void capturaDicc(Diccionario *dic);
void muestra(Diccionario dic);
void GuardaArch(Diccionario dic);
void LecturadArch(Diccionario dic);
int main()
{
    int nM;
    Diccionario dicc;
    
    nM=Cuantos();
    creaDicc(&dicc,nM);
    capturaDicc(&dicc);
    muestra(dicc);
    GuardaArch(dicc);
    LecturadArch(dicc);
    
    system("pause");
}
int Cuantos()
{
    int nMet;
    
    printf("Inserta Cuantos Metadatos son\t=>");
    scanf("%d",&nMet);
    
    return nMet;
}
void creaDicc(Diccionario *dic,int nMet)
{
     dic->arreglo=(Metadatos *)malloc(sizeof(Metadatos)*nMet);
     if(!dic->arreglo)
        printf("No Hay Arreglo de Metadatos\n");
     else
       dic->numMet=nMet;
}
void capturaDicc(Diccionario *dic)
{
     int i;
     
     printf("\n\n");
     for(i=0;i<dic->numMet;i++)
     {
        printf("Inserta Nombre[%d]\t",i);fflush(stdin);
        gets((dic->arreglo+i)->nom);
        printf("Tipo:\t");
        printf("0=char 1=int 2=float 3=cadena\t");
        scanf("%d",&(dic->arreglo+i)->tipo);
        
        switch((dic->arreglo+i)->tipo)
        {
          case 0: (dic->arreglo+i)->tam=sizeof(char);
                  break;
          case 1: (dic->arreglo+i)->tam=sizeof(int);
                  break;
          case 2: (dic->arreglo+i)->tam=sizeof(float);
                  break;
          case 3: printf("Inserta el Tamanio de la Cadena\t=>");
                  scanf("%d",&(dic->arreglo+i)->tam);
                  break;
          }//switch
        printf("Es un Campo Clave[%d]?:\t",i);
        scanf("%d",&(dic->arreglo+i)->clave);
        printf("\n--------------------------------\n");
        }//for
}
void muestra(Diccionario dic)
{
     int i;
     
     printf("\n\n\t\t=DATOS  ALMACENADOS EN DICCIONARIO=\n\n");
     for(i=0;i<dic.numMet;i++)
     {
       printf("Nombre[%d] %s\n",i,(dic.arreglo+i)->nom);
       printf("Clave[%d] %d\n",i,(dic.arreglo+i)->clave);
       printf("Tamanio[%d] %d\n",i,(dic.arreglo+i)->tam);
       printf("Tipo[%d] %d\n",i,(dic.arreglo+i)->tipo);
       printf("\n");
       }//for
       system("pause");
}
void GuardaArch(Diccionario dic)
{
   FILE *arch;
   int i;
   
   arch=fopen("Dicc.txt","w");
   if(!arch)
     printf("No Hay Archivo para Guardar\n");
    else
     {
      for(i=0;i<dic.numMet;i++)
      {
       fprintf(arch,"%s\t%d\t%d\t%d\n",(dic.arreglo+i)->nom,(dic.arreglo+i)->clave,(dic.arreglo+i)->tam,(dic.arreglo+i)->tipo);
       }//for
      fclose(arch);
      }//else
}
void LecturadArch(Diccionario dic)
{
     FILE *arch;
     Metadatos m;
     int i=0;
     
     arch=fopen("Dicc.txt","r");
     if(!arch)
       printf("No Hay Archivo para Lectura\n");
      else
       {
         printf("\n\n\t\t=DATOS DEL ARCHIVO=\n");
         printf("Nombre      Clave     Tamanio     Tipo\n");
         while(!feof(arch))
         {
          fscanf(arch,"%s\t%d\t%d\t%d\n",m.nom,&m.clave,&m.tam,&m.tipo);
          
           printf("%s\t",m.nom);
           printf("%d\t",m.clave);
           printf("%d\t",m.tam);
           printf("%d\n",m.tipo);
           printf("\n");
           i++;
           
          }//while
         fclose(arch);
         }//else
}

