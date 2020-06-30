/* Limpia Records
   creando un nuevo archivo de records
   con el mismo nombre*/

#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

#define n 5

typedef struct
{
        char nombre[50];
        int puntos;
}record;

int main()
{
    FILE *f;
    record a[n];
    int i=0;
    
    f=fopen("records.bin", "wb");
    while(i<n)
    {
              strcpy(a[i].nombre, "***");
              a[i].puntos = 0;
              i++;
    }
    fwrite(&a, sizeof(record), n, f);
    fclose(f);
    printf("\n\nSE A CREADO UN ARCHIVO NUEVO DE RECORDS\n\n");
    system("pause");
}
