#include "shell.h"

// Buffer para guardar o prompt da shell;
char prompt[100] = {0};

int main ()
{
  int len = 0; // Tamanho da String;
  char buf[1024] = {0}; // Buffer para guardar a string total que foi escrita;
  char *args[64]; // Buffer para guardar a string total, dividida em argumentos (sendo o espaço o termo de divisão);

  strcpy (prompt, DEFAULT_PREFIX); // Para facilitar, será copiado o PROMPT para o default;

  while (1)
  {
    printf ("%s", prompt); // Imprime o PROMPT;

    // Caso não vá buscar nada do que foi inserido (Exemplo: usar os comandos CTRL + C), o programa termina automaticamente;
    if (fgets (buf, 1023, stdin) == NULL)
	  {
	    printf ("\n");
	    exit (0);
	  }
    
    // Vai buscar o tamanho total inserido nos comandos da shell;
    len = strlen (buf);
    
    // Caso seja igual a 1, é ignorado (Exemplo: Apenas um "\n");
    if (1 == len)
	    continue;
      
    // Como no STDIN o "\n" fica no fim da string, será substituido pelo "\0" (fim da string)
    if (buf[len - 1] == '\n')
	    buf[len - 1] = '\0';

    // Divide a string em argumentos, retornando o seu número total;
    int argc = parse(buf, args);

    // Caso não seja um dos comandos customizados da shell, vai executar o comando normalmente;
    if (!builtin (argc, args))
	      execute (argc, args);
    }
  return 0;
}

// Comandos Customizados da Shell;
int builtin (int argc, char **args)
{
  // Sair da Shell
  if (strcmp (args[0], "sair") == 0)
  {
    exit (0);
    return 1;
  }

  // Caso queira mudar o comando do prompt, usando "PS1=" no inicio;
  if (strlen(args[0]) > 4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    if(0 == strcmp(args[0], "PS1={default}"))
    {
      strcpy(prompt, DEFAULT_PREFIX);
    }
    else
    {
      strcpy(prompt, "[");
      strcat(prompt, args[0]+4);
      strcat(prompt, "] > ");
    }
    return 1;
  }

  // Print do ID do PC
  if(0 == strcmp(args[0], "quemsoueu"))
  {
    system("id");
    return 1;
  }

  // Copia o conteúdo de um ficheiro para outro (em baixo nível);
  if(0 == strcmp(args[0], "socp"))
  {
    if(argc < 3)
    {
      printf("Não inseriste argumentos suficientes!");
      return 1;
    }
    else
    {
      socp(args[1], args[2]);
      return 1;
    }
  }

  // Imprime os conteúdos da pasta local no STDOUT
  if(0 == strcmp(args[0], "sols"))
  {
    sols(argc, args);
    return 1;
  }

  // Obter informações da Shell
  if(0 == strcmp(args[0], "obterinfo"))
  {
    fprintf(stderr, "%s\n", INFO);
    return 1;
  }

  // Calculadora básica;
  if(0 == strcmp(args[0], "calc"))
  {
    // Caso não tenha 4 argumentos, será mandado uma mensagem de erro;
    if(argc < 4)
    {
      fprintf(stderr, "O número de argumentos tem de ser igual a 4!\n");
    }
    else
    {
      calc(args[1], args[2], args[3]);
    }
  
    return 1;
  }

  // Calculadora bnária básica;
  if(0 == strcmp(args[0], "bits"))
  {
    // Caso não tenha 4 argumentos, será mandado uma mensagem de erro;
    if(argc < 4)
    {
      fprintf(stderr, "O número de argumentos tem de ser igual a 4!\n");
    }
    else
    {
      bits(args[1], args[2], args[3]);
    }
  
    return 1;
  }

  if(0 == strcmp(args[0], "isjpg"))
  {
    if(argc < 2)
    {
      fprintf(stderr, "O número de argumentos tem de ser igual a 2!\n");
    }
    else
    {
      isjpg(open(args[1], O_RDONLY));
    }
    
	return 1;
  }

  if(0 ==  strcmp(args[0], "avisoTeste"))
  {
    if(argc < 3)
      fprintf(stderr, "O número de argumentos tem de ser igual a 3!\n");
    else
      Aviso(args[1], atoi(args[2]));

    return 1;
  }

  if(0 ==  strcmp(args[0], "avisoth"))
  {
    if(argc < 3)
      fprintf(stderr, "O número de argumentos tem de ser igual a 3!\n");
    else
    {
      pthread_t th;
      aviso_t *ptr = (aviso_t *) malloc(sizeof(aviso_t));
      strcpy(ptr->mensagem, args[1]);
      ptr->tempo = atoi(args[2]);
      pthread_create(&th, NULL, AvisoWrapper, (void *) ptr);
    }

    return 1;
  }

  if(0 == strcmp(args[0], "socp"))
  {
    if(argc < 3)
    {
      printf("Não inseriste argumentos suficientes!");
      return 1;
    }
    else
    {
      socp(args[1], args[2]);
    }
  }

  if(0 == strcmp(args[0], "socpth"))
  {
    if(argc < 3)
    {
      printf("Não inseriste argumentos suficientes!");
      return 1;
    }
    else
    {
      pthread_t th;
      copiar_t *ptr = (copiar_t *) malloc(sizeof(copiar_t));
      strcpy(ptr->input, args[1]);
      strcpy(ptr->output, args[2]);
      pthread_create(&th, NULL, socpWrapper, (void *) ptr);
      return 1;
    }
  }
  
  // Mudança de diretoria;
  if(0 == strcmp(args[0], "cd"))
  {
    int err = 0;

    // Caso não insere algo como 2º argumento, ou for "~", muda para a "Home Directory"
    if (argc < 2 || (0 == strcmp(args[1], "~")))
    {
      err = chdir(getenv("HOME"));
    }
    else
    {
      err = chdir(args[1]);
    }

    // Caso seja menor que 0, significa que houve um erro na diretoria;
    if(err < 0)
      perror("Ocorreu um erro ao mudar a diretoria!");
  
	return 1;
  }

  // Como retorna 0, nenhum comando foi utilizado!
  return 0;
}