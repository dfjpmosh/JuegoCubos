#include <winbgim.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

//TAMAÑOS DE PORTADA Y MENU
#define ANCHO 10
#define PROF ANCHO/2

//TAMAÑOS DE CONTENEDOR
#define A 8
#define P A/2
#define N 29

//COLORES DE MONITO
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

//FUNCIONES DE JUEGO
void dibuja_cubo(int x, int y, int color);
cubo ***crea(int ncapas, int nrenglones, int ncolumnas);
void libera(cubo ***ptr,int ncapas, int nrenglones, int ncolumnas);
void inicializa(cubo ***a,int p,int r, int c);
void dibuja_contenedor(cubo ***a,int p,int r, int c);
void derecha(cubo ***a, int p, int r, int c);
void izquierda(cubo ***a, int p, int r, int c);
void arriba(cubo ***a, int p, int r, int c);
void abajo(cubo ***a, int p, int r, int c);
void disparo(cubo ***a, int p, int r, int c);
void juego(cubo ***a, int p, int r, int c, int *nivel, int *vida, jugador jug);
void datos_jugador(jugador jug, int nivel_aux, int vida_aux2);
void pide_nom(jugador *jug);
void retraso(int milisec);
void lee_texto(int x, int y, char var[]);
void SALIR();
void salir();
void ayuda();
void crear_record_bin(jugador jug);
void crear_record_txt(jugador *jug);
int tamArch(char nom[]);
void abrir_record();
void mueve_pared(cubo ***a, int p, int r, int c, int *vida_aux, int k);
void bala(cubo ***a, int p, int r, int c, jugador *jug);

//FUCNIONES DE PORTADA
void portada();
void linea_cubos();
void paraboloide();
void circulos();
void comentarios(void);

//FUNCIONES DEL MENU
void menu_mouse(cubo ***a, int p, int r, int c, jugador jug);
void menu();
void linea_cubos_mouse();
void paraboloide_mouse();
void circulos_mouse();

int main()
{
  cubo ***contenedor; // arreglo 3D 
  int ncap=N,nren=N,ncol=N;
  int tecla;
  jugador jug;
  
  contenedor=crea(ncap,nren,ncol);
  inicializa(contenedor,ncap,nren,ncol);
  initwindow(648,486);
  
  //portada();
  menu_mouse(contenedor,ncap,nren,ncol,jug);
  
  libera(contenedor,ncap,nren,ncol);
  closegraph();   
}

//FUNCION JUEGO
void juego(cubo ***a, int p, int r, int c, int *nivel, int *vida, jugador jug)
{
  int tecla, page=0, nivel_aux, vida_aux, vida_aux2, cont=0, k=0;
    
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
       bala(a,p,r,c, &jug);
       dibuja_contenedor(a,p,r,c);
       datos_jugador(jug, nivel_aux, vida_aux2);
       
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
          case 65 : disparo(a,p,r,c);
                    break; 
          case 97 : disparo(a,p,r,c);
                    break;
        }
      }    
            
      //Pared de Cubos
      else
      {
         cont++;
         if(cont==(10 / *nivel))
         { 
           mueve_pared(a, p, r, c, &vida_aux, k);
           cont=0;
           k++;
         }
         
         if(k==N-1 && nivel_aux!=11 && vida_aux2!=0)
         {
           if(vida_aux<vida_aux2)
           {
             vida_aux2--;
             inicializa(a,p,r,c);
             k=0;
           }
           else
           {
             nivel_aux++;                     
             inicializa(a,p,r,c);
             k=0;
           }
         }
      }
      
   }while(tecla!=13 && vida_aux2!=0 && nivel_aux!=11); 
      
   salir();
   delay(400);
   crear_record_bin(jug);
   crear_record_txt(&jug);
}

void mueve_pared(cubo ***a, int p, int r, int c, int *vida_aux, int k)
{
  int i,j;
  
    
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
                    *vida_aux--;
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
          
  
}

//INICIALIZA EL CONTENEDOR
void inicializa(cubo ***a,int p,int r, int c)
{
  int i,j,k;
  
  for(k=0;k<p;k++)
   for(i=0;i<r;i++)
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

//DIBUJA EL CONTENEDOR
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
 
//DIBUJA UN CUBO
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

//SIMULA EL DESPLAZAMIENTO HACIA LA DERECHA DEL MONITO
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

//SIMULA EL DESPLAZAMIENTO HACIA LA IZQUIERDA DEL MONITO
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

//SIMULA EL DESPLAZAMIENTO HACIA ARRIBA DEL MONITO
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

//SIMULA EL DESPLAZAMIENTO HACIA ABAJO DEL MONITO
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

//SIMULA EL RECORRIDO DEL DISPARO
void disparo(cubo ***a, int p, int r, int c)
{
     int i,j,k;
     
     
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
              if(a[p-2][i][j].color==11 && a[p-2][i][j].existe==1)
              {
                  a[p-3][i][j].existe=1;
                  a[p-3][i][j].color=0;
              }
            }
        }
}

void bala(cubo ***a, int p, int r, int c, jugador *jug)
{
     int i,j,k, b;
     
     for(k=0;k<p;k++)
        for(i=0;i<r;i++)
          for(j=0;j<c;j++)
            if(a[k][i][j].color==0 && a[k][i][j].existe==1)
            {
                                   
               if(a[0][i][j].color==0 && a[0][i][j].existe==1)
               {
                  a[k][i][j].existe=0;
               }
               else
               {
                   if(a[k-1][i][j].existe==1 && a[k-1][i][j].color==RED)
                   {
                      a[k][i][j].existe=0;
                      a[k-1][i][j].existe=0;
                      jug->puntos++;    //Aqui se acumulan los puntos
                   }
                   else
                   {
                     a[k-1][i][j].existe=1;
                     a[k-1][i][j].color=0;
                     a[k][i][j].existe=0;
                   }
               }
           }
}

//IMPRIME Y GUARDA LOS DATOS DEL JUGADOR DURANTE EL JUEGO
void datos_jugador(jugador jug, int nivel_aux, int vida_aux2)
{
     int i, punt;
     char punt_st[5];
     char nivel_st[5];
     char vidas_st[5];
    
     punt=jug.puntos;
	 itoa(punt,punt_st, 10);
	 itoa(nivel_aux,nivel_st, 10);
	 itoa(vida_aux2,vidas_st, 10);
	 
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
     outtextxy(32,205,vidas_st);
     outtextxy(32,240,"NIVEL");
     outtextxy(32,265,nivel_st);
     setcolor(RED);
     for(i=0; i<10; i+=2)
     rectangle(i, i, 639-i, 475-i);   
}

//CAPTURA NOMBRE DEL JUGADOR
void pide_nom(jugador *jug)
{
	int x=50,y=200;
	
	cleardevice();
    linea_cubos_mouse();
    paraboloide_mouse();
    circulos_mouse();
    setfillstyle(11, 1);
    setcolor(14);
    bar(30, 195, 600, 220);	
    settextstyle(0,0,2);
    outtextxy(x,y,"NOMBRE DEL JUGADOR: ");
    rectangle(30, 195, 600, 220);	
    lee_texto(x+textwidth("NOMBRE DEL JUGADOR: "), y, jug->nom);
}

//CAPTURA TEXTO EN GRAFICO
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

//SIMULA UN RETRASO EN LA CAPTURA DE TEXTO
void retraso(int milisec)
{
     clock_t i,j;
     i=clock();
     do
     {
     j=clock();
     }while((j-i)< milisec); 
}

//DIBUJA LA PORTADA
void portada()
{
	linea_cubos();
	circulos();
	paraboloide();
	comentarios();
	getch();
}

//DIBUJA LINEAS DE CUBOS EN LOS EXTREMOS
void linea_cubos()
{
    int i, ncy=36, nc=52;
    int x1=63, x2=6, x3=620;
	int y1=10, y2=462, y3=64;
	
    // CUBOS HORIZONTALES
    for(i=0;i<nc;i+=2)
    {
      dibuja_cubo(x1+i*ANCHO, y1, RED);
      dibuja_cubo(x1+i*ANCHO, y2, RED);
      delay(100);
    }
    
    //CUBOS VERTICALES
    for(i=0;i<ncy;i+=2)
    {
      dibuja_cubo(x2, y3+i*ANCHO, RED);
      dibuja_cubo(x3, y3+i*ANCHO, RED);
      delay(100);
    }
}

// DIBUJA LINEAS LA PARABOLOIDE HIPERBOLICA
void paraboloide()
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
                delay(250);
                j+=7;        
                i+=7;
   }
}

//DIBUJA COMENTARIOS DE LA PORTADA
void comentarios(void)
{
   rectangle(0, 0, 639, 479);
   
   delay(1000);

   setcolor(1);
   settextstyle(9, 0, 5);
   outtextxy(173, 50, "ROBOCUB");
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
   setcolor(14);
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

//SIMULA EL MOVIMIENTO DE LOS BOTONES
void menu_mouse(cubo ***a, int p, int r, int c, jugador jug)
{
  int vida=2, nivel=1;
  jug.puntos=0;
  
  cleardevice();
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
           pide_nom(&jug);
           juego(a, p, r, c, &nivel, &vida, jug);
           clearmouseclick(WM_LBUTTONDBLCLK);   /* limpia la bandera que indica si se presionó un botón */
           menu_mouse(a, p, r, c, jug);
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
           ayuda();
           clearmouseclick(WM_LBUTTONDBLCLK);   /* limpia la bandera que indica si se presionó un botón */
           menu_mouse(a, p, r, c, jug);
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
           abrir_record();
           clearmouseclick(WM_LBUTTONDBLCLK);   /* limpia la bandera que indica si se presionó un botón */
           menu_mouse(a, p, r, c, jug);
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
           clearmouseclick(WM_LBUTTONDBLCLK);   /* limpia la bandera que indica si se presionó un botón */
           SALIR();
           clearmouseclick(WM_LBUTTONDBLCLK);   /* limpia la bandera que indica si se presionó un botón */
       }
    }  
  }while (!ismouseclick(WM_RBUTTONDBLCLK) && !kbhit());  /* checa si se presionó boton derecho dos veces o una tecla */
}

//FIN DEL JUEGO
void salir()
{
     cleardevice();
     linea_cubos_mouse();
     paraboloide_mouse();
     circulos_mouse();
     setcolor(14);
     outtextxy(130, 200, "F I N  D E L  J U E G O");
}

//SALIR DEL PROGRAMA
void SALIR()
{
     cleardevice();
     linea_cubos_mouse();
     paraboloide_mouse();
     circulos_mouse();
     comentarios();
}

//DIBUJA EL MENU
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

void ayuda()
{
    FILE *f;
    char n[255];
    int y=70;
    
    cleardevice();
    linea_cubos_mouse();
	circulos_mouse();
	paraboloide_mouse();
    settextstyle(11,0,1);
    rectangle(50,50,getmaxx()-50,getmaxy()-50);
    rectangle(52,52,getmaxx()-52,getmaxy()-52);
    setcolor(14);
    outtextxy(getmaxx()/2-20,55,"AYUDA");
    f=fopen("ayuda.txt", "r");
    
    if(f==NULL)
    {
               outtext("No se encontro el archivo");
    }
    while(!feof(f))
    {
               fgets(n, 255,f);
               n[strlen(n)-1]='\0';
               outtextxy(60,y,n);
               y+=20;
    }    
    
    fclose(f);
    getch();
}

void abrir_record()
{
    FILE *f;
    char n[255], rec_st[3];
    int y=70, rec, i;
    
    
    cleardevice();
    linea_cubos_mouse();
	circulos_mouse();
	paraboloide_mouse();
    settextstyle(1,0,1);
    rectangle(50,50,getmaxx()-50,getmaxy()-50);
    rectangle(52,52,getmaxx()-52,getmaxy()-52);
    setcolor(14);
    outtextxy(getmaxx()/2-20,55,"RECORDS");
    
    f=fopen("Records.txt","r");
    while(!feof(f))
    {
               fgets(n, 255,f);
               //n[strlen(n)-1]='\0';
               outtextxy(60,y,n);
               y+=20;
    }    
    fclose(f);
    
    /*for(i=1; i<11; i++)
    {
       rec=i;
	   itoa(rec,rec_st, 10);
       outtextxy(56,110+(i*20),rec_st);
    }*/
    getch();
}

void crear_record_bin(jugador jug)
{
    FILE *f;
    f=fopen("Records.bin","ab");
    fwrite(&jug, sizeof(jugador), 1, f);
    fclose(f);
}

void crear_record_txt(jugador *jug)
{
    FILE *fb, *f;
    int n, i;
    
    fb=fopen("Records.bin","rb");
    f=fopen("Records.txt","w");
    
    n= tamArch("Records.bin");
    jug=(jugador*)malloc(sizeof(jugador)*n);
    fread(jug, sizeof(jugador), n, fb);
    fclose(fb);
}

int tamArch(char nom[])
{
   FILE *stream;
   long curpos, length;
   int tam; 
   
   stream = fopen(nom, "rb+");
   curpos = ftell(stream);  /* regresa la posición actual del apuntador */
   fseek(stream, 0L, SEEK_END); /* coloca el apuntador al final */
   length = ftell(stream);  /* regresala la posición actual de apuntador */
   fseek(stream, curpos, SEEK_SET); /*coloca apuntador en "curpos" */
   tam=length / sizeof(jugador);
   fclose(stream);
   return tam;
}

//CREA MEMORIA 
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

//LIBERA MEMORIA
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


