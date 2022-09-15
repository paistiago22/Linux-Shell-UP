#include "shell.h"

/*
  Calc: Realiza uma operação (decimal) entre dois números;
    - value1: Primeiro número da operação;
    - op: Operador que será utilizado para a operação;
    - value2: Segundo número da operação;
*/
void calc(char *value1, char *op, char *value2)
{
  // Como os números estão guardados em strings, será preciso convertê-los para números reais;
  float v1 = atof(value1);
  float v2 = atof(value2);
  float resultado = 0.0;
  
  /*
    O Operador pode ser:
      - Soma;
      - Subtração;
      - Multiplicação;
      - Divisão;
      - Exponencial;
  */

  if(0 == strcmp(op, "+"))
    resultado = v1 + v2;
  else if(0 == strcmp(op, "-"))
    resultado = v1 - v2;
  else if(0 == strcmp(op, "*"))
    resultado = v1 * v2;
  else if(0 == strcmp(op, "/"))
  {
    // Obviamente, como não é possível dividir por 0, o cálculo será cancelado;
    if(v2 == 0.0)
    {
      printf("Lamento, mas não é possível dividir por zero!\n");
      return;
    }
    resultado = v1 / v2;
  }
  else if(0 == strcmp(op, "^"))
    resultado = powf(v1, v2);
  else
  {
    printf("Este operador não existe ou não é suportado por esta operação!\n");
    return;
  }

  // Caso o cálculo seja realizado com sucesso, será imprimido o resultado, tal como a operação que foi feita.
  printf("%0.2f %s %0.2f = %0.2f\n", v1, op, v2, resultado);
}

/*
  Bits: Realiza uma operação (binária) entre dois números;
    - value1: Primeiro número da operação;
    - op: Operador que será utilizado para a operação;
    - value2: Segundo número da operação;
*/
void bits(char *value1, char *op, char *value2)
{
  // Como os números estão guardados em strings, será preciso convertê-los para números inteiros;
  int v1 = atoi(value1);
  int v2 = atoi(value2);
  int resultado = 0;

  if(0 == strcmp(op, "&"))
    resultado = v1 & v2;
  else if(0 == strcmp(op, "^"))
    resultado = v1 ^ v2;
  else if(0 == strcmp(op, "|"))
    resultado = v1 | v2;
  else
  {
    printf("Este operador não existe ou não é suportado por esta operação!\n");
    return;
  }

  printf("%d %s %d = %d\n", v1, op, v2, resultado);
}
