#include <stdio.h>
#include <stdlib.h>
long filesize(FILE *stream);
int main(void)
{
   FILE *stream;
   stream = fopen("archivo.dat", "rb+");
   printf("\nFilesize of jueves.dat is %ld bytes\n", filesize(stream));
   fclose(stream);
   system("pause");
   return 0;
}
long filesize(FILE *stream)
{
   long curpos, length;

   curpos = ftell(stream);  /* regresa la posición actual del apuntador */
   fseek(stream, 0L, SEEK_END); /* coloca el apuntador al final */
   length = ftell(stream);  /* regresala la posición actual de apuntador */
   fseek(stream, curpos, SEEK_SET); /*coloca apuntador en "curpos" */
   return length;
}
