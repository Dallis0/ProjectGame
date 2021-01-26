#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funkcje.h"
#include "ogolne.h"


int main(int argc, char **argv){
  int wiersz, kolumna;
  gra G;
  listaruchow *lista = NULL;

  G = utworz();
  wypisz_plansze(&G);

  
  int ile, a;


  for (int i = 0; i< pow(N, 2); i++){
    printf("for nr %d\n", i);
    wypisz_plansze(&G);
    ile = ile_ruchow(&G);
    lista = ruchy_dostepne(&G);
    wypisz_ruchy(lista, &G);
    if(strcmp(G.ruch, "X") == 0){
      printf("MAMY TO!\n");
      listaruchow *naj = najlepszy_ruch(&G, 4, -100, 100);
      printf("Najlepszy ruch negamaxa x:%d y:%d\n", naj->x, naj->y);
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
    if(ocena(&G) == 5 || ocena(&G) == -5){
      break;
    }  
  }
return 0;
}