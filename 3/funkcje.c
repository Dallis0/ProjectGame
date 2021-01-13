#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "ogolne.h"
#include <math.h>


gra *utworz(int N){
  gra *G; 
  G = (gra*) malloc(sizeof(gra));
  G->pole = (char **) malloc(sizeof(char*) * N);
  for(int i=0;i<N;i++)
    G->pole[i] = (char*) malloc(sizeof(char) * N);
  G->ruch = (char *) malloc(sizeof(char));

  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      G->pole[i][j] = ' ';
  G->ruch = "O";

  return G;
}

void wypisz_plansze(gra *G, int N){
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


Ruch *dane(gra *G, int wiersz, int kolumna){
	Ruch *glowa;
  glowa = (Ruch*) malloc(sizeof(Ruch));
  glowa->kto = (char*) malloc(sizeof(char));
  glowa->gdzie = (char*) malloc(sizeof(char) *3);

  glowa->kto = G->ruch;
  sprintf(glowa->gdzie, "%d %d", wiersz, kolumna);
  
  return glowa;
}


listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna){
  listaruchow *glowa;
  glowa = (listaruchow*) malloc(sizeof(listaruchow));
  glowa->ruchy = (Ruch*) malloc(sizeof(Ruch));
  glowa->ruchy = dane(G, wiersz, kolumna);

  return glowa;
}

void mozliwe_ruchy(gra *G, int N){
  printf("Teraz ruch: %s\nDostępne ruchy:\n", G->ruch);
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++){
      switch(G->pole[i][j]){
        case ' ':
          printf("%s   ", wstaw_na_puste(G, i, j)->ruchy->gdzie);
          break;
        case 'X':
          break;
        case 'O':
          break;
      }
    }
  }
  printf("\n");
}

gra *wstaw(gra *G, int N, int wiersz, int kolumna){
  gra *nowa; 
    nowa = (gra*) malloc(sizeof(gra));
    nowa->pole = (char **) malloc(sizeof(char*) * N);
    for(int i=0;i<N;i++)
      nowa->pole[i] = (char*) malloc(sizeof(char) * N);
    nowa->ruch = (char *) malloc(sizeof(char));
  nowa = G; 

  if(G->ruch == "O"){
    nowa->pole[wiersz][kolumna] = 'O';
    nowa->ruch = "X";
  }
  else if(G->ruch == "X"){
    nowa->pole[wiersz][kolumna] = 'X';
    nowa->ruch = "O";
  }

  return nowa;
}


int ocena(gra *G, int N){
  int a;
  for(int k=0; k<N; k++) //sprawdzamy pionowe ustawienie
  {
    a = 0;
    
    if(G->pole[0][k] != ' ')
      {
      for(int w=0;w<N-1;w++)
      {
    		if(G->pole[w+1][k] == G->pole[w][k])
          a++;
      }
    }
    if(a == N-1)
    {
      if(G->pole[0][k] == 'X')
        return 1;
      else if(G->pole[0][k] == 'O')
        return 2;
    }
  }
  
  for(int w=0; w<N; w++) //sprawdzamy poziome ustawienie
  {
    a = 0;
    
    if(G->pole[w][0] != ' ')
    {
      for(int k=0;k<N-1;k++)
      {
    		if(G->pole[w][k+1] == G->pole[w][k])
          a++;
      }
    }

    if(a == N-1)
    {
      if(G->pole[w][0] == 'X')
        return 1;
      if(G->pole[w][0] == 'O')
        return 2;
      else 
        printf("Nikt jeszcze nie wygrał\n");
    }
  }
  
  int w=0; //sprawdzamy ukos od lewego gornego rogu
  a = 0;
  if(G->pole[0][0] != ' ')
  {
  	for(int k=0;k<N-1;k++)
  	{ 
      if(G->pole[w+1][k+1] == G->pole[w][k])	
        a++;
    	w++;
    }
  if(a == N-1)
  {
    if(G->pole[0][0] == 'X')
        return 1;
      else if(G->pole[0][0] == 'O')
        return 2;
  }
  }

  w=0; //sprawdzamy ukos od lewego dolnego rogu
  a=0;
  if(G->pole[N-1][0] != ' ')
  {
  	for(int k=0;k<N-1;k++)
  	{ 
      if(G->pole[N-w-2][k+1] == G->pole[N-w-1][k])	
        a++;
    	w++;
    }
  if(a == N-1)
    {
      if(G->pole[N-1][0] == 'X')
        return 1;
      else if(G->pole[N-1][0] == 'O')
        return 2;
    }
  }
  return 0;
}

// void start(gra G){
//   printf("\nWitaj w ""Kołko i krzyżyk""!\n\n");
//   wypisz_plansze(utworz(&G));

//   printf("\nWybierz, kształt jakim chcesz grać wpisująć:\n./gra krzyzyk\nlub\n./gra kolko\n");
// }

int wynik(int a){
  if(a == 1){
    printf("Krzyżyk is the winner!\n");
    return 1;
  }
  else if(a == 2){
    printf("Kółko is the winner!\n");
    return 1;
  }
  else if(a == 0){
    printf("Graj dalej!\n");
    return 0;
  }
}
