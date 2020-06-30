#include <stdio.h>
#include <stdlib.h>

int **crea(int nrenglones, int ncolumnas);
void captura(int **rptr, int nrenglones, int ncolumnas);
void imprime(int **rptr, int nrenglones, int ncolumnas);

int main()
{
    int **rptr;
    int nren,ncol;
    
    printf("Numero de Renglones: ");
    scanf("%d", &nren);
    printf("Numero de Columnas: ");
    scanf("%d", &ncol);
    
    rptr=crea(nren, ncol);
    captura(rptr, nren, ncol);
    imprime(rptr, nren, ncol);
    
    system("pause");
}

int **crea(int nrenglones, int ncolumnas)
{
    int **rptr;
    int *aptr;
    int k;
    
    aptr = (int *)malloc(nrenglones * ncolumnas * sizeof(int));
    rptr = (int **)malloc(nrenglones * sizeof(int *));
    for (k = 0; k < nrenglones; k++)
    {
        rptr[k] = aptr + (k * ncolumnas);
    }
    
    return rptr;
}

void captura(int **rptr, int nrenglones, int ncolumnas)
{
     int renglon, columna;
     
     printf("\n\nCapturando Datos Del Arreglo\n\n");
     for(renglon=0; renglon<nrenglones; renglon++)
        for(columna=0; columna<ncolumnas; columna++)
        {
            printf("Dato [%d][%d]: ", renglon, columna);
            scanf("%d", &rptr[renglon][columna]);
            //scanf("%d", (*(rptr+1)+1));
        }
}
     
void imprime(int **rptr, int nrenglones, int ncolumnas)
{
     int renglon, columna;
     
     printf("\n\nDatos Del Arreglo: \n\n");
     for(renglon=0; renglon<nrenglones; renglon++)
     {
        for(columna=0; columna<ncolumnas; columna++)
        {
            printf("%d", rptr[renglon][columna]);
            //printf("%d", *(*(rptr + 1) + 1));
        }
        putchar('\n');
     }
     printf("\n\n");
}
