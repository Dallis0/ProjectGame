#ifndef funkcje_h
#define funkcje_h
#include "ogolne.h"

gra *utworz(int N);

void start(gra G);

listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna);

listaruchow *ostatni_r(listaruchow *glowa);

void wypisz_ruchy(listaruchow *lista, gra *G, int N);

listaruchow *ruchy_dostepne(gra *G, int N, int ile);

int wynik(int a);

int ocena(gra *G, int N);

void wypisz_plansze(gra *G, int N);

int ile_ruchow(gra *G, int N);

gra *wstaw(gra *G, int N, int wiersz, int kolumna);

int negamax(gra *G, int glebokosc, int alfa, int beta, int N, int ile);

#endif