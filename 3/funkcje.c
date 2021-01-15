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


<<<<<<< HEAD
Ruch dane(gra *G, int wiersz, int kolumna){
	Ruch glowa;
   printf("loldane1\n");
  //glowa = (Ruch*) malloc(sizeof(Ruch));
   printf("loldane2\n");
  glowa.kto = (char*) malloc(sizeof(char));
   printf("loldane3\n");
  glowa.gdzie = (char*) malloc(sizeof(char) *3);
   printf("loldane4\n");

  glowa.kto = G->ruch;
   printf("loldane5\n");
  sprintf(glowa.gdzie, "%d %d", wiersz, kolumna);
   printf("loldane6\n");
   
  return glowa;
}

listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna){
  listaruchow *glowa;
  glowa = (listaruchow*) malloc(sizeof(listaruchow));
  //glowa->ruchy = (Ruch*) malloc(sizeof(Ruch));
  glowa->ruchy = dane(G, wiersz, kolumna);
=======
listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna){
  listaruchow *glowa;
  glowa = (listaruchow*) malloc(sizeof(listaruchow));
  glowa->gdzie = (char*) malloc(sizeof(char));
  sprintf(glowa->gdzie, "%d %d", wiersz, kolumna);
>>>>>>> 52af5c4a728d53be6025a58c926ecafba2af2208

  return glowa;
}

listaruchow *ostatni_r(listaruchow *glowa)
{
    if(glowa != NULL){
        while(glowa->nast != NULL)
            glowa = glowa->nast;
        return glowa;
    }
    else 
        return NULL;
}

listaruchow *ruchy_dostepne(gra *G, int N, int ile){
<<<<<<< HEAD
   printf("lol1\n");
  listaruchow *glowa;
   printf("lol2\n");
  glowa = (listaruchow*) malloc(sizeof(listaruchow) * ile);
   printf("lol3\n");
  //glowa->ruchy = (Ruch*) malloc(sizeof(Ruch) * ile);
   printf("lol4\n");
  glowa = NULL;
   printf("lol5\n");
   printf("lol6\n");
  for(int i=0; i<N; i++)
    for(int j=0;j<N;j++){
      if(G->pole[i][j] == ' '){
        printf("lol7\n");
      glowa->ruchy = dane(G, i, j);
       printf("lol8\n");
      glowa = glowa->nast;
=======
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
        lista->gdzie = (char*) malloc(sizeof(char) *3);
        sprintf(lista->gdzie, "%d %d", i, j);
>>>>>>> 52af5c4a728d53be6025a58c926ecafba2af2208
      }
    }
  wypisz_ruchy(glowa, G, N);
  return glowa;
}

void wypisz_ruchy(listaruchow *lista, gra *G, int N){
  listaruchow *r = lista;
  int i,ile;
  ile = ile_ruchow(G, N);
  for(i=0;i<ile; i++){
  printf("%s   ", r->gdzie);
  r = r->nast;
  }
  printf("\n");
}

int ile_ruchow(gra *G, int N){
  int a = 0;
  printf("Teraz ruch: %s\nDostępne ruchy:\n", G->ruch);
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++){
      switch(G->pole[i][j]){
        case ' ':
<<<<<<< HEAD
          printf("%s   ", wstaw_na_puste(G, i, j)->ruchy.gdzie);
=======
>>>>>>> 52af5c4a728d53be6025a58c926ecafba2af2208
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

int negamax(gra *G, int glebokosc, int alfa, int beta, int N){
  if (!glebokosc)
  return ocena(G, N);

  int nowaocena;
  int ocenawezla = -1;
  

return 0;
}

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
