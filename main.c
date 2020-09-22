#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>



int my_strcmp(char * str1, char *str2,int flag){
    int i=0,j=0;
    char symb_from_str1, symb_from_str2;
    char * buf_str1=NULL;
    char * buf_str2=NULL;

    if (flag==0)
    {
        int len_str1 = strlen(str1), len_str2 = strlen(str2);

        buf_str1 = calloc(len_str1,sizeof(char));
        buf_str2 = calloc(len_str2,sizeof(char));

        for (int k=0;k<len_str1;k++)
            buf_str1[k] = str1[len_str1-k-1];
        buf_str1[len_str1]='\0';

        for (int k=0;k<len_str2;k++)
            buf_str2[k] = str2[len_str2-k-1];
        buf_str2[len_str2]='\0';
    }

    else
    {
       buf_str1 = str1;
       buf_str2 = str2;
    }

    while (buf_str1[i]!='\0' && buf_str2[j]!='\0')
    {
        while (buf_str1[i]==' ')
            ++i;
        while (buf_str2[j]==' ')
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
            return -1;
        else if (symb_from_str1<symb_from_str2)
            return 1;
        i++;
        j++;
    }
    if (buf_str1[i]=='\0')
    {
        symb_from_str2 = buf_str2[j];
        if (!flag)
        {
            free(buf_str1);
            free(buf_str2);
        }
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


char * copy_file_to_memory(int handle_file_source)
{
    size_t size_of_file = 0;
    struct stat stat_buf;

    assert(fstat(handle_file_source, &stat_buf)==0);
    size_of_file = stat_buf.st_size;

    char * source_file = calloc(size_of_file, sizeof(char));

    unsigned int buf_for_size = 0;

    while (size_of_file > UINT_MAX)
    {
        buf_for_size = UINT_MAX;
        size_of_file  = size_of_file - UINT_MAX;
        assert(read(handle_file_source,source_file,buf_for_size)==buf_for_size);
    }

    assert(read(handle_file_source,source_file,size_of_file)==size_of_file);

    return source_file;
}



char ** create_array_of_pointers(char * source_file)
{
    int step_for_realloc = 50;
    int cur_size = 0;
    char ** array_of_pointers = NULL;
    int flag = 1;

    do
    {
        array_of_pointers = realloc(array_of_pointers, (cur_size + step_for_realloc)*sizeof(char *));
        cur_size=cur_size+step_for_realloc;

        for (int i = 0;i<step_for_realloc;++i)
        {
            array_of_pointers[i] = source_file;

            if ((*source_file) == '\0')
            {
                flag = 0;
                break; // весь файл считан
            }

            source_file = strchr(source_file, '\n');
            *source_file = '\0';
            ++source_file;
        }

    } while (flag);

    return array_of_pointers;
}

int main(int argc, char *argv[])
{
    // assert(argc==5);

    int handle_file_source = open(argv[1],O_RDONLY);
    /* int handle_file_out_direct = open(argv[2],O_WRONLY | O_TRUNC);
    int handle_file_out_reverse = open(argv[3],O_WRONLY | O_TRUNC);
    int handle_file_out_copy = open(argv[4],O_WRONLY | O_TRUNC);

    assert(handle_file_source!=-1);
    assert(handle_file_out_direct!=-1);
    assert(handle_file_out_reverse!=-1);
    assert(handle_file_out_copy!=-1); */

    char * source_file = copy_file_to_memory(handle_file_source);

    char ** array = create_array_of_pointers(source_file);

    for (int i=0; strlen(array[i])!=0; ++i)
        puts(array[i]);

    return 0;
}
