#ifndef funkcje_h
#define funkcje_h
#include "ogolne.h"

gra *utworz(int N);

void start(gra G);

Ruch *dane(gra *G, int wiersz, int kolumna);

listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna);

listaruchow *ruchy_dostepne(gra *G, int N, int ile);

int wynik(int a);

int ocena(gra *G, int N);

void wypisz_plansze(gra *G, int N);

int mozliwe_ruchy(gra *G, int N);

gra *wstaw(gra *G, int N, int wiersz, int kolumna);

#endif