#include "onegin.h"

long Sizeof_file(FILE *fin)
{
    assert(fin);

    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    return size;
}

int Count_line(char *buff, long file_size)
{
    assert(buff);

    int count_line = 0;

    for (int i = 0; i < file_size; i++)
    {
        if (buff[i] == '\n')
        {
            buff[i] = '\0';
            count_line++;
        }
    }

    buff[file_size] = '\0';
    if(file_size != 0)
    {
        count_line++;
    }

    return count_line;
}

String_view* Make_buffstr(char* buff, int count_line, long file_size, int* count_empty)
{
    assert(count_empty);
    assert(buff);

    String_view* strings = (String_view*) calloc((size_t) count_line, sizeof(* strings));
    assert(strings);

    char* ptrString = buff;
    int i = 0;
    int cur_position = 0;

    for(int j = 0; j < file_size + 1; j++)
    {
        if(buff[j] == '\0')
        {
            strings[i].length = j - cur_position;
            if(i == 0)
            {
                strings[i].length++;
            }
            strings[i].string = ptrString;
            ptrString = &(buff[j]) + 1;
            cur_position = j;
            if(strings[i].length == 1)
            {
                (*count_empty)++;
            }
            else
            {
                i++;
            }
        }
    }
    return strings;
}

void Print_text(FILE* file, String_view* strings, int count_line)
{
    assert(count_line);
    assert(file);
    assert(strings);

    int i = 0;
    for(i = 0; i < count_line; i++)
    {
        fprintf(file, "%s\n", strings[i].string);
    }
}

int Comparator(const void* const_str1, const void* const_str2)
{
    assert(const_str1);
    assert(const_str2);
    String_view str1 = *(String_view *) const_str1;
    String_view str2 = *(String_view *) const_str2;

    while (isdigit(*(str1.string)) || isspace(*(str1.string))
           || ispunct(*(str1.string)))
    {
        (str1.string)++;
    }
    while (isdigit(*(str2.string)) || isspace(*(str2.string))
           || ispunct(*(str2.string)))
    {
        (str2.string)++;
    }
    return strcmp(str1.string, str2.string);
}

int Onegin(FILE* fout, FILE* fin)
{
    if(fout == NULL)
    {

        return -10;
    }
    if(fin == NULL)
    {
        return -11;
    }


    assert(fout);
    assert(fin);


    long file_size = Sizeof_file(fin);
    if(file_size <= 0)
    {
        return -3;
    }

    char* buff = (char*) calloc ((size_t)file_size + 1, sizeof(* buff));
    if(buff == NULL)
    {
        return -12;
    }
    assert(buff);

    size_t result = fread(buff, sizeof(char), (size_t) file_size, fin);
    if (result != file_size)
    {
        return -4;
    }
    int count_line = Count_line(buff, file_size);
    if(count_line <= 0)
    {
        return -5;
    }

    int count_empty = 0;
    String_view* strings = Make_buffstr(buff, count_line, file_size, &count_empty);
    assert(strings);
    if(strings == NULL)
    {
        return -13;
    }

    int real_count_line = count_line - count_empty;


    char* buff_copy = (char*) calloc ((size_t)file_size + 1, sizeof(* buff_copy));
    assert(buff_copy);
    memcpy(buff_copy, (const char*) buff, ((size_t)file_size + 1) *  sizeof(* buff));
    String_view* strings_copy = Make_buffstr(buff_copy, count_line, file_size, &count_empty);

    Print_text(fout, strings_copy, real_count_line);


    Free_mem(buff, buff_copy, strings_copy, strings);
    return 0;

}

void Free_mem(char* buff, char* buff_copy, String_view* strings_copy, String_view* strings)
{
    free(buff);
    buff = NULL;
    free(buff_copy);
    buff_copy = NULL;
    free(strings_copy);
    strings_copy = NULL;
    free(strings);
    strings = NULL;
}




String_view*  Sort_str(String_view* strings, int count_real_lines)
{
    assert(strings);
    qsort(strings, (size_t) count_real_lines, sizeof(*strings), Comparator);
    return strings;
}

