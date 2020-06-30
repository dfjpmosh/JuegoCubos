#include <winbgim.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#define A 8
#define P A/2
#define N 29

#define TAMMON 13
#define BLUE 1
#define RED 4
#define GREEN 3
#define WHITE 15

typedef struct
{
        int x;
        int y;
        int color;
        int existe;
}cubo;

typedef struct
{
        char nom[50];
        int puntos;
}jugador;

void dibuja_cubo(int x, int y, int color);
cubo ***crea(int ncapas, int nrenglones, int ncolumnas);
void libera(cubo ***ptr,int ncapas, int nrenglones, int ncolumnas);
void inicializa(cubo ***a,int p,int r, int c);
void dibuja_contenedor(cubo ***a,int p,int r, int c);
void derecha(cubo ***a, int p, int r, int c);
void izquierda(cubo ***a, int p, int r, int c);
void arriba(cubo ***a, int p, int r, int c);
void abajo(cubo ***a, int p, int r, int c);
void disparo(cubo ***a, int p, int r, int c, jugador *jug);
void juego(cubo ***a, int p, int r, int c, int *nivel, int *vida, jugador jug);
void datos_jugador(jugador jug);
void pide_nom(jugador *jug);
void retraso(int milisec);
void lee_texto(int x, int y, char var[]);

int main()
{
  int vida=3, nivel=1;
  cubo ***contenedor; // arreglo 3D 
  int ncap=N,nren=N,ncol=N;
  jugador jug;
  jug.puntos=0;
  
  contenedor=crea(ncap,nren,ncol);
  
  inicializa(contenedor,ncap,nren,ncol);
  initwindow(648,486);
  pide_nom(&jug);
  juego(contenedor,ncap,nren,ncol, &nivel, &vida, jug);
  
  libera(contenedor,ncap,nren,ncol);
  closegraph();   
}

void juego(cubo ***a, int p, int r, int c, int *nivel, int *vida, jugador jug)
{
  int tecla, page=0, choque=0, nivel_aux, vida_aux, vida_aux2;
  int i,j,k=0, cont=0;
  
  
  nivel_aux=*nivel;
  vida_aux=*vida;
  vida_aux2=vida_aux;
   do
   {
       
       if(page==1)
            page=0;
       else
            page=1;
       setactivepage(page);
       
       cleardevice();
       dibuja_contenedor(a,p,r,c);
       datos_jugador(jug);
       
       setvisualpage(page);
     
      if(kbhit())
      {
        tecla=getch();
	    if(tecla==0)
	    tecla=getch();
	   
	    switch(tecla)
	    {
	      case 77 : derecha(a,p,r,c);
                    break; 
          case 75 : izquierda(a,p,r,c);
                    break; 
          case 72 : arriba(a,p,r,c);
                    break; 
          case 80 : abajo(a,p,r,c);
                    break;
          case 65 : disparo(a,p,r,c, &jug);
                    break; 
          case 97 : disparo(a,p,r,c, &jug);
                    break;
        }
      }    
      
      
      //Pared de Cubos
      else
      {
          cont++;
          if(cont==(10 / *nivel))
          {
            if(k<N-1)
            {
              for(i=0;i<r;i++)
              {
                  for(j=0;j<c;j++)
                  {   
                      if(k==N-2)
                      {
                        for(i=0;i<r;i++)
                          for(j=0;j<c;j++)
                          {
                            if(a[p-1][i][j].existe==1 && a[k][i][j].existe==1)
                            {
                              a[p-1][i][j].color = a[k][i][j].color;
                              a[p-1][i][j].existe = a[k][i][j].existe;
                              a[k][i][j].existe = 0;
                              vida_aux--;
                            }
                           }
                      }
                      else
                      {
                        a[k+1][i][j].color = a[k][i][j].color;
                        a[k+1][i][j].existe = a[k][i][j].existe;
                        a[k][i][j].existe = 0;
                      }
                  }
              }
              k++;
            }cont=0;
          }
          if(k==N-1 && nivel_aux!=10 && vida_aux2!=0)
          {
             if(vida_aux!=vida_aux2)
             {
                inicializa(a,p,r,c);
                vida_aux2--;
                k=0;
                //juego(a,p,r,c, &nivel_aux, &vida_aux2, jug);
             }
             else
             {
                nivel_aux++;
                inicializa(a,p,r,c);
                k=0;
                //juego(a,p,r,c, &nivel_aux, &vida_aux, jug);
             }
          }
      }
      
   }while(tecla!=13 && vida_aux2!=0 && nivel_aux!=10); 
}

void inicializa(cubo ***a,int p,int r, int c)
{
  int i,j,k;
  
  for(k=0;k<p;k++)
   for
   (i=0;i<r;i++)
   {
     for(j=0;j<c;j++)
      {   
        a[k][i][j].x=300+A*j-k*P;
        a[k][i][j].y=300-A*i+k*P;
        a[k][i][j].color=1;
        a[k][i][j].existe = 0;
      }
   }  
   
  //Pared de Cubos
  //for(k=0;k<p;k++)
   for(i=0;i<r;i++)
   {
     for(j=0;j<c;j++)
      {   
        a[0][i][j].color=RED;
        a[0][i][j].existe = 1;
      }
   }   
  
  //El Monito se pinta de arriba hacia abajo y de izquierda a derecha
  a[p-1][6][c/2-2].existe=1;
  a[p-1][6][c/2-2].color=11;
  
  a[p-1][7][c/2-2].existe=1;
  a[p-1][7][c/2-2].color=BLUE;
  
  a[p-1][0][c/2-1].existe=1;
  a[p-1][0][c/2-1].color=GREEN;
  
  for(i=1; i<5; i++)
  {
    a[p-1][i][c/2-1].existe=1;
    a[p-1][i][c/2-1].color=6;
  }
  
  for(i=5; i<8; i++)
  {
    a[p-1][i][c/2-1].existe=1;
    a[p-1][i][c/2-1].color=BLUE;
  }
  
  for(i=9; i<12; i++)
  {
    a[p-1][i][c/2-1].existe=1;
    a[p-1][i][c/2-1].color=14;
  }
  
  for(i=3; i<5; i++)
  {
    a[p-1][i][c/2].existe=1;
    a[p-1][i][c/2].color=6;
  }
  
  for(i=5; i<8; i++)
  {
    a[p-1][i][c/2].existe=1;
    a[p-1][i][c/2].color=BLUE;
  }
  
    a[p-1][8][c/2].existe=1;
    a[p-1][8][c/2].color=11;
  
  for(i=9; i<12; i++)
  {
    a[p-1][i][c/2].existe=1;
    a[p-1][i][c/2].color=14;
  }
  
  a[p-1][0][c/2+1].existe=1;
  a[p-1][0][c/2+1].color=GREEN;
  
  for(i=1; i<5; i++)
  {
    a[p-1][i][c/2+1].existe=1;
    a[p-1][i][c/2+1].color=6;
  }
  
  for(i=5; i<8; i++)
  {
    a[p-1][i][c/2+1].existe=1;
    a[p-1][i][c/2+1].color=BLUE;
  }
  
  for(i=9; i<12; i++)
  {
    a[p-1][i][c/2+1].existe=1;
    a[p-1][i][c/2+1].color=14;
  }
  
  a[p-1][6][c/2+2].existe=1;
  a[p-1][6][c/2+2].color=11;
  
  a[p-1][7][c/2+2].existe=1;
  a[p-1][7][c/2+2].color=BLUE;
  
  a[p-2][0][c/2-1].existe=1;
  a[p-2][0][c/2-1].color=GREEN;
  
  a[p-2][0][c/2+1].existe=1;
  a[p-2][0][c/2+1].color=GREEN;
  
  a[p-2][6][c/2+2].existe=1;
  a[p-2][6][c/2+2].color=11;
  
}

void dibuja_contenedor(cubo ***a,int p,int r, int c)
{
 int i,j,k;
 
 setcolor(9);
 rectangle(300+P, 300+P, 300+A*N+P, 300-A*N+P); //Rectangulo de Atras
 line(300+P, 300+P, 300-P*N+P, 300+P*N+P);  //Linea Izquierda-Abajo
 line(300+P, 300-A*N+P, 300-P*N+P, 300-P*N+P);  //Linea Izquierda-Arriba
 line(300+A*N+P, 300+P, 300+P*N+P, 300+P*N+P);  //Linea Derecha-Abajo

 for(k=0;k<p;k++)
   for(i=0;i<r;i++)  /* primero dibuja cubos de abajo */
     for(j=0;j<c;j++)    /* en c/renglon se dibujan de izq a der */
        if(a[k][i][j].existe == 1)
        {
          dibuja_cubo(a[k][i][j].x,a[k][i][j].y,a[k][i][j].color); 
        }
 setcolor(9);
 rectangle(300-P*N+P, 300+P*N+P, 300+P*N+P, 300-P*N+P); //Rectangulo de Adelante
 line(300+P*N+P, 300-P*N+P, 300+A*N+P, 300-A*N+P);  //Linea Derecha-Arriba
 setcolor(10);
 rectangle(300-P*(N-10)+P, 300+P*(N-12)+P, 300+P*(N-10)+P, 300-P*19+P);  //Rectangulo de Referencia
}
 

void dibuja_cubo(int x, int y, int color)
{
     int poly[8];
	 
     setcolor(9);
	 poly[0]=x;             // x1
	 poly[1]=y;             // y1
	 poly[2]=x+A/2;         // x2
	 poly[3]=y-P;           // y2
	 poly[4]=x+A+A/2;       // x3
	 poly[5]=y-P;           // y3
	 poly[6]=x+A;           // x4
	 poly[7]=y;             // y4
	setfillstyle(1,color);
	fillpoly(4,poly);
	bar(x,y,x+A,y+A);
	rectangle(x,y,x+A,y+A);
     poly[0]=x+A;             // x1
	 poly[1]=y;               // y1
	 poly[2]=x+A;             // x2
	 poly[3]=y+A;             // y2
	 poly[4]=x+A*3/2;         // x3
	 poly[5]=y+A-P;           // y3
	 poly[6]=x+A*3/2;         // x4
	 poly[7]=y-P;             // y4
	setfillstyle(1,color);
	fillpoly(4,poly);
	
	
}

void derecha(cubo ***a, int p, int r, int c)
{
     int i,j,k;
     
     if(a[p-1][6][c-1].existe==0 && a[p-1][7][c-1].existe==0 && a[p-1][8][c-1].existe==0 && a[p-1][9][c-1].existe==0 && a[p-1][10][c-1].existe==0)
     if(a[p-1][11][c-1].existe==0 && a[p-1][12][c-1].existe==0 && a[p-1][13][c-1].existe==0 && a[p-1][14][c-1].existe==0 && a[p-1][15][c-1].existe==0)   
     if(a[p-1][16][c-1].existe==0 && a[p-1][17][c-1].existe==0 && a[p-1][18][c-1].existe==0 && a[p-1][19][c-1].existe==0 && a[p-1][20][c-1].existe==0)   
     if(a[p-1][21][c-1].existe==0 && a[p-1][22][c-1].existe==0 && a[p-1][23][c-1].existe==0 && a[p-1][24][c-1].existe==0 && a[p-1][25][c-1].existe==0)   
     {
     for(k=p-2;k<p;k++)
        for(i=0;i<r;i++)
        {
          for(j=c-2;j>=0;j--)
            {
              if(a[k][i][j].existe==1 && a[k][i][j+1].existe==0)
              {
                a[k][i][j].existe=0;
                a[k][i][j+1].existe=1;
                a[k][i][j+1].color=a[k][i][j].color;
              }
            }
        }
     }
}

void izquierda(cubo ***a, int p, int r, int c)
{
     int i,j,k;
     
     if(a[p-1][6][0].existe==0 && a[p-1][7][0].existe==0 && a[p-1][8][0].existe==0 && a[p-1][9][0].existe==0 && a[p-1][10][0].existe==0)
     if(a[p-1][11][0].existe==0 && a[p-1][12][0].existe==0 && a[p-1][13][0].existe==0 && a[p-1][14][0].existe==0 && a[p-1][15][0].existe==0)   
     if(a[p-1][16][0].existe==0 && a[p-1][17][0].existe==0 && a[p-1][18][0].existe==0 && a[p-1][19][0].existe==0 && a[p-1][20][0].existe==0)   
     if(a[p-1][21][0].existe==0 && a[p-1][22][0].existe==0 && a[p-1][23][0].existe==0 && a[p-1][24][0].existe==0 && a[p-1][25][0].existe==0)   
     {
     for(k=p-2;k<p;k++)
        for(i=0;i<r;i++)
        {
          for(j=0;j<=c;j++)
            {
              if(a[k][i][j].existe==1 && a[k][i][j-1].existe==0 )
              {
                a[k][i][j].existe=0;
                a[k][i][j-1].existe=1;
                a[k][i][j-1].color=a[k][i][j].color;
              }
            }
        }
     }
}

void arriba(cubo ***a, int p, int r, int c)
{
     int i,j,k;
     
     if(a[p-1][r-1][2].existe==0 && a[p-1][r-1][3].existe==0 && a[p-1][r-1][4].existe==0 && a[p-1][r-1][5].existe==0 && a[p-1][r-1][6].existe==0)
     if(a[p-1][r-1][7].existe==0 && a[p-1][r-1][8].existe==0 && a[p-1][r-1][9].existe==0 && a[p-1][r-1][10].existe==0 && a[p-1][r-1][11].existe==0)
     if(a[p-1][r-1][12].existe==0 && a[p-1][r-1][13].existe==0 && a[p-1][r-1][14].existe==0 && a[p-1][r-1][15].existe==0 && a[p-1][r-1][16].existe==0)
     if(a[p-1][r-1][17].existe==0 && a[p-1][r-1][18].existe==0 && a[p-1][r-1][19].existe==0 && a[p-1][r-1][20].existe==0 && a[p-1][r-1][21].existe==0)
     if(a[p-1][r-1][22].existe==0 && a[p-1][r-1][23].existe==0 && a[p-1][r-1][24].existe==0 && a[p-1][r-1][25].existe==0 && a[p-1][r-1][26].existe==0)
     {
     for(k=p-2;k<p;k++)
        for(i=r-2;i>=0;i--)
        {
            for(j=0;j<c;j++)
            {
              if(a[k][i][j].existe==1 && a[k][i+1][j].existe==0)
                {
                  a[k][i+1][j].existe=1;
                  a[k][i][j].existe=0;
                  a[k][i+1][j].color=a[k][i][j].color;
                }
            }
        }
     }
}

void abajo(cubo ***a, int p, int r, int c)
{
     int i,j,k;
     
     if(a[p-1][0][2].existe==0 && a[p-1][0][3].existe==0 && a[p-1][0][4].existe==0 && a[p-1][0][5].existe==0 && a[p-1][0][6].existe==0)
     if(a[p-1][0][7].existe==0 && a[p-1][0][8].existe==0 && a[p-1][0][9].existe==0 && a[p-1][0][10].existe==0 && a[p-1][0][11].existe==0)
     if(a[p-1][0][12].existe==0 && a[p-1][0][13].existe==0 && a[p-1][0][14].existe==0 && a[p-1][0][15].existe==0 && a[p-1][0][16].existe==0)
     if(a[p-1][0][17].existe==0 && a[p-1][0][18].existe==0 && a[p-1][0][19].existe==0 && a[p-1][0][20].existe==0 && a[p-1][0][21].existe==0)
     if(a[p-1][0][22].existe==0 && a[p-1][0][23].existe==0 && a[p-1][0][24].existe==0 && a[p-1][0][25].existe==0 && a[p-1][0][26].existe==0)
     {
     for(k=p-2;k<p;k++)
        for(i=1;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
              if(a[k][i][j].existe==1 && a[k][i-1][j].existe==0)
                {
                  a[k][i-1][j].existe=1;
                  a[k][i][j].existe=0;
                  a[k][i-1][j].color=a[k][i][j].color;
                }
            }
        }
     }
}

void disparo(cubo ***a, int p, int r, int c, jugador *jug)
{
     int i,j,k, cont;
     
     
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
              if(a[p-2][i][j].color==11 && a[p-2][i][j].existe==1)
              {
                  for(k=p-2;k>=2;k--)
                  {
                    if(a[k-2][i][j].existe==1)
                    {
                       a[k-2][i][j].existe=0;
                       k=1;
                       jug->puntos+=10;
                    }
                    else
                    {
                       a[k-1][i][j].existe=1;
                       a[k-1][i][j].color=0;
                       dibuja_contenedor(a, p, r, c);
                       datos_jugador(*jug);
                       delay(20);
                       a[k-1][i][j].existe=0;
                       cleardevice();
                       dibuja_contenedor(a, p, r, c);
                       datos_jugador(*jug);
                    }
                  }
              }
            }
        }
}

void datos_jugador(jugador jug)
{
     int i, punt;
     char punt_st[5];
    
     punt=jug.puntos;
	 itoa(punt,punt_st, 10);
     
     setfillstyle(11, 1);
     bar(21, 30, 155, 420);   
     setcolor(14);
     rectangle(21, 30, 155, 420);   
     settextstyle(0,0,2);
     outtextxy(32,60,"JUGADOR");
     outtextxy(32,85,jug.nom);
     outtextxy(32,120,"PUNTOS");
     outtextxy(32,145, punt_st);
     outtextxy(32,180,"VIDAS");
     outtextxy(32,205,"v");
     outtextxy(32,240,"NIVEL");
     outtextxy(32,265,"n");
     setcolor(RED);
     for(i=0; i<10; i+=2)
     rectangle(i, i, 639-i, 475-i);   
}

void pide_nom(jugador *jug)
{
	int x=50,y=200;
	
        
    cleardevice();
		/*setcolor(4);
		settextstyle(1,0,1);
		outtextxy(23,10,"Da tu Nombre: ");
		lee_texto(23+textwidth("Da tu Nombre: "),10,jug->nom);
	*/
    setfillstyle(11, 1);
    setcolor(14);
    bar(30, 195, 600, 220);	
    settextstyle(0,0,2);
    outtextxy(x,y,"NOMBRE DEL JUGADOR: ");
    rectangle(30, 195, 600, 220);	
    lee_texto(x+textwidth("NOMBRE DEL JUGADOR: "), y, jug->nom);
    
}

void lee_texto(int x, int y, char var[])
{
    char tecla;
    int contador=0, i;
              
    var[0]='\0';

    do{
         do{
              //parpàdeo
              setcolor(15);
              outtextxy(x+textwidth(var),y,"_");
              retraso(200);
              setcolor(0);
              outtextxy(x+textwidth(var),y,"_");
              retraso(200);
              setcolor(15);
           }while(!kbhit());
     
              tecla=getch();
            if(tecla==0)//si es codigo extendido
               tecla=getch();
            if(tecla==8 && contador > 0)//se presiona <backspace> borrar
               {
               setcolor(0);
               outtextxy(x,y,var);
               var[--contador]='\0';
               setcolor(15);
               outtextxy(x,y,var);         
               }
            else
            {
            if(tecla!=13)    
            {
               var[contador++]=tecla;
               var[contador]='\0';
               outtextxy(x,y,var);                 
            }
            }
    }while(tecla!=13);// enter
    
    
}
//////......................../////////77
void retraso(int milisec)
{
     clock_t i,j;
     i=clock();
     do
     {
     j=clock();
     }while((j-i)< milisec); 
}

cubo ***crea(int ncapas, int nrenglones, int ncolumnas)
{
cubo ***ptr;
int capas,renglon;

  ptr = (cubo***) malloc(ncapas * sizeof(cubo **));
  for (capas = 0; capas < ncapas; capas++)
  {
    ptr[capas] = (cubo**) malloc(nrenglones * sizeof(cubo *));
    for (renglon = 0; renglon < nrenglones; renglon++)
      ptr[capas][renglon] = (cubo*) malloc(ncolumnas * sizeof(cubo));  
  }  
  return ptr;  
}

void libera(cubo ***ptr,int ncapas, int nrenglones, int ncolumnas)
{
int capas,renglon;
  for (capas = 0; capas < ncapas; capas++)
  {   
    for (renglon = 0; renglon < nrenglones; renglon++)
    {
      free(ptr[capas][renglon]);  /* libera columnas */
    }
    free(ptr[capas]);             /* libera renglones */
  }
  free(ptr);                      /* libera capas */
} 


