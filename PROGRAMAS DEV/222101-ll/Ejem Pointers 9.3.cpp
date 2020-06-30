#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **rptr;
    int *aptr;
    int *pruebaptr;
    int k;
    int nrenglones = 5; /* Ambos, nrenglones y ncolumnas pueden ser */
    int ncolumnas = 8; /* evaluados o leidos en tiempo de ejecucion */
    int renglon, columna;

    /* ahora reservamos memoria para el arreglo completo */
    aptr = (int *)malloc(nrenglones * ncolumnas * sizeof(int));
    if (aptr == NULL)
    {
        puts("\nError al reservar memoria para el arreglo completo.");
        exit(0);
    }
   
    /* ahora reservamos espacio para los apuntadores a renglones */
    rptr = (int **)malloc(nrenglones * sizeof(int *));
    if (rptr == NULL)
    {
        puts("\nError al reservar memoria para los punteros");
        exit(0);
    }

    /* y ahora hacemos que los apuntadores �apunten� */
    for (k = 0; k < nrenglones; k++)
    {
        rptr[k] = aptr + (k * ncolumnas);
    }
    
    /* Ahora demostramos que los punteros a renglones se han incrementado */
    printf("\nDemostramos que los punteros a renglones se han incrementado:");
    printf("\n\nIndice Apuntador(dec) Diferencia(dec)");
    for (renglon = 0; renglon < nrenglones; renglon++)
    {
        printf("\n%d %d", renglon, rptr[renglon]);
        if (renglon > 0)
            printf("%d", ((int)rptr[renglon] - (int)rptr[renglon-1]));
    }
    printf("\n\nY ahora mostramos el arreglo:\n");
    for (renglon = 0; renglon < nrenglones; renglon++)
    {
        for (columna = 0; columna < ncolumnas; columna++)
        {
            rptr[renglon][columna] = renglon + columna;
            printf("%d ", rptr[renglon][columna]);
        }
        putchar('\n');
    }
    puts("\n");
    /* Y aqu� es donde demostramos que efectivamente estamos manejando un
    arreglo bidimensional contenido en un bloque continuo de memoria */
    printf("Demostrando que los elementos son continuos en memoria:\n");
    pruebaptr = aptr;
    for (renglon = 0; renglon < nrenglones; renglon++)
    {
        for (columna = 0; columna < ncolumnas; columna++)
        {
            printf("%d ", *(pruebaptr++));
        }
        putchar('\n');
    }
    system("pause");
    return 0;
}
