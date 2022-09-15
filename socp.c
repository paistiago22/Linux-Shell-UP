#include "shell.h"

/*
    socp.c – copia os dados de um ficheiro para outro
*/

void *socpWrapper(void *args)
{
  copiar_t *ptr = (copiar_t *) args;
  socp(ptr->input, ptr->output);
  return NULL;
}

void streamCopy (int entrada, int saida)
{
  int ch;
  char buffer[1];
  while((ch = read(entrada, buffer, 1)) > 0)
  {
    write(saida, buffer, ch);
  }
}

void socp(char *fonte, char *destino)
{
  if(fonte == NULL)
  {
    fprintf(stderr, "Erro a inserir no nome do ficheiro fonte!\n");
    return;
  }

  if(destino == NULL)
  {
    fprintf(stderr, "Erro a inserir no nome do ficheiro destino!\n");
    return;
  }

  int fent = open(fonte, O_RDWR);
  int fdest = open(destino, O_WRONLY);

  if(fent < 0)
  {
    fprintf(stderr, "Ficheiro fonte não existe!\n");
    return;
  }

  if(fdest < 0)
  {
    fdest = creat(destino,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  }

  streamCopy(fent,fdest);
  printf("Ficheiro %s copiado com sucesso para %s!\n", fonte, destino);

  close(fent);
  close(fdest);
}
