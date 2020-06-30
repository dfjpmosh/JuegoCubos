
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   char nombre[20];
   int tipo;
   int tamanio;
   int clave;
}MetaDato;

typedef struct
{ 
   int numDatos;
   MetaDato *metaDato;
}Diccionario;

void crear( Diccionario *);
void leer( Diccionario * );
void imprime( Diccionario );
void guardarArchivo( Diccionario );
void leerArchivo( );
void liberaMemoria( Diccionario * );

int main()
{
   Diccionario  m_diccionario;
   
   int opc;
   
   do
   {
       system( "cls" );
       
       printf( "\n 1.- Crear Diccionario" );
       printf( "\n 2.- Leer Diccionario" );
       printf( "\n 3.- Imprimir Diccionario" );
       printf( "\n 4.- Guardar Archivo" );
       printf( "\n 5.- Leer Archivo" );
       printf( "\n 6.- Salir\n\n" ); 
       printf( " Opcion:  " );
       scanf( "%d", &opc );
       
       switch( opc )
       {
         case 1:  crear( &m_diccionario);
                  break;
          case 2: leer( &m_diccionario );
                  break;
          case 3: imprime( m_diccionario );
                  break;
          case 4: guardarArchivo( m_diccionario);
                  break;
          case 5: leerArchivo( );
                  break;
          default:
                    printf( "\n Error \n" );
          
        }
     }while( opc <= 5 && opc >= 0 );
       
   //liberaMemoria( &m_diccionario);
   system ( "pause" );
}

void crear( Diccionario *dic)
{   
    printf( "\n Introduzca el numero de datos del diccionario :  " );
    scanf( " %d", &dic->numDatos );
    
    dic->metaDato = ( MetaDato * ) malloc( dic->numDatos * sizeof( MetaDato) );
    
    if( dic->metaDato == NULL )
         printf( "\n Error no se pudo reservar memoria\n" );
    else
     {
         printf( "\n La estructura se ha creado con exito\n\n" );
         system ( "pause" );
     }
}
    
void leer( Diccionario *dic )     
{
    int tipoAux;
    
    printf( "\n Introduzca los datos del diccionario...\n" );
    
    for( int i=0; i< dic->numDatos; i++)
    {
      printf( "\n Datos del elemento %d \n", i+1 );
      
      
      printf( " Nombre : " );
      fflush( stdin );
      gets( dic->metaDato[i].nombre );
      
      
      printf( " Tipo (0->char  1->int  2->float  3->string): " );
      fflush( stdin );
      scanf( "%d", &tipoAux );
          switch( tipoAux )
          {
            case 0: dic -> metaDato[i].tipo = 0;
                    dic -> metaDato[i].tamanio = sizeof(char);
                  break;
            case 1: dic -> metaDato[i].tipo = 1;
                    dic->metaDato[i].tamanio = sizeof(int);
                  break;
            case 2: dic -> metaDato[i].tipo = 2;
                    dic->metaDato[i].tamanio = sizeof(float);
                  break;
            case 3: dic -> metaDato[i].tipo = 3;
                  printf( "Tamaño de la cadena: " );
                  scanf( "%d", &tipoAux );
                  dic->metaDato[i].tamanio=tipoAux;
                  break;
           }
      
      printf( " Es un campo Clave? "  );
      scanf ( "%d", &dic->metaDato[i].clave );
      fflush( stdin );
      
    }
    
    system ( "pause" );
}


void imprime( Diccionario dic )
{
   int i;
   
   printf( "\n\n Los datos del diccionario son\n\n:" );
   printf( " Nombre\tTipo\tTamañio\tClave\n" );
   
   for ( i = 0;  i < dic.numDatos; i++ )
   { 
     printf( "\n %d.- %s\t", i+1, dic.metaDato[i].nombre);
     printf( " %d\t", dic.metaDato[i].tipo);
     printf( " %d\t", dic.metaDato[i].tamanio);
     printf( " %d\t", dic.metaDato[i].clave);
   }
   
   system ( "pause" );
}

void guardarArchivo( Diccionario dic)
{
 FILE *ptrA;    
   if( ( ptrA = fopen( "Diccionario.dat", "wb" ) ) != NULL )
   {
      fwrite( &dic.numDatos, sizeof( int ), 1, ptrA );
      fwrite( dic.metaDato, sizeof( MetaDato ), dic.numDatos, ptrA );
      fclose( ptrA );  
      printf( "\n El archivo se guardo con exito\n" );
      
    }else
         printf( "\n Error no se puede crear el archivo\n" );
    
    system ( "pause" );
}

void leerArchivo(  )
{  FILE *ptrA;
   Diccionario dicAux;
   int i = 0;
   int nElem;
   
   printf( "\n Los datos del Diccionario son:\n\n" );
   printf( " Nombre\t  Tipo\t Tamanio\t Clave\n"  );
   ptrA = fopen( "Diccionario.dat", "rb" );
   //crear( &dicAux);
   if( ptrA != NULL )
   {
      fread( &dicAux.numDatos, sizeof( int ), 1, ptrA );
      dicAux.metaDato = ( MetaDato * ) malloc( dicAux.numDatos * sizeof( MetaDato) );
      fread( dicAux.metaDato, sizeof( MetaDato ), dicAux.numDatos, ptrA );
      for( i ; i < dicAux.numDatos; i++ )
          {   
            printf( "\n %d.- %s\t ", i+1, dicAux.metaDato[i].nombre );
            printf( " %d\t", dicAux.metaDato[i].tipo );
            printf( " %d\t", dicAux.metaDato[i].tamanio );
            printf( " %d\t", dicAux.metaDato[i].clave );
          }
   }     
  else
        printf("\n Error no se puede leer el Archivo\n\n" );
  fclose( ptrA);
  system ( "pause" );
}

/* void liberaMemoria( MetaDato *ptr )
{
   free( ptr );
} */
       
