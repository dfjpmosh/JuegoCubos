/* Ejemplo de apuntadores a funciones
   Libro: Fundamentos de Programación Algoritmos y Estructuras de Datos
   Autor: Luis Joyanes Aguilar
   Editorial: Mc Graw Hill;  2da Edición*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int comp(const void *i, const void *j);

int main()
{
	int i;
	char cad[] = "area de computacion e informatica";
	
	printf("\nArreglo original: \n");
	for (i=0; i<strlen(cad); i++)
		printf("%c", cad[i]);

	qsort(cad, strlen(cad), sizeof(char), comp );

	printf("\n\nArreglo ordenado: \n");
	for (i=0; i<strlen(cad); i++)
		printf("%c", cad[i]);

	printf("\n\n");
	system("pause");
}

int comp(const void *i, const void *j)
{
	char *a, *b;

	a = (char *) i; /* Para forzar void * al tipo char *, se hace cast */ 
	b = (char *) j; /*     empleando (char *)                          */
	return *a - *b;  
}

