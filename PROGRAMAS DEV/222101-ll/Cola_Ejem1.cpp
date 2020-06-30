#include<stdio.h>
#include<stdlib.h>

typedef struct
{ 
    int *cola;
    int inicio, final;
    int tam;
}Cola;

int inicializaCola(Cola *c, int tam);
int colaVacia(Cola c);
int colaLlena(Cola c);
int enqueue(Cola * c, int d);
int dequeue(Cola * c, int *d);
void imprimir(Cola c);

int main()
{
     int opcion, d, n;
     Cola c;
          
     do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Crear Cola");
		 printf("\n  2.- Insertar en Cola");
		 printf("\n  3.- Sacar de Cola");
		 printf("\n  4.- Imprimir Cola");
		 printf("\n  5.- Salir");
		 printf("\n\n  Opci¢n: ");
		 scanf("%d",&opcion);
		 switch(opcion)
		 {
			case 1: printf("Cuantos Datos: ");
			        scanf("%d", &n);
                    inicializaCola(&c, n);
			        break;
			case 2: printf("Dato: ");
			        scanf("%d", &d);
			        if(enqueue(&c, d)==0)
			        {
                       printf("\nCola Llena\n");   
                       system("pause");
                    }
			        break;
			case 3: if(dequeue(&c, &d)==0)
			        {
                       printf("\nCola Vacia\n");   
                    }
                    else
                       printf("Dato: %d\n", d);
                    system("pause");
                    break;
            case 4: imprimir(c);
                    putchar('\n');
                    system("pause");
			        break;
			}
	}while(opcion!=5);
}

int inicializaCola(Cola * c, int tam)
{  
     int res=0;
     
     c->cola = (int*)malloc(sizeof(int) * tam);
     
     if(c->cola)
     {
         c->tam = tam;
         c->inicio =c->final = 0;   
         res = 1;
     }
     return (res);
}

int colaVacia(Cola c)
{
      int reg;
      
      reg = c.inicio == c.final ? 1 : 0;			
		
      return(reg);			
}

int colaLlena(Cola c)
{
      int reg;

      reg = (c.final + 1) % c.tam == c.inicio? 1:0;		
      
      return(reg);			
}

int enqueue(Cola * c, int d)
{
      int reg = 0;					// 2.1
      if( ! colaLlena(*c) )                 		//  1
      {
             c->cola[c->final] = d;			// 1.1
             c->final = (c->final + 1) % c->tam;	// 1.2
             reg = 1;					// 1.3
      }
      return(reg);	
}

int dequeue(Cola * c, int *d)
{
      int reg = 0;						// 2.1
      if( ! colaVacia(*c))                			 	//  1
      { 
           *d = c->cola[c->inicio];				// 1.1		
            c->inicio = (c->inicio + 1) % c->tam;		// 1.2        	
             reg = 1;						// 1.3
      }
      return(reg);						//1.3, 2.1
}

void imprimir(Cola c)
{
     int i;
     
     if(colaVacia(c) == 1)
         printf("Pila Vacia");
     else
         for(i=c.inicio; i<c.final; i++)
         {
            printf("Dato: %d\n", c.cola[i]);
         }
}
