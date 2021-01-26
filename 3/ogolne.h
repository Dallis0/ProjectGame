#ifndef ogolne_h
#define ogolne_h

#define X 1
#define O 0
#define N 3
#define W 3


typedef struct _gra{
   char pole[N][N], ruch[10];
} gra;

typedef struct _listaruchow{
   int x;
   int y;
   struct _listaruchow *nast;

} listaruchow;

#endif