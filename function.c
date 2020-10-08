#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>



int is_punkt(char c)
{
    char punkt_marks[] = {'.',',',';',':','!','?','-','"','\'','(',')',']','[','1','2','3','4','5','6','7','8','9','0','\0'};

    for (int i=0;punkt_marks[i]!='\0';++i)
    {
        if (c==punkt_marks[i])
            return 1;
    }

    return 0;
}

int my_strcmp(char * str1, char *str2,int flag){
    int i=0,j=0;
    char symb_from_str1, symb_from_str2;

    int len_str1 = strlen(str1), len_str2 = strlen(str2);

    char * buf_str1=calloc(len_str1+1,sizeof(char));
    char * buf_str2=calloc(len_str2+1,sizeof(char));

    if (flag==0)
    {
        for (int k=0;k<len_str1;k++)
            buf_str1[k] = str1[len_str1-k-1];
        buf_str1[len_str1]='\0';

        for (int k=0;k<len_str2;k++)
            buf_str2[k] = str2[len_str2-k-1];
        buf_str2[len_str2]='\0';
    }

    else
    {
       strcpy(buf_str1,str1);
       strcpy(buf_str2,str2);
    }

    while (buf_str1[i]!='\0' && buf_str2[j]!='\0')
    {
        while (buf_str1[i]==' ' || is_punkt(buf_str1[i]))
            ++i;
        while (buf_str2[j]==' ' || is_punkt(buf_str2[j]))
            ++j;
        if (buf_str1[i]=='\0' || buf_str2[j]=='\0')
            break;

        symb_from_str1 = buf_str1[i];
        symb_from_str2 = buf_str2[j];

        if (symb_from_str1>'A' && symb_from_str1<'Z')
            symb_from_str1 = 'a'+symb_from_str1-'A';

        if (symb_from_str2>'A' && symb_from_str2<'Z')
            symb_from_str2 = 'a'+symb_from_str2-'A';

        if (symb_from_str1>symb_from_str2)
        {
            free(buf_str1);
            free(buf_str2);
            return -1;
        }
        else if (symb_from_str1<symb_from_str2)
        {
            free(buf_str1);
            free(buf_str2);
            return 1;
        }
        i++;
        j++;
    }
    if (buf_str1[i]=='\0')
    {
        symb_from_str2 = buf_str2[j];
        free(buf_str1);
        free(buf_str2);
        return !(symb_from_str2=='\0');
    }

    free(buf_str1);
    free(buf_str2);
    return -1;
}


void swap(char ** array, int from, int to)
{
    char * buf = array[from];
    array[from]=array[to];
    array[to]=buf;
}


void pre_sort(char ** array, int begin, int end,int flag)
{
    int mid = (begin+end)/2+(begin+end)%2;
    if (my_strcmp(array[mid],array[begin],flag)==-1)
    {
        if (my_strcmp(array[begin],array[end],flag)==-1)
            swap(array,begin,end);
        else if (my_strcmp(array[mid],array[end],flag)==1)
            swap(array,mid,end);
    }
    else if (my_strcmp(array[mid],array[end],flag)==-1)
        swap(array,mid,end);
    else if (my_strcmp(array[begin],array[end],flag)==1)
        swap(array,begin,end);
}


void quick_sort(char ** array, int begin, int end, int flag) // flag 1 - for direct order, 0 - for reverse order
{
    if (begin>=end)
        return;

    pre_sort(array,begin,end,flag);


    int i = begin, j = end;
    while (i<j){
        if (my_strcmp(array[i],array[j],flag)==-1)
        {
            swap(array,j-1,j);
            if (i!=j-1)
                swap(array,i,j);
            j--;
        }
        else
            i++;
    }
    quick_sort(array,begin,j-1,flag);
    quick_sort(array,j+1,end,flag);
}


char * copy_file_to_memory(char * name)
{
    int handle_file_from = open(name,O_RDONLY);
    assert(handle_file_from!=-1);

    size_t size_of_file = 0;
    struct stat stat_buf;

    assert(fstat(handle_file_from, &stat_buf)==0);
    size_of_file = stat_buf.st_size;
    assert(size_of_file!=0);

    char * source_file = calloc(size_of_file, sizeof(char));

    unsigned int buf_for_size = 0;

    while (size_of_file > UINT_MAX)
    {
        buf_for_size = UINT_MAX;
        size_of_file  = size_of_file - UINT_MAX;
        assert(read(handle_file_from,source_file,buf_for_size)==buf_for_size);
    }

    assert(read(handle_file_from,source_file,size_of_file)==size_of_file);

    assert(close(handle_file_from)==0);

    return source_file;
}



char ** create_array_of_pointers(char * source_file, int * size)
{
    int step_for_realloc = 50;
    int cur_size = 0;
    char ** array_of_pointers = NULL;
    int flag = 1;
    *size = 0;

    do
    {
        array_of_pointers = realloc(array_of_pointers, (cur_size + step_for_realloc)*sizeof(char *));

        for (int i = cur_size;i<cur_size+step_for_realloc;++i)
        {

            if ((*source_file) == '\n')
            {
                ++source_file;
                --i;
                continue;
            }

            array_of_pointers[i] = source_file;
            ++(*size);

            if ((*source_file) == '\0')
            {
                flag = 0;
                --(*size);
                break; // весь файл считан
            }

            source_file = strchr(source_file, '\n');
            (*source_file) = '\0';
            ++source_file;
        }

    cur_size=cur_size+step_for_realloc;

    } while (flag);

    return array_of_pointers;
}

char ** copy_array(char ** origin_array, int size)
{
    char ** copied_array = calloc(size,sizeof(char *));
    for (int i=0;i<size;++i)
        copied_array[i]=origin_array[i];

    return copied_array;
}

void write_to_file(char ** array, int size, char * name)
{
    int handle_file_out = open(name,O_WRONLY | O_TRUNC);
    assert(handle_file_out!=-1);

    int len_of_string = 0;
    for (int i=0;i<size;++i)
    {
        len_of_string = strlen(array[i]);
        while (len_of_string > UINT_MAX)
        {
            assert(write(handle_file_out, array[i], UINT_MAX)==UINT_MAX);
            array[i]=array[i]+UINT_MAX;
            len_of_string = len_of_string - UINT_MAX;
        }

        assert(write(handle_file_out, array[i],len_of_string)==len_of_string);
        assert(write(handle_file_out, "\n", 1)==1);
    }
    assert(close(handle_file_out)==0);
    free(array);
}
