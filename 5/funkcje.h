#ifndef funkcje_h
#define funkcje_h
#include "ogolne.h"


gra utworz();

void start(gra G);

void wypisz_ruchy(listaruchow *lista, gra *G);

listaruchow *ruchy_dostepne(gra *G);

int wynik(int a);

int ocena(gra *G);

void wypisz_plansze(gra *G);

int ile_ruchow(gra *G);

gra wstaw(gra G, int wiersz, int kolumna);

int negamax(gra *G, int glebokosc, int alfa, int beta);

listaruchow *najlepszy_ruch(gra *G, int glebokosc, int alfa, int beta);

#endif