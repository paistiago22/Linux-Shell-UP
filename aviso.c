#include "shell.h"

void Aviso(char *mensagem, int tempo){
    while(tempo > 0){
        sleep(1);
        tempo--;
    }
    fprintf(stderr, "Aviso : %s\n", mensagem);
}

void *AvisoWrapper(void *args){
    aviso_t *ptr = (aviso_t *) args;
    Aviso(ptr->mensagem, ptr->tempo);
    free(ptr);
    return NULL;
}