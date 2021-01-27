#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "ogolne.h"
#include <math.h>


gra utworz(){
  gra G;

  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)  
      G.pole[i][j] = ' ';
      
  strcpy(G.ruch, "O");

  return G;
}

void wypisz_plansze(gra *G){
  for(int i=0;i<N;i++){
  printf("%4d",i);
  } 
  printf("\n");
  for(int i=0;i<N;i++){
    printf(" ");
    for(int i=0;i<N;i++){
      printf("+---");
    }  
    printf("+\n");
    printf("%d|", i);
    for(int j=0;j<N;j++){
      printf(" %1c |", G->pole[i][j]);   
    }
    printf("\n");
  }
  printf(" ");
  for(int i=0;i<N;i++){
   printf("+---");
  } 
  printf("+\n");
}

listaruchow *ruchy_dostepne(gra *G){
  int i,j;
  listaruchow *glowa = NULL;
  listaruchow *lista = NULL;
  listaruchow *r = NULL;

  for(i=0;i<N;i++)
    for(j=0;j<N;j++){
      if(G->pole[i][j] == ' '){
        lista = (listaruchow*) malloc(sizeof(listaruchow));
        lista->nast = NULL;

        if(glowa == NULL)
          glowa = lista;
        else{
          r = glowa;
          while(r->nast !=NULL)
            r = r->nast;
          r->nast = lista;
        }
        lista->x = j;
        lista->y = i;
      }
    }

  return glowa;
}

void wypisz_ruchy(listaruchow *lista, gra *G){
  listaruchow *r = lista;
  int i,ile;
  ile = ile_ruchow(G);
  for(i=0;i<ile; i++){
  printf("%d %d   ", r->y, r->x);
  r = r->nast;
  }
  printf("\n");
  printf("Teraz kolejność : %s\n", G->ruch);
}

int ile_ruchow(gra *G){
  int a = 0;
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++){
      switch(G->pole[i][j]){
        case ' ':
          a++;
          break;
        case 'X':
          break;
        case 'O':
          break;
      }
    }
  }
  return a;
}

gra wstaw(gra G, int wiersz, int kolumna){
  gra nowa; 
  nowa = G; 
  
  if(strcmp(G.ruch, "O") == 0){
    nowa.pole[wiersz][kolumna] = 'O';
    strcpy(nowa.ruch, "X");
  }
  else if(strcmp(G.ruch, "X") == 0){
    nowa.pole[wiersz][kolumna] = 'X';
    strcpy(nowa.ruch, "O");
  }

  return nowa;
}

int ocena(gra *G){
  int i, j, m, n, a, rodzaj;
  int ruch;
  if(strcmp(G->ruch, "O") == 0)
    ruch = 'O';
  else if(strcmp(G->ruch, "X") == 0)
    ruch = 'X';

  for(i = 0; i<N;i++){
    for(j = 0;j<N;j++){
        if(G->pole[i][j] == 'O' || G->pole[i][j] == 'X'){
        rodzaj = G->pole[i][j];
        a = 1;
        m = i;
        n = j;
        while(G->pole[m][n+1] == rodzaj){
          a++;
          n++;
          if(n == N - 1)
            break;
        }
        if(a == W){
          if(G->pole[i][j] == ruch){
            return 5;
          }
          else if(G->pole[i][j] != ruch)
            return -5;
        }
        a = 1;
        m = i;
        n = j;
        while(G->pole[m+1][n] == rodzaj){
          a++;
          m++;
          if(m == N - 1)
            break;
        }
        if(a == W){
          if(G->pole[i][j] == ruch){
            return 5;
          }
          else if(G->pole[i][j] != ruch)
            return -5;
        }
        a = 1;
        m = i;
        n = j;
        while(G->pole[m+1][n+1] == rodzaj){
          a++;
          m++;
          n++;
          if(m == N-1 || n == N-1)
            break;
        }
        if(a == W){
          if(G->pole[i][j] == ruch){
            return 5;
          }
          else if(G->pole[i][j] != ruch)
            return -5;
        }
        a = 1;
        m = i;
        n = j;
        if(n < N - 1)
          while(G->pole[m-1][n+1] == rodzaj){
            a++;
            m--;
            n++;
            if(m == 0 || n == N - 1)
              break;
          }
        if(a == W){
          if(G->pole[i][j] == ruch){
            return 5;
          }
          else if(G->pole[i][j] != ruch)
            return -5;
        }
      }
    }
  }
  return 0;
}

int negamax(gra *G, int glebokosc, int alfa, int beta){
  if(!glebokosc)
    return ocena(G);
  
  int nowaocena;
  int ocenawezla = -50;
  for(listaruchow *lr = ruchy_dostepne(G), *ptr = lr; lr; lr = lr->nast, free(ptr),ptr = lr){
    gra dziecko = wstaw(*G, lr->y, lr->x);
    nowaocena = -negamax(&dziecko, glebokosc -1, -beta, -alfa);

    if(nowaocena > ocenawezla)
      ocenawezla = nowaocena;
    if(ocenawezla > alfa)
      alfa = ocenawezla;
    if(alfa > beta)
      break;
  }

return ocenawezla;
}

listaruchow *najlepszy_ruch(gra *G, int glebokosc, int alfa, int beta){
  int ile = ile_ruchow(G);
  int nowaocena[ile]; 
  listaruchow naj_pole[ile];
  
  int i = -1;
  listaruchow *j = NULL;
  j = (listaruchow*) malloc(sizeof(listaruchow));
  int maxocena;
    for(listaruchow *lr = ruchy_dostepne(G); lr; lr = lr->nast)
    {
      i++;
      gra dziecko = wstaw(*G, lr->y, lr->x);
      nowaocena[i] = -negamax(&dziecko, glebokosc, alfa, beta);
      naj_pole[i].x = lr->x;
      naj_pole[i].y = lr->y;
    }
        i = 0;
        j->x = naj_pole[i].x;
        j->y = naj_pole[i].y;

        maxocena = -50;
        for(i;i<ile;i++)
        {
            if(maxocena<nowaocena[i])
            {
                j->x = naj_pole[i].x;
                j->y = naj_pole[i].y;
                maxocena=nowaocena[i];
            }
        }
        
    return j;
}

int wynik(int a){
    if(a == 1){
      printf("Krzyżyk wygrał!\n");
      return 1;
    }
    else if(a == -1){
      printf("Kółko wygrało!\n");
      return 1;
    }
  
  else if(a == 0){
    return 0;
  }
}
