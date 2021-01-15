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
<<<<<<< HEAD
   Ruch ruchy;
=======
   char *gdzie;
>>>>>>> 52af5c4a728d53be6025a58c926ecafba2af2208
   struct _listaruchow *nast;

} listaruchow;

#endif