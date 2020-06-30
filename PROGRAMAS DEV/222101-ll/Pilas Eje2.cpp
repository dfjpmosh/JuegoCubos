#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int puntos;
    char nom[30];
}Record;

typedef struct
{ 
    Record *pila;
    int tope;
    int tam;
}Pila;


int push(Pila *p, Record r); //Insertar en la Pila
int pop(Pila *p, Record *r); //Sacar de la Pila
int pilaVacia(Pila p);
int pilaLlena(Pila p);
int inicializaPila(Pila *p, int tam);
void imprimir(Pila p);

int main()
{
     int opcion, n;
     Pila p;
     Record r;
          
     do{
		 system("cls");
		 printf("\n\n  M  E  N  U");
		 printf("\n  1.- Crear Pila");
		 printf("\n  2.- Insertar en Pila");
		 printf("\n  3.- Sacar de Pila");
		 printf("\n  4.- Imprimir Pila");
		 printf("\n  5.- Salir");
		 printf("\n\n  Opci¢n: ");
		 scanf("%d",&opcion);
		 switch(opcion)
		 {
			case 1: printf("Cuantos Datos: ");
			        scanf("%d", &n);
                    inicializaPila(&p, n);
			        break;
			case 2: printf("Puntos: ");
			        scanf("%d", &r.puntos);
			        printf("Nombre: ");
			        fflush(stdin);
			        gets(r.nom);
			        if(push(&p, r)==0)
			        {
                       printf("\nPila Llena\n");   
                       system("pause");
                    }
			        break;
			case 3: if(pop(&p, &r)==0)
			        {
                       printf("\nPila Vacia\n");   
                    }
                    else
                    {
                       printf("Puntos: %d\n", r.puntos);
                       printf("Nombre: %s\n", r.nom);
                    }
                    system("pause");
                    break;
            case 4: imprimir(p);
                    putchar('\n');
                    system("pause");
			        break;
			}
	}while(opcion!=5);
}

int pilaVacia(Pila p)
{
      // 1 Quiere decir que la pila esta vacia y un 0 si no esta
      int reg = 1;			
      if(p.tope > 0)                          			
               reg = 0;			
      return(reg);			
}

int pilaLlena(Pila p)
{
      //Regresa un 1 si esta llena, esto es, tope == tam
      int reg = 1;			
      if(p.tope < p.tam)                          			
               reg = 0;			
      return(reg);			
    	}

int inicializaPila(Pila *p, int tam)
{  
     int res=0;
     
      p->pila = (Record*)malloc(sizeof(Record) * tam);
     
     if(p->pila)
     {
         p->tam = tam;
         p->tope = 0;   
         res = 1;
     }
     return (res);
}

//insercion de nuevo dato
int push(Pila *p, Record r)
{
      int reg = 0;			// 2.1
      if( ! pilaLlena(*p) )                 //  1
      {
             p->pila[p->tope] = r;	// 1.1
             p->tope++;			// 1.2
             reg = 1;			// 1.3
      }
      return(reg);			//1.3, 2.1
}

//sacar o eliminar el dato
int pop(Pila *p, Record *r)
{
      int reg = 0;
      if( ! pilaVacia(*p))
      {
             p->tope--;
            *r=p->pila[p->tope];
             reg = 1;
      }
      return(reg);
}

void imprimir(Pila p)
{
     int i;
     
     if(pilaVacia(p) == 1)
         printf("Pila Vacia");
     else
         for(i=p.tope-1; i>=0; i--)
         {
            printf("Puntos: %d\n", p.pila[i].puntos);
            printf("Nombre: %s\n", p.pila[i].nom);
         }
}
