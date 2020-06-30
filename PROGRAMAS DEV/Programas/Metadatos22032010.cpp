//MetaDatos
//22 - Marzo - 2010
//Generar un menu para metadatos y captura de datos con estructura dinamica diccionario
//Guardar diccionario en un archivo y los registros de este 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
        char nombre[20];	//nombre del atributo 
        int tipo;	//tipo del atributo 
        int tam;	//tamaño del atributo en bytes 
        char clave;
        }MetaDato;
        
typedef struct{
        int num;
        MetaDato *metadato;
        }Diccionario;      

typedef struct{
        int numDatos,tam;
        void *datos;
        }Datos;      
          

void menu();
void creaDic(Diccionario *dic);
void leeDic(Diccionario *dic);
void imprimeDic(Diccionario dic);
void guardaDic(Diccionario dic);
void imprimeArch(Diccionario *d);
long filezise(FILE *stream, char nombre[]);
void capturaDatos(Diccionario d,Datos *dat);
void imprimeDatos(Diccionario d,Datos dat);
int tamRegistro(Diccionario d);
void capturaRegistro(Diccionario d, void *dir);
void guardaRegistro(Diccionario d,Datos dat);
void buscarDatos(Diccionario d,Datos dat);

int main()
{
    menu();
}
void menu()
{
     int tecla;
     Diccionario dic,d;
     Datos dat;
     
     void *dir;
     do{
        system("cls");         
        printf("1.- Crea diccionario\n");
        printf("\n2.- Lee diccionario\n");
        printf("\n3.- Imprime diccionario\n");
        printf("\n4.- Guarda diccionario en archivo\n");
        printf("\n5.- Lee archivo\n");
        printf("\n6.- Captura Registro\n");
        printf("\n7.- Imprime Registro\n");
        printf("\n8.- Guarda Registro\n");
        printf("\n9.- Busqueda de Registro\n");
        printf("\n\n10.- Salir");
        printf("\n\nTeclea el numero de la opcion deseada: ");
        scanf("%d",&tecla);
        system("cls");
        switch(tecla)
        {
               case 1:creaDic(&dic);
                      break;
               case 2:leeDic(&dic);
                      break;
               case 3:imprimeDic(dic);
                      break;
               case 4:guardaDic(dic);
                      break;
               case 5:imprimeArch(&d);
                      break;
               case 6:capturaDatos(d,&dat);
                      break;
               case 7:imprimeDatos(d,dat);
                      break;
               case 8:guardaRegistro(d,dat);
                      break;
               
               case 9:buscarDatos(d,dat);
                      break;       
        }    
     }while(tecla!=10);
}
void creaDic(Diccionario *dic)
{
     int i;
     
     printf("Numero de registros: ");
     scanf("%d",&dic->num);
     
     dic->metadato =(MetaDato *) malloc(sizeof(MetaDato)*(dic->num)); 
}
void leeDic(Diccionario *dic)
{
     int i,t;
     
     for(i=0; i<dic->num; i++) 
     {
            printf("\nNombre del campo [%d]: ",i+1);
            fflush(stdin);
            gets(dic->metadato[i].nombre);
            printf("Tipos de campo: \n0=char\n1=int\n2=float\n3=string\nCual tipo de campo desea: " );
            scanf("%d", &dic->metadato[i].tipo);
            printf("Es clave(0/1): ");
            fflush(stdin);
            scanf("%d", &dic->metadato[i].clave);
            switch(dic->metadato[i].tipo)
            {    
                  case 0: dic->metadato[i].tam=sizeof(char);   
                          break;
                  case 1: dic->metadato[i].tam=sizeof(int);   
                          break;
                  case 2: dic->metadato[i].tam=sizeof(float);   
                          break;
                  case 3: printf("Tamaño de la cadena:");
                          scanf("%d",&t);
                          dic->metadato[i].tam=t;   
                          break;
            }    
     }
     
}    
void imprimeDic(Diccionario dic)
{
     int i;
     printf("Campo\tTipo\tClave\tTamaño");
     for(i=0; i<dic.num; i++) 
     {
            printf("\n%s",dic.metadato[i].nombre);
            printf("\t%d",dic.metadato[i].tipo);
            printf("\t%d",dic.metadato[i].clave);
            printf("\t%d",dic.metadato[i].tam);
     }
     system("pause");
}
void guardaDic(Diccionario dic)
{
     FILE *arch;
     int i;
     char nombre[50];
     printf("Nombre del archivo: ");
     fflush(stdin);
     gets(nombre);
     arch=fopen(nombre,"wb");
     
     fwrite(&dic.num,sizeof(int),1,arch);
     fwrite(dic.metadato,sizeof(MetaDato),dic.num,arch);
     
     fclose(arch);
}
void imprimeArch(Diccionario *d)
{
     int i;
     FILE *arch,*stream;
     long tam=0;
     char nombre[50];
     printf("Nombre del archivo: ");
     fflush(stdin);
     gets(nombre);
     arch=fopen(nombre,"rb+");
     fread(&d->num,sizeof(int),1,arch); 
     tam=filezise(stream,nombre);
     tam/=sizeof(MetaDato); 
     
     d->metadato =(MetaDato *) malloc(sizeof(MetaDato)*tam);
     fread(d->metadato,sizeof(MetaDato),tam,arch);         //Lee los datos del archivo sin formato
     
     printf("Campo\tTipo\tClave\tTamaño");
       for(i=0;i<tam;i++)
       {
          printf("\n %s",d->metadato[i].nombre);
          printf("\t %d",d->metadato[i].tipo);
          printf("\t %d",d->metadato[i].clave);
          printf("\t %d",d->metadato[i].tam); 
       }
       system("pause");
    fclose(arch);
}
long filezise(FILE *stream, char nombre[])
{
     long curpos, length;
     
     stream=fopen(nombre,"rb+");
     curpos=ftell(stream);
     fseek(stream,0L,SEEK_END);
     length=ftell(stream);
     fseek(stream,curpos,SEEK_SET);
     fclose(stream);
     return length;
}
void capturaDatos(Diccionario d,Datos *dat) 
{ 
     int i;
     void *dir; 
     //Datos *dat;
     int num; 
     
     printf("Cuantos: ");
     scanf("%d",&num);
     dat->numDatos = num; 
     dat->tam = tamRegistro(d);	/* ver abajo la funcio´n */ 
     dat->datos = malloc(dat->tam * dat->numDatos); 
     dir = dat->datos; 
     for(i=0; i<dat->numDatos; i++) 
     {
         capturaRegistro(d, dir); 
         dir = (char *)dir + dat->tam;
         printf("\n");
     }
}
int tamRegistro(Diccionario d) 
{
    int i, tam = 0; 
    
    for(i = 0; i< d.num; i++)
        tam+=d.metadato[i].tam; 
    return(tam);  
}
void capturaRegistro(Diccionario d, void *dir) 
{ 
     int i;
     
     for(i = 0; i<d.num; i++)
     {
           printf("%s: ", d.metadato[i].nombre);  
           switch(d.metadato[i].tipo) 
           {
                 case 0: //char 
                         fflush(stdin);
                         scanf("%c", (char *) dir); 
                         break;
                 case 1: //int 
                         scanf("%d",(int *) dir); 
                         break;
                 case 2: // float 
                         scanf("%f",(float*)dir); 
                         break;
                 case 3: //string 
                         fflush(stdin);
                         scanf("%s", (char *)dir);
                         break;
           }
      dir = (char *)dir + d.metadato[i].tam; 
      }
}
void imprimeDatos(Diccionario d,Datos dat) 
{ 
     int i,j;
     void *dir;
     
     dir=dat.datos; 
     
     for(j=0; j<dat.numDatos; j++) 
     {
          printf("\n");
          for(i = 0; i<d.num; i++)
          {
            printf("\n%s: ", d.metadato[i].nombre);  
            switch(d.metadato[i].tipo) 
            {
                  case 0: //char 
                              printf("%c", *(char *) dir); 
                              break;
                  case 1: //int 
                              printf("%d",*(int *) dir); 
                              break;
                  case 2: // float 
                              printf("%.2f",*(float*)dir); 
                              break;
                  case 3: //string 
                              printf("%s", (char *)dir);
                              break;
            } 
            dir = (char *)dir + d.metadato[i].tam; 
          }
         
      }
      system("pause");
}
void guardaRegistro(Diccionario d,Datos dat)
{
     FILE *arch;
     char nombre[50];
     int i,j;
     void *dir;
     
     printf("Nombre del archivo de texto: ");
     fflush(stdin);
     gets(nombre);
     
     arch=fopen(nombre,"w");
     
     dir=dat.datos; 
     
     for(i=0;i<d.num;i++)
     {
        if(d.metadato[i].clave==1)
            fprintf(arch,"%s %d\t\t",d.metadato[i].nombre,1);
        else
            fprintf(arch,"%s\t\t",d.metadato[i].nombre);
     }       
     
     for(j=0; j<dat.numDatos; j++) 
     {
          fprintf(arch,"\n"); 
          for(i = 0; i<d.num; i++)
          { 
            switch(d.metadato[i].tipo) 
            {
                  case 0: //char 
                              fprintf(arch,"%c\t\t", *(char *) dir); 
                              break;
                  case 1: //int 
                              fprintf(arch,"%d\t\t",*(int *) dir); 
                              break;
                  case 2: // float 
                              fprintf(arch,"%.2f\t\t",*(float*)dir); 
                              break;
                  case 3: //string 
                              fprintf(arch,"%s\t\t", (char *)dir);
                              break;
            } 
            dir = (char *)dir + d.metadato[i].tam; 
          }
         
      }
      system("pause");
     
     fclose(arch);
}
void buscarDatos(Diccionario d,Datos dat)
{
    int i,j;
     void *dir,*busqueda;
     
     dir=dat.datos; 
     
     for(i=0;i<d.num;i++)
     {
        if(d.metadato[i].clave==1)
        { 
           printf("\nCapturando el dato a buscar\n");
           printf("%s: ",d.metadato[i].nombre);  
           switch(d.metadato[i].tipo) 
            {
                  case 0: //char  
                              busqueda=malloc(sizeof(char));
                              scanf("%c", (char *) busqueda); 
                              break;
                  case 1: //int
                              busqueda=malloc(sizeof(int));  
                              scanf("%d",(int *) busqueda); 
                              break;
                  case 2: // float 
                              busqueda=malloc(sizeof(float));
                              scanf("%.2f",(float*)busqueda); 
                              break;
                  case 3: //string 
                              fflush(stdin);
                              busqueda=malloc(sizeof(char)*d.metadato[i].tam);
                              scanf("%s", (char *)busqueda);
                              break;
            } 
        }                 
     }
     for(j=0; j<dat.numDatos; j++) 
     {
          printf("\n");
          for(i = 0; i<d.num; i++)
          {
          if(d.metadato[i].clave==1)
          {  
            switch(d.metadato[i].tipo) 
            {
                  case 0: //char 
                              if(*(char *) dir==*(char *)busqueda)
                              printf("\nel dato se encontro\n"); 
                              break;
                  case 1: //int 
                  
                              if(*(int *) dir==*(int *)busqueda)
                              printf("\nel dato se encontro\n");
                              break;
                  case 2: // float
                              if(*(float *) dir==*(float *)busqueda)
                              printf("\nel dato se encontro\n");
                              break;
                  case 3: //string
                              if(strcmp((char *) dir,(char *)busqueda)==0)
                              printf("\nel dato se encontro\n");
                              break;
            } 
          } 
          dir = (char *)dir + d.metadato[i].tam;
          }
         
      }
      system("pause"); 
}




