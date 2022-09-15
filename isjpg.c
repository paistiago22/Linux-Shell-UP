#include "shell.h"

/*
   isjpg.c – Verifica se o ficheiro é um jpg
*/
int isjpg(int fileDescriptor)
{
  if(fileDescriptor < 0)
  {
    fprintf(stderr, "O Ficheiro não existe!\n");
    return 0;
  }

  unsigned char b[4];
  read(fileDescriptor,b,4);

  if (b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0)
  {
    fprintf(stderr, "O ficheiro é um JPG!\n");
    return 1;
  }

  fprintf(stderr, "O ficheiro não é um JPG!\n");
  return 0;
}
