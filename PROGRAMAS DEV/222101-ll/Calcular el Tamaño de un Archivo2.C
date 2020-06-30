#include <stdio.h>
#include <stdlib.h>


int main(void)
{
   FILE *stream;
   long curpos, length; 
   
   stream = fopen("archivo.dat", "rb+");
   curpos = ftell(stream);  /* regresa la posición actual del apuntador */
   fseek(stream, 0L, SEEK_END); /* coloca el apuntador al final */
   length = ftell(stream);  /* regresala la posición actual de apuntador */
   fseek(stream, curpos, SEEK_SET); /*coloca apuntador en "curpos" */
   printf("\nFilesize of archivo.dat is %ld bytes\n", length);
   fclose(stream);
   system("pause");
   return 0;
}
