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
  wypisz_plansze(G, N);
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
    lista = ruchy_dostepne(G, N, ile);
    A:
    printf("Ruch:\n");
    scanf("%d %d", &wiersz, &kolumna);
    switch(G->pole[wiersz][kolumna]){
    case ' ':
    wypisz_plansze(wstaw(G, N, wiersz, kolumna), N);
    break;
    case 'X':
    printf("Nie da się wykonać ruchu!\n");
      goto A;
    case 'O':
    printf("Nie da się wykonać ruchu!\n");
      goto A;
    }
    printf("\n\n");
    if(wynik(ocena(G, N)) == 1){
      break;
    }
  }
return 0;
}