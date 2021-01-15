#ifndef funkcje_h
#define funkcje_h
#include "ogolne.h"

gra *utworz(int N);

void start(gra G);

<<<<<<< HEAD
Ruch dane(gra *G, int wiersz, int kolumna);

=======
>>>>>>> 52af5c4a728d53be6025a58c926ecafba2af2208
listaruchow *wstaw_na_puste(gra *G, int wiersz , int kolumna);

listaruchow *ostatni_r(listaruchow *glowa);

void wypisz_ruchy(listaruchow *lista, gra *G, int N);

listaruchow *ruchy_dostepne(gra *G, int N, int ile);

int wynik(int a);

int ocena(gra *G, int N);

void wypisz_plansze(gra *G, int N);

int ile_ruchow(gra *G, int N);

gra *wstaw(gra *G, int N, int wiersz, int kolumna);

#endif