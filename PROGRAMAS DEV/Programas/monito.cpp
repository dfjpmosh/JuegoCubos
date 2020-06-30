#include <winbgim.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>


#define MAX RENX

#define RENX   17
#define COLY   17            //(x, y, z)
#define PROFZ  17
#define ANCHO 10
#define PROF ANCHO/2
#define MAXCUB 10
#define NUMCAS 8
#define NUMPTS 4
#define TAMMON 13
#define BLUE 1
#define RED 4
#define GREEN 3
#define WHITE 15

typedef struct
{
	int x;
	int y;
	int col_r;
	int col_b;
	int existe;

}cubito;

typedef struct
{
	int x;
	int y;
	int z;
}cord;

void guarda(int x, int y, cubito contenedor[RENX][COLY][PROFZ], cord monito[TAMMON]);
void pintacontenedor(cubito contenedor[RENX][COLY][PROFZ]);
void modificacontenedor(cubito contenedor[RENX][COLY][PROFZ]);
void cubo( int x, int y, int col_r, int col_b);
void mueve_cubo(cubito contenedor[RENX][COLY][PROFZ], cord monito[TAMMON]);
void salir(void);



int main()
{
	cubito contenedor[RENX][COLY][PROFZ];
	cord monito[TAMMON];
	int x=250, y=220;

	guarda(x, y, contenedor, monito);
	initwindow(400,400);
	mueve_cubo(contenedor, monito);
	getch();

	closegraph();        //close graphics window
	return 0;
}

void guarda(int x, int y, cubito contenedor[RENX][COLY][PROFZ], cord monito[TAMMON])
{
	int i, j, k;



	for (k=0;k<PROFZ;k++)
	{
		for (j=0;j<COLY;j++)
		{
			for(i=0;i<RENX;i++)
			{
				contenedor[i][j][k].x=x+i*ANCHO-k*PROF;
				contenedor[i][j][k].y=y-j*ANCHO+k*PROF;
				contenedor[i][j][k].col_r=BLUE;
				contenedor[i][j][k].col_b=WHITE;
				contenedor[i][j][k].existe=0;

			}

		}

	}

    for (j=0;j<PROFZ;j++)
	{
		for(i=0;i<RENX;i++)
		{
			contenedor[i][j][0].col_r=RED;
			contenedor[i][j][0].existe=1;

		}
	}

	contenedor[RENX/2][COLY/2][PROFZ-1].existe=1;
	contenedor[RENX/2][COLY/2][PROFZ-1].col_r=BLUE;
	contenedor[RENX/2][COLY/2][PROFZ-1].col_b=WHITE;
	monito[0].x=RENX/2;
	monito[0].y=COLY/2;
	monito[0].z=PROFZ-1;

	contenedor[RENX/2][COLY/2+1][PROFZ-1].existe=1;
	contenedor[RENX/2][COLY/2+1][PROFZ-1].col_r=BLUE;
	contenedor[RENX/2][COLY/2+1][PROFZ-1].col_b=WHITE;
	monito[1].x=RENX/2;
	monito[1].y=COLY/2+1;
	monito[1].z=PROFZ-1;

	contenedor[RENX/2][COLY/2+2][PROFZ-1].existe=1;
	contenedor[RENX/2][COLY/2+2][PROFZ-1].col_r=11;
	contenedor[RENX/2][COLY/2+2][PROFZ-1].col_b=WHITE;
	monito[2].x=RENX/2;
	monito[2].y=COLY/2+2;
	monito[2].z=PROFZ-1;

	contenedor[RENX/2-1][COLY/2-1][PROFZ-1].existe=1;
	contenedor[RENX/2-1][COLY/2-1][PROFZ-1].col_r=4;
	contenedor[RENX/2-1][COLY/2-1][PROFZ-1].col_b=WHITE;
	monito[3].x=RENX/2-1;
	monito[3].y=COLY/2-1;
	monito[3].z=PROFZ-1;

	contenedor[RENX/2-2][COLY/2-2][PROFZ-1].existe=1;
	contenedor[RENX/2-2][COLY/2-2][PROFZ-1].col_r=4;
	contenedor[RENX/2-2][COLY/2-2][PROFZ-1].col_b=WHITE;
	monito[4].x=RENX/2-2;
	monito[4].y=COLY/2-2;
	monito[4].z=PROFZ-1;
	
	contenedor[RENX/2+1][COLY/2-1][PROFZ-1].existe=1;
	contenedor[RENX/2+1][COLY/2-1][PROFZ-1].col_r=4;
	contenedor[RENX/2+1][COLY/2-1][PROFZ-1].col_b=WHITE;
	monito[5].x=RENX/2+1;
	monito[5].y=COLY/2-1;
	monito[5].z=PROFZ-1;

	contenedor[RENX/2+2][COLY/2-2][PROFZ-1].existe=1;
	contenedor[RENX/2+2][COLY/2-2][PROFZ-1].col_r=4;
	contenedor[RENX/2+2][COLY/2-2][PROFZ-1].col_b=WHITE;
	monito[6].x=RENX/2+2;
	monito[6].y=COLY/2-2;
	monito[6].z=PROFZ-1;

	contenedor[RENX/2-1][COLY/2+1][PROFZ-1].existe=1;
	contenedor[RENX/2-1][COLY/2+1][PROFZ-1].col_r=BLUE;
	contenedor[RENX/2-1][COLY/2+1][PROFZ-1].col_b=WHITE;
	monito[7].x=RENX/2-1;
	monito[7].y=COLY/2+1;
	monito[7].z=PROFZ-1;

	contenedor[RENX/2-2][COLY/2+1][PROFZ-1].existe=1;
	contenedor[RENX/2-2][COLY/2+1][PROFZ-1].col_r=11;
	contenedor[RENX/2-2][COLY/2+1][PROFZ-1].col_b=WHITE;
	monito[8].x=RENX/2-2;
	monito[8].y=COLY/2+1;
	monito[8].z=PROFZ-1;

	contenedor[RENX/2-2][COLY/2+1][PROFZ-2].existe=1;
	contenedor[RENX/2-2][COLY/2+1][PROFZ-2].col_r=11;
	contenedor[RENX/2-2][COLY/2+1][PROFZ-2].col_b=WHITE;
	monito[9].x=RENX/2-2;
	monito[9].y=COLY/2+1;
	monito[9].z=PROFZ-2;

	contenedor[RENX/2+1][COLY/2+1][PROFZ-1].existe=1;
	contenedor[RENX/2+1][COLY/2+1][PROFZ-1].col_r=BLUE;
	contenedor[RENX/2+1][COLY/2+1][PROFZ-1].col_b=WHITE;
	monito[10].x=RENX/2+1;
	monito[10].y=COLY/2+1;
	monito[10].z=PROFZ-1;

	contenedor[RENX/2+2][COLY/2+1][PROFZ-1].existe=1;
	contenedor[RENX/2+2][COLY/2+1][PROFZ-1].col_r=11;
	contenedor[RENX/2+2][COLY/2+1][PROFZ-1].col_b=WHITE;
	monito[11].x=RENX/2+2;
	monito[11].y=COLY/2+1;
	monito[11].z=PROFZ-1;

	contenedor[RENX/2+2][COLY/2+1][PROFZ-2].existe=1;
	contenedor[RENX/2+2][COLY/2+1][PROFZ-2].col_r=11;
	contenedor[RENX/2+2][COLY/2+1][PROFZ-2].col_b=WHITE;
	monito[12].x=RENX/2+2;
	monito[12].y=COLY/2+1;
	monito[12].z=PROFZ-2;
}

void pintacontenedor(cubito contenedor[RENX][COLY][PROFZ])
{
	int i,j,k;

    setcolor(WHITE);

	rectangle(contenedor[0][COLY-1][0].x+PROF, contenedor[0][COLY-1][0].y-PROF, contenedor[0][COLY-1][0].x+ANCHO*COLY+PROF, contenedor[0][COLY-1][PROFZ].y+ANCHO-PROF);
	rectangle(contenedor[RENX-1][COLY-1][PROFZ-1].x-ANCHO*(COLY-1), contenedor[RENX-1][COLY-1][PROFZ-1].y, contenedor[RENX-1][0][PROFZ-1].x+ANCHO, contenedor[RENX-1][0][PROFZ-1].y+ANCHO);
	line(contenedor[0][COLY-1][0].x+PROF, contenedor[0][COLY-1][0].y-PROF, contenedor[RENX-1][COLY-1][PROFZ-1].x-ANCHO*(COLY-1), contenedor[RENX-1][COLY-1][PROFZ-1].y);
	line(contenedor[0][COLY-1][0].x+ANCHO*COLY+PROF, contenedor[0][COLY-1][PROFZ].y+ANCHO-PROF, contenedor[RENX-1][0][PROFZ-1].x+ANCHO, contenedor[RENX-1][0][PROFZ-1].y+ANCHO);
	line(contenedor[0][COLY-1][0].x+ANCHO*COLY+PROF, contenedor[0][COLY-1][0].y-PROF, contenedor[RENX-1][0][PROFZ-1].x+ANCHO, contenedor[RENX-1][COLY-1][PROFZ-1].y);
	line(contenedor[0][COLY-1][0].x+PROF, contenedor[0][COLY-1][PROFZ].y+ANCHO-PROF, contenedor[RENX-1][COLY-1][PROFZ-1].x-ANCHO*(COLY-1), contenedor[RENX-1][0][PROFZ-1].y+ANCHO);

	for (k=0;k<PROFZ;k++)
	{
		for (j=0;j<COLY;j++)
		{
			for(i=0;i<RENX;i++)
			{
				if (contenedor[i][j][k].existe==1)
				{
					cubo(contenedor[i][j][k].x, contenedor[i][j][k].y, contenedor[i][j][k].col_r, contenedor[i][j][k].col_b);

				}
			 }
		 }
	 }

	
}


void cubo( int x, int y, int col_r, int col_b)
{
 int puntos[NUMCAS];

 setcolor(col_b);
/* Cara de Enfrente               */
 puntos[0]=x;
 puntos[1]=y;
 puntos[2]=x+ANCHO;
 puntos[3]=y;
 puntos[4]=x+ANCHO;
 puntos[5]=y+ANCHO;
 puntos[6]=x;
 puntos[7]=y+ANCHO;
 setfillstyle(SOLID_FILL,col_r);
 fillpoly(NUMPTS,puntos);
 floodfill(x+1,y+1,col_r);


 /* Cara Superior tapa                  */
 puntos[0]=x;
 puntos[1]=y;
 puntos[2]=x+PROF;
 puntos[3]=y-PROF;
 puntos[4]=x+ANCHO+PROF;
 puntos[5]=y-PROF;
 puntos[6]=x+ANCHO;
 puntos[7]=y;
 setfillstyle(1,col_r);
 fillpoly(NUMPTS,puntos);
 floodfill(x+1,y+1,col_r);

 /*                  lateral */
 puntos[0]=x+ANCHO;
 puntos[1]=y;
 puntos[2]=x+ANCHO+PROF;
 puntos[3]=y-PROF;
 puntos[4]=x+ANCHO+PROF;
 puntos[5]=y-PROF+ANCHO;
 puntos[6]=x+ANCHO;
 puntos[7]=y+ANCHO;
 setfillstyle(1,col_r);
 fillpoly(NUMPTS,puntos);
 floodfill(x+1,y+1,col_r);
}


void salir(void)
{
	setcolor(BLUE);
	outtextxy(200,450,"gracias por usar el programa");
	getch();
	cleardevice();
	closegraph();
}

void mueve_cubo(cubito contenedor[RENX][COLY][PROFZ], cord monito[TAMMON])
{

		int t, i;



		do
		{        for(i=0;i<=12;i++)
			 {
				contenedor[monito[i].x][monito[i].y][monito[i].z].existe=1;
			 }

			 cleardevice();
			 pintacontenedor(contenedor);

			 for(i=0;i<=12;i++)
			 {
			 contenedor[monito[i].x][monito[i].y][monito[i].z].existe=0;
			 contenedor[monito[i].x][monito[i].y][monito[i].z].col_r=contenedor[monito[i].x][monito[i].y][monito[i].z].col_r;
			 }


			 t=getch();
			 if(t==0)
			 t=getch();
			 switch(t)
			 {


	case 72: if(monito[0].y<MAX-3 && contenedor[monito[0].x][monito[0].y+1][monito[0].z].existe==0)  //ARRIBA
		 monito[0].y++;
		 contenedor[monito[0].x][monito[0].y][monito[0].z].existe=1;


		 if(monito[1].y<MAX-2 && contenedor[monito[1].x][monito[1].y+1][monito[1].z].existe==0)  //ARRIBA
		 monito[1].y++;
		 contenedor[monito[1].x][monito[1].y][monito[1].z].existe=1;

		 if(monito[2].y<MAX-1 && contenedor[monito[2].x][monito[2].y+1][monito[2].z].existe==0)  //ARRIBA
		 monito[2].y++;
		 contenedor[monito[2].x][monito[2].y][monito[2].z].existe=1;

		 if(monito[3].y<MAX-4 && contenedor[monito[3].x][monito[3].y+1][monito[3].z].existe==0)  //ARRIBA
		 monito[3].y++;
		 contenedor[monito[3].x][monito[3].y][monito[3].z].existe=1;

		 if(monito[4].y<MAX-5 && contenedor[monito[4].x][monito[4].y+1][monito[4].z].existe==0)  //ARRIBA
		 monito[4].y++;
		 contenedor[monito[4].x][monito[4].y][monito[4].z].existe=1;

		 if(monito[5].y<MAX-4 && contenedor[monito[5].x][monito[5].y+1][monito[5].z].existe==0)  //ARRIBA
		 monito[5].y++;
		 contenedor[monito[5].x][monito[5].y][monito[5].z].existe=1;

		 if(monito[6].y<MAX-5 && contenedor[monito[6].x][monito[6].y+1][monito[6].z].existe==0)  //ARRIBA
		 monito[6].y++;
		 contenedor[monito[6].x][monito[6].y][monito[6].z].existe=1;

		 for(i=7;i<=12;i++)
		 {
		 if(monito[i].y<MAX-2 && contenedor[monito[i].x][monito[i].y+1][monito[i].z].existe==0)  //ARRIBA
		 monito[i].y++;
		 contenedor[monito[i].x][monito[i].y][monito[i].z].existe=1;
		 }
		 break;


	case 80: if(monito[0].y>2 && contenedor[monito[0].x][monito[0].y-1][monito[0].z].existe==0)     //ABAJO
		 monito[0].y--;
		 contenedor[monito[0].x][monito[0].y][monito[0].z].existe=1;

		 if(monito[1].y>3 && contenedor[monito[1].x][monito[1].y-1][monito[1].z].existe==0)     //ABAJO
		 monito[1].y--;
		 contenedor[monito[1].x][monito[1].y][monito[1].z].existe=1;

		 if(monito[2].y>4 && contenedor[monito[2].x][monito[2].y-1][monito[2].z].existe==0)     //ABAJO
		 monito[2].y--;
		 contenedor[monito[2].x][monito[2].y][monito[2].z].existe=1;

		 if(monito[3].y>1 && contenedor[monito[3].x][monito[3].y-1][monito[3].z].existe==0)  //ARRIBA
		 monito[3].y--;
		 contenedor[monito[3].x][monito[3].y][monito[3].z].existe=1;

		 if(monito[4].y>0 && contenedor[monito[4].x][monito[4].y-1][monito[4].z].existe==0)  //ARRIBA
		 monito[4].y--;
		 contenedor[monito[4].x][monito[4].y][monito[4].z].existe=1;

		 if(monito[5].y>1 && contenedor[monito[5].x][monito[5].y-1][monito[5].z].existe==0)  //ARRIBA
		 monito[5].y--;
		 contenedor[monito[5].x][monito[5].y][monito[5].z].existe=1;

		 if(monito[6].y>0 && contenedor[monito[6].x][monito[6].y-1][monito[6].z].existe==0)  //ARRIBA
		 monito[6].y--;
		 contenedor[monito[6].x][monito[6].y][monito[6].z].existe=1;

		 for(i=7;i<=12;i++)
		 {
		 if(monito[i].y>3 && contenedor[monito[i].x][monito[i].y-1][monito[i].z].existe==0)  //ARRIBA
		 monito[i].y--;
		 contenedor[monito[i].x][monito[i].y][monito[i].z].existe=1;
		 }
		 break;


	case 77: if(monito[0].x<MAX-3 && contenedor[monito[0].x+1][monito[0].y][monito[0].z].existe==0)   //DERECHA
		 monito[0].x++;
		 contenedor[monito[0].x][monito[0].y][monito[0].z].existe=1;

		 if(monito[1].x<MAX-3 && contenedor[monito[1].x+1][monito[1].y][monito[1].z].existe==0)   //DERECHA
		 monito[1].x++;
		 contenedor[monito[1].x][monito[1].y][monito[1].z].existe=1;

		 if(monito[2].x<MAX-3 && contenedor[monito[2].x+1][monito[2].y][monito[2].z].existe==0)   //DERECHA
		 monito[2].x++;
		 contenedor[monito[2].x][monito[2].y][monito[2].z].existe=1;

		 if(monito[3].x<MAX-4 && contenedor[monito[3].x+1][monito[3].y][monito[3].z].existe==0)  //ARRIBA
		 monito[3].x++;
		 contenedor[monito[3].x][monito[3].y][monito[3].z].existe=1;

		 if(monito[4].x<MAX-5 && contenedor[monito[4].x+1][monito[4].y][monito[4].z].existe==0)  //ARRIBA
		 monito[4].x++;
		 contenedor[monito[4].x][monito[4].y][monito[4].z].existe=1;

		 if(monito[5].x<MAX-2 && contenedor[monito[5].x+1][monito[5].y][monito[5].z].existe==0)  //ARRIBA
		 monito[5].x++;
		 contenedor[monito[5].x][monito[5].y][monito[5].z].existe=1;

		 if(monito[6].x<MAX-1 && contenedor[monito[6].x+1][monito[6].y][monito[6].z].existe==0)  //ARRIBA
		 monito[6].x++;
		 contenedor[monito[6].x][monito[6].y][monito[6].z].existe=1;

		 if(monito[7].x<MAX-4 && contenedor[monito[7].x+1][monito[7].y][monito[7].z].existe==0)  //ARRIBA
		 monito[7].x++;
		 contenedor[monito[7].x][monito[7].y][monito[7].z].existe=1;

		 if(monito[8].x<MAX-5 && contenedor[monito[8].x+1][monito[8].y][monito[8].z].existe==0)  //ARRIBA
		 monito[8].x++;
		 contenedor[monito[8].x][monito[8].y][monito[8].z].existe=1;

		 if(monito[9].x<MAX-5 && contenedor[monito[9].x+1][monito[9].y][monito[9].z].existe==0)  //ARRIBA
		 monito[9].x++;
		 contenedor[monito[9].x][monito[9].y][monito[9].z].existe=1;

		 if(monito[10].x<MAX-2 && contenedor[monito[10].x+1][monito[10].y][monito[10].z].existe==0)  //ARRIBA
		 monito[10].x++;
		 contenedor[monito[10].x][monito[10].y][monito[10].z].existe=1;

		 if(monito[11].x<MAX-1 && contenedor[monito[11].x+1][monito[11].y][monito[11].z].existe==0)  //ARRIBA
		 monito[11].x++;
		 contenedor[monito[11].x][monito[11].y][monito[11].z].existe=1;

		 if(monito[12].x<MAX-1 && contenedor[monito[12].x+1][monito[12].y][monito[12].z].existe==0)  //ARRIBA
		 monito[12].x++;
		 contenedor[monito[12].x][monito[12].y][monito[12].z].existe=1;
		 break;

	case 75: if(monito[0].x>2 && contenedor[monito[0].x-1][monito[0].y][monito[0].z].existe==0)       //IZQUIERDA
		 monito[0].x--;
		 contenedor[monito[0].x][monito[0].y][monito[0].z].existe=1;

		 if(monito[1].x>2 && contenedor[monito[1].x-1][monito[1].y][monito[1].z].existe==0)       //IZQUIERDA
		 monito[1].x--;
		 contenedor[monito[1].x][monito[1].y][monito[1].z].existe=1;

		 if(monito[2].x>2 && contenedor[monito[2].x-1][monito[2].y][monito[2].z].existe==0)       //IZQUIERDA
		 monito[2].x--;
		 contenedor[monito[2].x][monito[2].y][monito[2].z].existe=1;

		 if(monito[3].x>1 && contenedor[monito[3].x-1][monito[3].y][monito[3].z].existe==0)  //ARRIBA
		 monito[3].x--;
		 contenedor[monito[3].x][monito[3].y][monito[3].z].existe=1;

		 if(monito[4].x>0 && contenedor[monito[4].x-1][monito[4].y][monito[4].z].existe==0)  //ARRIBA
		 monito[4].x--;
		 contenedor[monito[4].x][monito[4].y][monito[4].z].existe=1;

		 if(monito[5].x>3 && contenedor[monito[5].x-1][monito[5].y][monito[5].z].existe==0)  //ARRIBA
		 monito[5].x--;
		 contenedor[monito[5].x][monito[5].y][monito[5].z].existe=1;

		 if(monito[6].x>4 && contenedor[monito[6].x-1][monito[6].y][monito[6].z].existe==0)  //ARRIBA
		 monito[6].x--;
		 contenedor[monito[6].x][monito[6].y][monito[6].z].existe=1;

		 if(monito[7].x>1 && contenedor[monito[7].x-1][monito[7].y][monito[7].z].existe==0)  //ARRIBA
		 monito[7].x--;
		 contenedor[monito[7].x][monito[7].y][monito[7].z].existe=1;

		 if(monito[8].x>0 && contenedor[monito[8].x-1][monito[8].y][monito[8].z].existe==0)  //ARRIBA
		 monito[8].x--;
		 contenedor[monito[8].x][monito[8].y][monito[8].z].existe=1;

		 if(monito[9].x>0 && contenedor[monito[9].x-1][monito[9].y][monito[9].z].existe==0)  //ARRIBA
		 monito[9].x--;
		 contenedor[monito[9].x][monito[9].y][monito[9].z].existe=1;

		 if(monito[10].x>3 && contenedor[monito[10].x-1][monito[10].y][monito[10].z].existe==0)  //ARRIBA
		 monito[10].x--;
		 contenedor[monito[10].x][monito[10].y][monito[10].z].existe=1;

		 if(monito[11].x>4 && contenedor[monito[11].x-1][monito[11].y][monito[11].z].existe==0)  //ARRIBA
		 monito[11].x--;
		 contenedor[monito[11].x][monito[11].y][monito[11].z].existe=1;

		 if(monito[12].x>4 && contenedor[monito[12].x-1][monito[12].y][monito[12].z].existe==0)  //ARRIBA
		 monito[12].x--;
		 contenedor[monito[12].x][monito[12].y][monito[12].z].existe=1;
		 break;




	}
		} while(t!=13);
}
