#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <dirent.h>

typedef struct
{
    char mensagem[100];
    int tempo;
}aviso_t;

typedef struct
{
    char input[100];
    char output[100];
}copiar_t;

int parse(char *buf, char **args);

void execute(int argc, char **args);

int builtin(int argc, char **args);

void socp(char *fonte, char *destino);

int isjpg(int fileDescriptor);

int sols(int argc, char *argv[]);

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int containsPipe(int numArgs,char **args);
// Ficheiro: redirects.c
int redirects(char *args[], int numargs);

void Aviso(char *mensagem, int tempo);

void *AvisoWrapper(void *args);

void *socpWrapper(void *args);

/* constantes que podem tornar uteis*/

#define DEBUG 1

#define BG 0
#define FG 1

#define INFO "SoShell 2019 v1.0 (30/04/2019)"

// TAGS DEFAULT DA SHELL

#define DEFAULT_PREFIX "[SoShell] ► "