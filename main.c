#include <stdio.h>
#include <stdlib.h>

#include "stock.h"

#define MAX 300

void main( void )
{
  FILE *F;
  char name[MAX], *str;
  int n_len, old_n_len = 0, str_len, i, j, k, cnst, sp_ind;

  printf("Needed length: ");
  scanf("%i", &n_len);

  printf("File name: ");
  scanf("%s", &name);

  if ((F = fopen(name, "rt")) == NULL)
    return;

  fseek(F, 0, SEEK_END);
  str_len = ftell(F);
  fseek(F, 0, SEEK_SET);
  str_len++;

  str = malloc(str_len * sizeof(char));

  for (i = 0; i < str_len - 1; i++)
  {
    char c = fgetc(F);
    if (c == '\n')
      str_len--;
    str[i] = c;
  }
  str[i] = '\0';

  str_len = i + 1;

  fclose(F);

  if ((F = fopen("a.out", "wt")) == NULL)
    return;

  cnst = n_len;

  for (i = 1, j = 0; j < str_len - 1; i++, j++)
  {
    if (n_len > old_n_len)
      if (j + cnst < str_len - 1 && str[j + cnst] != ' ')
      {
        for (k = j + cnst - 1; k >= j; k--)
          if (k < str_len - 1)
            if (str[k] == ' ')
            {
              sp_ind = k;
              k = -1;
            }
        if (k == j - 1)
          sp_ind = -1;
        old_n_len = n_len;
      }
      else
        sp_ind = -1;

    if (sp_ind != -1)
      if (j == sp_ind)
      {
        fputc('\n', F);
        n_len += cnst;
        i = n_len - cnst;
      }
      else
        fputc(str[j], F);
    else if (i == n_len && str[j + 1] != '\0')
    {
      if (str[j + 1] != ' ')
      {
        fputc('-', F);
        fputc('\n', F);
        fputc(str[j], F);
        i++;
      }
      else
      {
        fputc(str[j], F);
        j++;
        fputc('\n', F);
      }
      n_len += cnst;
    }
    else
      fputc(str[j], F);
  }

  fclose(F);
}
