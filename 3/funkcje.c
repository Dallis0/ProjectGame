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


/*listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna){
  listaruchow *glowa;
  glowa = (listaruchow*) malloc(sizeof(listaruchow));
  glowa->gdzie = (char*) malloc(sizeof(char));
  sprintf(glowa->gdzie, "%d %d", wiersz, kolumna);

  return glowa;
}*/

/*listaruchow *ostatni_r(listaruchow *glowa)
{
    if(glowa != NULL){
        while(glowa->nast != NULL)
            glowa = glowa->nast;
        return glowa;
    }
    else 
        return NULL;
}*/

listaruchow *ruchy_dostepne(gra *G, int N, int ile){
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
        // lista->gdzie = (char*) malloc(sizeof(char) *3);
        // sprintf(lista->gdzie, "%d %d", i, j);
      }
    }
  return glowa;
}

void wypisz_ruchy(listaruchow *lista, gra *G, int N){
  listaruchow *r = lista;
  int i,ile;
  ile = ile_ruchow(G, N);
  for(i=0;i<ile; i++){
  printf("%d %d   ", r->y, r->x);
  r = r->nast;
  }
  printf("\n");
}

int ile_ruchow(gra *G, int N){
  int a = 0;
  //printf("Teraz ruch: %s\nDostępne ruchy:\n", G->ruch);
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

gra *wstaw(gra *G, int N, int wiersz, int kolumna){
  gra *nowa; 
    /*nowa = (gra*) malloc(sizeof(gra));
    nowa->pole = (char **) malloc(sizeof(char*) * N);
    for(int i=0;i<N;i++)
      nowa->pole[i] = (char*) malloc(sizeof(char) * N);
    nowa->ruch = (char *) malloc(sizeof(char));*/
  nowa = G; 
  
  if(G->ruch == "O"){
    nowa->pole[wiersz][kolumna] = 'O';
    nowa->ruch = "X";
  }
  else if(G->ruch == "X"){
    nowa->pole[wiersz][kolumna] = 'X';
    nowa->ruch = "O";
  }
  printf("Wstaw G\n");
  wypisz_plansze(G, N);
  printf("Wstaw nowa\n");
  wypisz_plansze(nowa, N);

  return nowa;
}

// gra *wstaw_negmax(gra *G, int N, int wiersz, int kolumna)
// {
//   gra *nowa;
//   nowa = G;
//   if(G->ruch == "O"){
//     nowa->pole[wiersz][kolumna] = 'O';    
//   }
//   else if(G->ruch == "X"){
//     nowa->pole[wiersz][kolumna] = 'X';    
//   }

//   return nowa;
// }

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
        return -1;
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
        return -1;
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
        return -1;
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
        return -1;
    }
  }
  return 0;
}

int negamax(gra *G, int glebokosc, int alfa, int beta, int N){
  if(glebokosc <1){
    printf("glebokosc = %d wykonuje sie if 240\n", glebokosc);
    printf("ocena z ifa = %d\n", ocena(G, N));
  return ocena(G, N);
  }
  int ile = ile_ruchow(G, N);
  printf("tyle jest ruchow dostepnych %d\n", ile);
  int nowaocena;
  int ocenawezla = -1;
  for(listaruchow *lr = ruchy_dostepne(G, N, ile), *ptr = lr; lr; lr = lr->nast, free(ptr),ptr = lr){
    wypisz_ruchy(lr, G, N);
    gra *dziecko = wstaw(G, N, lr->y, lr->x);
    printf("Plansza G\n");
    wypisz_plansze(G,N); 
    printf("Plansza dziecko\n");
    wypisz_plansze(dziecko,N);
    printf("glebokosc %d\n", glebokosc);
    nowaocena = -negamax(dziecko, glebokosc -1, alfa, beta, N);
    if(nowaocena > ocenawezla)
      ocenawezla = nowaocena;
    if(ocenawezla > alfa)
      alfa = ocenawezla;
    if(alfa > beta)
      break;
  }

return ocenawezla;
}

int wynik(int a){
  if(a == 1){
    printf("Krzyżyk is the winner!\n");
    return 1;
  }
  else if(a == -1){
    printf("Kółko is the winner!\n");
    return 1;
  }
  else if(a == 0){
    printf("Graj dalej!\n");
    return 0;
  }
}
