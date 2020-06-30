#include<winbgim.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>

#define ANCHO 10
#define PROF ANCHO/2

void cubo(int x, int y);
void linea_cubos();
void paraboloide();
void circulos();
void comentarios(void);

int main()
{
	
    initwindow(648,486); // HABRE UNA VENTANA DE TAMAÑO XY
    
    linea_cubos();
	paraboloide();
	circulos();
	comentarios();
	
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
   floodfill(x+ANCHO+1, y, 1);
   floodfill(x+PROF, y-1, 1);
}


//DIBUJA 4 LINEAS DE CUBOS
void linea_cubos()
{
    int i, ncy=36, nc=52;
    int x1=63, x2=6, x3=620;
	int y1=10, y2=462, y3=64;
	
    // CUBOS HORIZONTALES
    for(i=0;i<nc;i+=2)
    {
      cubo(x1+i*ANCHO, y1);
      cubo(x1+i*ANCHO, y2);
      delay(100);
    }
    
    //CUBOS VERTICALES
    for(i=0;i<ncy;i+=2)
    {
      cubo(x2, y3+i*ANCHO);
      cubo(x3, y3+i*ANCHO);
      delay(100);
    }
}

// DIBUJA LINEAS LA PARABOLOIDE HIPERBOLICA
void paraboloide()
{
   int i=0, j=0;
   int x=110, y=240, x1=320, y1=30, nl=441;
   
   setcolor(2);
   line(110, 240, 530, 240);//linea horizontal
   line(320, 30, 320, 450);//linea vertical   
   
   while(i<221)
   {
                line(320, 30+i, 320+j, 240);
                line(320, 30+i, 320-j, 240);
                line(320+i, 240, 320, 450-j);
                line(320-i, 240, 320, 450-j);
                delay(250);
                j+=7;        
                i+=7;
   }
}

void comentarios(void)
{
   rectangle(0, 0, 639, 479);
   
   delay(1000);

   setcolor(1);
   settextstyle(9, 0, 5);
   outtextxy(173, 50, "CUBOMAN");
   delay(200);
   setcolor(7);
   settextstyle(6, 0, 3);
   outtextxy(240, 160, "U A S L P");
   delay(200);
   settextstyle(8, 0, 2);
   outtextxy(200, 200, "FACULTAD DE INGENIERÍA");
   delay(200);
   outtextxy(125, 240, "ÁREA DE COMPUTACIÓN E INFORMÁTICA");
   delay(200);
   setcolor(9);
   settextstyle(8, 0, 2);
   outtextxy(110, 280, "ESTRUCTURAS DE DATOS Y ALGORITMOS A");
   delay(200);
   setcolor(9);
   settextstyle(8, 0, 2);
   outtextxy(140, 320, "PROF. JUAN CARLOS CUEVAS TELLO");
   delay(200);
   setcolor(1);
   settextstyle(8, 0, 2);
   outtextxy(140, 360, "DANIEL FELICIANO JIMÉNEZ PIÑA");
   delay(200);
   settextstyle(8, 0, 2);
   outtextxy(220, 400, "PROYECTO No: ###");

}

//DIBUJO SEMICIRCULOS EN LA ESQUINAS
void circulos()
{
   int x=0, y=0, rad=4, ncc=15;
   int i;
   
   setcolor(1);
   rectangle(0, 0, 639, 479);
   for(i=0;i<ncc;i++)
   {
      circle(x, y, rad*i);
      circle(x, y+479, rad*i);
      circle(x+639, y, rad*i);
      circle(x+639, y+479, rad*i);
      delay(150);
   }
   line(28, 50, 28, 429);
   line(50, 28, 589, 28);
   line(50, 451, 589, 451);
   line(611, 50, 611, 429);
}
