#include <winbgim.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>

#define ANCHO 10
#define PROF ANCHO/2

void cubo(int x, int y);
void pared_cubos();

int main()
{
	
    initwindow(648,486); // HABRE UNA VENTANA DE TAMAÑO XY
    
    //int x=100, y=100;
    pared_cubos();
	//cubo(x, y);
	
    getch();
    
    closegraph();        // CIERRA GRAFICOS
	return 0;
}

// DIBUJA UN CUBO
void cubo(int x, int y)
{
   setcolor(1);  //color linea
   setfillstyle(SOLID_FILL, 4);    //color relleno
   bar3d(x, y, x+ANCHO, y+ANCHO, PROF, 1);
   floodfill(x+ANCHO+ANCHO/3, y, 1);
   floodfill(x+PROF, y-PROF/3, 1);
}

//DIBUJA PARED DE CUBOS
void pared_cubos()
{    
     int x=100, y=100, nc=5;
     int i,j,k;

     for(k=0;k<nc;k++)
     {
         for(j=0; j<nc; j++)
	     {
	         //cubo(x+j*PROF,y+k*PROF);
	         for(i=0; i<nc; i++)
	         {
                 cubo(x+i*ANCHO,y+j*ANCHO);
	             delay(500);
             }
	     }
     }

}
