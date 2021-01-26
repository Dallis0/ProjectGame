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
        // lista->gdzie = (char*) malloc(sizeof(char) *3);
        // sprintf(lista->gdzie, "%d %d", i, j);
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

gra wstaw(gra G, int wiersz, int kolumna){
  gra nowa; 
    /*nowa = (gra*) malloc(sizeof(gra));
    nowa->pole = (char **) malloc(sizeof(char*) * N);
    for(int i=0;i<N;i++)
      nowa->pole[i] = (char*) malloc(sizeof(char) * N);
    nowa->ruch = (char *) malloc(sizeof(char));*/
  nowa = G; 
  
  if(strcmp(G.ruch, "O") == 0){
    nowa.pole[wiersz][kolumna] = 'O';
    strcpy(nowa.ruch, "X");
  }
  else if(strcmp(G.ruch, "X") == 0){
    nowa.pole[wiersz][kolumna] = 'X';
    strcpy(nowa.ruch, "O");
  }
  //wypisz_plansze(&nowa);

  return nowa;
}

int ocena(gra *G){
  int a;
  int ruch;
  if(strcmp(G->ruch, "O") == 0)
    ruch = 'O';
  else if(strcmp(G->ruch, "X") == 0)
    ruch = 'X';
  
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
      if(G->pole[0][k] == ruch){
        printf("%c is the winner\n", ruch);
        return 5;
      }
      else if(G->pole[0][k] != ruch)
        return -5;
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
      if(G->pole[w][0] == ruch){
        printf("%c is the winner\n", ruch);
        return 5;
      }
      if(G->pole[w][0] != ruch)
        return -5;
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
    if(G->pole[0][0] == ruch){
      printf("%c is the winner\n", ruch);
      return 5;
    }
      else if(G->pole[0][0] != ruch)
        return -5;
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
      if(G->pole[N-1][0] == ruch){
        printf("%c is the winner\n", ruch);
        return 5;
      }
      else if(G->pole[N-1][0] != ruch)
        return -5;
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
    //wypisz_ruchy(lr, G);
    gra dziecko = wstaw(*G, lr->y, lr->x);
    //printf("negamax %d\n", glebokosc);
    nowaocena = -negamax(&dziecko, glebokosc -1, -beta, -alfa);
    printf("nowa ocena w negamaxie %d\n", nowaocena);
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
  listaruchow *j = NULL; //RUCH
  j = (listaruchow*) malloc(sizeof(listaruchow));
  int maxocena;
    for(listaruchow *lr = ruchy_dostepne(G); lr; lr = lr->nast)
    {
      printf("ruchy: %d %d\n", lr->x, lr->y);
      i++;
      gra dziecko = wstaw(*G, lr->y, lr->x);
      nowaocena[i] = -negamax(&dziecko, glebokosc, alfa, beta);
      printf("Przypisuję współrzędne x:%d y:%d to struktury nr %d\n", lr->x, lr->y, i);
      naj_pole[i].x = lr->x;
      naj_pole[i].y = lr->y;
      printf("naj_pole dla struktury %d x:%d y:%d\n", i, naj_pole[i].x, naj_pole[i].y);
    }
        i = 0;
        printf("\ni:%d\n",i);
        j->x = naj_pole[i].x;
        j->y = naj_pole[i].y;

        maxocena = -50;
        //ocena ruchu[2] -> 1,2 ==1
        //ocena ruchu[1] -> 1,0 ==-1
        //ocena ruchu[0] -> 0,0 ==15
        for(i;i<ile;i++)
        {
            printf("Ocena dla x:%d y:%d =%d\n",naj_pole[i].x, naj_pole[i].y ,nowaocena[i]);
            if(maxocena<nowaocena[i])
            {
                printf("i=%d\n",i);
                printf("Nowe naj_pole = x:%d y:%d\n",naj_pole[i].x, naj_pole[i].y);
                j->x = naj_pole[i].x;
                j->y = naj_pole[i].y;
                printf("j = x:%d y:%d\n",j->x, j->y);
                maxocena=nowaocena[i];
                //printf("wieksze j: %d\n",j);
            }
        }
        
    return j;
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
