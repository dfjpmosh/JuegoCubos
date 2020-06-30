#include <winbgim.h>

#define ANCHO 10
#define PROF ANCHO/2

void dibuja_cubo(int x, int y, int color);
void linea_cubos_mouse();
void paraboloide_mouse();
void circulos_mouse();
void menu();

int main()
{
  initwindow(648,486);
  
  linea_cubos_mouse();
  paraboloide_mouse();
  circulos_mouse();
  menu();
  
  do
  {
    if(ismouseclick(WM_LBUTTONDBLCLK) )   /* checa si se presionó dos veces botón derecho */
    {                                    
       if(mousex()>213 && mousey()>100 && mousex()<435 && mousey()<128)
       {
           setfillstyle(1, 2);
           bar(213, 100, 435, 128);
           setfillstyle(1, 11);
           bar(213, 128, 435, 124);
           bar(431, 128, 435, 100);
           setcolor(7);
           rectangle(213, 100, 435, 128);
           setcolor(14);
           settextstyle(1,0,1);
           outtextxy(273, 102,"JUEGO");
           delay(100);
           menu();
       }
       
       if(mousex()>213 && mousey()>180 && mousex()<435 && mousey()<208)
       {
           setfillstyle(1, 2);
           bar(213, 180, 435, 208);
           setfillstyle(1, 11);
           bar(213, 208, 435, 204);
           bar(431, 208, 435, 180);
           setcolor(7);
           rectangle(213, 180, 435, 208);
           setcolor(14);
           settextstyle(1,0,1);
           outtextxy(265, 182,"AYUDA"); 
           delay(100);
           menu();
       }
       
       if(mousex()>213 && mousey()>260 && mousex()<435 && mousey()<288)
       {
           setfillstyle(1, 2);
           bar(213, 260, 435, 288);
           setfillstyle(1, 11);
           bar(213, 288, 435, 284);
           bar(431, 288, 435, 260);
           setcolor(7);
           rectangle(213, 260, 435, 288);
           setcolor(14);
           settextstyle(1,0,1);
           outtextxy(256, 262,"RECORDS");
           delay(100);
           menu();
       }
       
       if(mousex()>213 && mousey()>340 && mousex()<435 && mousey()<368)
       {
           setfillstyle(1, 2);
           bar(213, 340, 435, 368);
           setfillstyle(1, 11);
           bar(213, 368, 435, 364);
           bar(431, 368, 435, 340);
           setcolor(7);
           rectangle(213, 340, 435, 368);
           setcolor(14);
           settextstyle(1,0,1);
           outtextxy(275, 342,"SALIR"); 
           delay(100);
           menu();
       }
       clearmouseclick(WM_LBUTTONDBLCLK);   /* limpia la bandera que indica si se presionó un botón */
    }  
  }while (!ismouseclick(WM_RBUTTONDBLCLK) && !kbhit());  /* checa si se presionó boton derecho dos veces o una tecla */

  closegraph();
  return 0;
}

void menu()
{
  setfillstyle(1, 2);
  bar(213, 100, 435, 128);
  setfillstyle(1, 11);
  bar(213, 100, 435, 104);
  bar(213, 100, 217, 128);
  setcolor(7);
  rectangle(213, 100, 435, 128);
  setcolor(14);
  settextstyle(1,0,1);
  outtextxy(275, 106,"JUEGO"); 
  
  setfillstyle(1, 2);
  bar(213, 180, 435, 208);
  setfillstyle(1, 11);
  bar(213, 180, 435, 184);
  bar(213, 180, 217, 208);
  setcolor(7);
  rectangle(213, 180, 435, 208);
  setcolor(14);
  settextstyle(1,0,1);
  outtextxy(267, 186,"AYUDA"); 
  
  setfillstyle(1, 2);
  bar(213, 260, 435, 288);
  setfillstyle(1, 11);
  bar(213, 260, 435, 264);
  bar(213, 260, 217, 288);
  setcolor(7);
  rectangle(213, 260, 435, 288);
  setcolor(14);
  settextstyle(1,0,1);
  outtextxy(258, 266,"RECORDS");
  
  setfillstyle(1, 2);
  bar(213, 340, 435, 368);
  setfillstyle(1, 11);
  bar(213, 340, 435, 344);
  bar(213, 340, 217, 368);
  setcolor(7);
  rectangle(213, 340, 435, 368);
  setcolor(14);
  settextstyle(1,0,1);
  outtextxy(277, 346,"SALIR"); 
}

// DIBUJA UN CUBO
void dibuja_cubo(int x, int y, int color)
{
     int poly[8];
	 
     setcolor(9);
	 poly[0]=x;             // x1
	 poly[1]=y;             // y1
	 poly[2]=x+ANCHO/2;         // x2
	 poly[3]=y-PROF;           // y2
	 poly[4]=x+ANCHO+ANCHO/2;       // x3
	 poly[5]=y-PROF;           // y3
	 poly[6]=x+ANCHO;           // x4
	 poly[7]=y;             // y4
	setfillstyle(1,color);
	fillpoly(4,poly);
	bar(x,y,x+ANCHO,y+ANCHO);
	rectangle(x,y,x+ANCHO,y+ANCHO);
     poly[0]=x+ANCHO;             // x1
	 poly[1]=y;               // y1
	 poly[2]=x+ANCHO;             // x2
	 poly[3]=y+ANCHO;             // y2
	 poly[4]=x+ANCHO*3/2;         // x3
	 poly[5]=y+ANCHO-PROF;           // y3
	 poly[6]=x+ANCHO*3/2;         // x4
	 poly[7]=y-PROF;             // y4
	setfillstyle(1,color);
	fillpoly(4,poly);
}


//DIBUJA 4 LINEAS DE CUBOS
void linea_cubos_mouse()
{
    int i, ncy=36, nc=52;
    int x1=63, x2=6, x3=620;
	int y1=10, y2=462, y3=64;
	
    // CUBOS HORIZONTALES
    for(i=0;i<nc;i+=2)
    {
      dibuja_cubo(x1+i*ANCHO, y1, 4);
      dibuja_cubo(x1+i*ANCHO, y2, 4);
    }
    
    //CUBOS VERTICALES
    for(i=0;i<ncy;i+=2)
    {
      dibuja_cubo(x2, y3+i*ANCHO, 4);
      dibuja_cubo(x3, y3+i*ANCHO, 4);
    }
}

// DIBUJA LINEAS LA PARABOLOIDE HIPERBOLICA
void paraboloide_mouse()
{
   int i=0, j=0;
   int x=110, y=240, x1=320, y1=30, nl=441;
   
   setcolor(1);
   line(110, 240, 530, 240);//linea horizontal
   line(320, 30, 320, 450);//linea vertical   
   
   while(i<221)
   {
                line(320, 30+i, 320+j, 240);
                line(320, 30+i, 320-j, 240);
                line(320+i, 240, 320, 450-j);
                line(320-i, 240, 320, 450-j);
                j+=7;        
                i+=7;
   }
}

//DIBUJO SEMICIRCULOS EN LA ESQUINAS
void circulos_mouse()
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
   }
   line(28, 50, 28, 429);
   line(50, 28, 589, 28);
   line(50, 451, 589, 451);
   line(611, 50, 611, 429);
}

