#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funkcje.h"
#include "ogolne.h"


int main(int argc, char **argv){
  int N;
  printf("Proszę podać wielkość planszy:");
  scanf("%d", &N);
  gra *G = NULL;
  G = utworz(N);
  int wiersz, kolumna;
  
  /*
 {//POLE BOJOWE / STREFA 51
  listaruchow *l = NULL;
  l = ruchy_dostepne(G, N, ile);
  wypisz_ruchy(l); 
  
  
return 0;
 }*/
 listaruchow *lista = NULL;
 int ile;
  for (int i = 0; i< pow(N, 2); i++){
    ile = ile_ruchow(G, N);
    wypisz_plansze(G,N);
    lista = ruchy_dostepne(G, N, ile);
    wypisz_ruchy(lista, G, N);
    if(strcmp(G->ruch, "X") == 0){
      printf("Tura negamaxa\n");
      negamax(G, 2, -1, 1, N, ile);
      G->ruch = "O";
    }
    else if(strcmp(G->ruch, "O") == 0){
      A:
      printf("Ruch:\n");
      scanf("%d %d", &wiersz, &kolumna);
      switch(G->pole[wiersz][kolumna]){
      case ' ':
      G = wstaw(G, N, wiersz, kolumna);
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
    if(wynik(ocena(G, N)) == 1){
      break;
    }
    
  }
return 0;
}