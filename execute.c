/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

int ultimo(int argc, char **args)
{
    if( args[argc-1][0] == '&')
    {
        args[argc-1] = NULL;
        return BG;
    }

    return FG;
}

void execute (int argc, char **args)
{
    int pid, status;

    int pidNovoFilho = 0, fd[2];
    int indice = containsPipe(argc, args);
    int code = ultimo(argc, args);

    if (code == BG)
        argc--;

    if ((pid = fork ()) < 0)
    {				
        // cria um processo progenito
        perror ("forks");		
        // NOTE: perror() produz uma pequema mensagem de erro para o stream
        exit (1);			
        // estandardizado de erros que descreve o ultimo erro encontrado durante uma chamada ao sistema ou funcao duma biblioteca
    }

    if (pid == 0)
    {
        redirects(args, argc);
        if(indice > 0)
        {
        args[indice] = NULL;
        argc -=1;
        pipe(fd);
        pidNovoFilho = fork();

        if(pidNovoFilho == 0)
        {
                //write
                argc = indice;
                dup2(fd[1],STDOUT_FILENO);
                close(fd[0]);
                execvp(*args, args);
              }
              else
              {
                //read
                args = args+indice+1;
                argc=argc-indice-1;

                dup2(fd[0], STDIN_FILENO);
                close(fd[1]);
                execvp(*args, args);
              }

           }
           else
           {
             execvp(*args, args);
           }

           perror(*args);
        exit (1);			/* execv() e execvp() sao o nome do ficheiro
				 * a ser executado e um */
    }
    /* vector de strings que contem os argumentos. O ultimo argument */

    if(FG == code)
        while (wait (&status) != pid)
            /*spin fazer nada*/ ;
  
  return;
}