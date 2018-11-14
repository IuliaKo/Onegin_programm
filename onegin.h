#ifndef ONEGIN_ONEGIN_H
#define ONEGIN_ONEGIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct String_view
{
    char* string;
    int length;
}String_view;

int             Onegin          (FILE* fout, FILE* fin);
long            Sizeof_file     (FILE *fin);
int             Count_line      (char *buff, long file_size);
String_view*    Make_buffstr    (char* buff, int count_line, long file_size, int* count_empty);
int             Comparator      (const void* const_str1, const void* const_str2);
void            Free_mem        (char* buff, char* buff_copy, String_view* strings_copy, String_view* strings);

#endif