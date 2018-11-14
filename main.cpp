#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "onegin.h"

int main()
{
    FILE* fin = fopen("INPUT.txt", "r");
    FILE* fout = fopen("OUTPUT", "w");

    if(Onegin(fout, fin) != 0)
    {
       printf("Error!!\n");
    }
    fclose(fin);
    fclose(fout);

    return 0;
}
