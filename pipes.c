#include "shell.h"

/* Detect PIPE SYMBOL in array of Strings  return its index or -1 if it does not exist */
int containsPipe(int numArgs,char **args)
{
  int index;
  for(index = 0; index < numArgs; index++)
  {
    if(args[index][0] == '|')
    {
      return index;
    }
  }

  return -1;
}