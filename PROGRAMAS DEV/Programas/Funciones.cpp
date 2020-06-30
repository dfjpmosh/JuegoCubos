#include <winbgim.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#define ANCHO 100
#define PROF ANCHO/2
#define D 50

int main()
{
    int x=100,y=100;
       
    initwindow(640,480); //open a 400x300 graphics window
    
        
   setcolor(1);  //color linea
   setfillstyle(SOLID_FILL, 4);    //color relleno
   bar3d(x, y, x+ANCHO, y+ANCHO, PROF, 1);
   floodfill(x+ANCHO+1, y, 1);
   floodfill(x+PROF, y-1, 1);
   }
   
    //getch();
    
    closegraph();        //close graphics window
	return 0;
}
