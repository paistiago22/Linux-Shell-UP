#include "shell.h"


int sols(int argc,char *argv[])
{
  struct stat f1;
  struct dirent **namelist;
  int n;
  if(argc < 1)
  {
    return 0;
  }
  else if (argc == 1)
  { 
    n = scandir(".", &namelist, NULL, alphasort);
  }
  else
  {
    n = scandir(argv[1], &namelist, NULL, alphasort);
  }

  if(n < 0)
  {
    perror("scandir");
    return 0;
  }
  else
  {
    while (n--)
    {
      stat(namelist[n]->d_name, &f1);
      if(S_ISDIR(f1.st_mode) && (0 != strcmp(".", namelist[n]->d_name)) && (0 != strcmp("..", namelist[n]->d_name)))
      {
        printf("%s\n", namelist[n]->d_name);
      }
      else if(S_ISREG(f1.st_mode))
      {
        printf("%s\n", namelist[n]->d_name);
      }
      free(namelist[n]);
    }
    free(namelist);
  }
  
  return 1;
}
