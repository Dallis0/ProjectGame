#ifndef ogolne_h
#define ogolne_h

#define X 1
#define O 0
// #define N 3
#define W 3

typedef struct _gra{
   char **pole, *ruch;
} gra;

typedef struct _listaruchow{
   char *gdzie;
   int x;
   int y;
   struct _listaruchow *nast;

} listaruchow;

#endif