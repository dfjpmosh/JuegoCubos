#include <stdio.h>
#include <stdlib.h>

int ***crea(int nrenglones, int ncolumnas, int ncapas);
void captura(int ***rptr, int nrenglones, int ncolumnas, int ncapas);
void imprime(int ***rptr, int nrenglones, int ncolumnas, int ncapas);

int main()
{
    int ***rptr;
    int nren, ncol, ncap;
    
    printf("Tamaño Del Arreglo:\n\n");
    printf("Numero de Renglones: ");
    scanf("%d", &nren);
    printf("Numero de Columnas: ");
    scanf("%d", &ncol);
    printf("Numero de Capas: ");
    scanf("%d", &ncap);
    
    rptr=crea(nren, ncol, ncap);
    captura(rptr, nren, ncol, ncap);
    imprime(rptr, nren, ncol, ncap);
    
    system("pause");
}

int ***crea(int nrenglones, int ncolumnas, int ncapas)
{
    int ***ptr;
    int capa,renglon;
    
    ptr=(int***) malloc(ncapas * sizeof(int **));
    for(capa=0; capa<ncapas; capa++)
    {
        ptr[capa]=(int**)malloc(nrenglones * sizeof(int*));
        for (renglon = 0; renglon < nrenglones; renglon++)
           ptr[capa][renglon] = (int*) malloc(ncolumnas * sizeof(int));
    }
    
    return ptr;
}

void captura(int ***rptr, int nrenglones, int ncolumnas, int ncapas)
{
     int renglon, columna, capa;
     
     printf("\n\nCapturando Datos Del Arreglo\n\n");
     for(capa=0; capa<ncapas; capa++)
        for(renglon=0; renglon<nrenglones; renglon++)
           for(columna=0; columna<ncolumnas; columna++)
           {
              printf("Dato [%d][%d][%d]: ", capa, renglon, columna);
              scanf("%d", &rptr[capa][renglon][columna]);
              //scanf("%d", (*(rptr+1)+1));
           }
}
     
void imprime(int ***rptr, int nrenglones, int ncolumnas, int ncapas)
{
     int renglon, columna, capa;
     
     printf("\n\nDatos Del Arreglo: \n\n");
     for(capa=0; capa<ncapas; capa++)
     {
        for(renglon=0; renglon<nrenglones; renglon++)
        {
           for(columna=0; columna<ncolumnas; columna++)
           {
               printf(" %d ", rptr[capa][renglon][columna]);
               //printf("%d", *(*(rptr + 1) + 1));
           }
           putchar('\n');
        }
        putchar('\n');
     }
     printf("\n\n");
}
