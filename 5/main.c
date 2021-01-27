#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funkcje.h"
#include "ogolne.h"


int main(int argc, char **argv){
  int wiersz, kolumna, oce;
  gra G;
  listaruchow *lista = NULL;

  G = utworz();
  wypisz_plansze(&G);

  
  int ile, a;


  for (int i = 0; i< pow(N, 2); i++){
    a = 5;
    ile = ile_ruchow(&G);
    if(a>ile)
      a--;
    lista = ruchy_dostepne(&G);
    wypisz_ruchy(lista, &G);
    if(strcmp(G.ruch, "O") == 0){
      listaruchow *naj = najlepszy_ruch(&G, a, -100, 100);
      G = wstaw(G, naj->y, naj->x);
      wypisz_plansze(&G);
    }

    else{
      A:
      printf("Ruch:\n");
      scanf("%d %d", &wiersz, &kolumna);
      switch(G.pole[wiersz][kolumna]){
      case ' ':
      G = wstaw(G, wiersz, kolumna);
      wypisz_plansze(&G);
        break;
      case 'X':
      printf("Nie da się wykonać ruchu!\n");
        goto A;
      case 'O':
      printf("Nie da się wykonać ruchu!\n");
        goto A;
      }
    }
    printf("\n\n");

    oce = ocena(&G);
    if(oce == 5 || oce == -5){
      if(strcmp(G.ruch, "X")==0)
      {
        printf("Kółko wygrało!\n");
      }     
      if(strcmp(G.ruch, "O")==0)
      {
        printf("Krzyżyk wygrał!\n");
      }
      break;
    }  
  }
  if(oce ==0)
  {
    printf("Remis!\n");
  }
return 0;
}