#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>




int my_strcmp(char * str1, char *str2){
    int i=0,j=0;
    char symb_from_str1, symb_from_str2;
    while (str1[i]!='\0' && str2[j]!='\0')
    {
        while (str1[i]==' ')
            ++i;
        while (str2[j]==' ')
            ++j;
        if (str1[i]=='\0' || str2[j]=='\0')
            break;

        symb_from_str1 = str1[i];
        symb_from_str2 = str2[j];

        //printf("%c %c\n",symb_from_str1,symb_from_str2);

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
    if (str1[i]=='\0')
        return !(str2[j]=='\0');
    return -1;
}


void swap(char ** array, int from, int to)
{
    char * buf = array[from];
    array[from]=array[to];
    array[to]=buf;
}


void pre_sort(char ** array, int begin, int end)
{
    int mid = (begin+end)/2+(begin+end)%2;
    if (my_strcmp(array[mid],array[begin])==-1)
    {
        if (my_strcmp(array[begin],array[end])==-1)
            swap(array,begin,end);
        else if (my_strcmp(array[mid],array[end])==1)
            swap(array,mid,end);
    }
    else if (my_strcmp(array[mid],array[end])==-1)
        swap(array,mid,end);
    else if (my_strcmp(array[begin],array[end])==1)
        swap(array,begin,end);
}


void quick_sort(char ** array, int begin, int end)
{
    if (begin>=end)
        return;

    pre_sort(array,begin,end);

    for (int i=begin;i<=end;i++)
        puts(array[i]);
    puts("&");

    int i = begin, j = end;
    while (i<j){
        if (my_strcmp(array[i],array[j])==-1)
        {
            swap(array,j-1,j);
            if (i!=j-1)
                swap(array,i,j);
            j--;
        }
        else
            i++;
    }

    for (int i=begin;i<=end;i++)
        puts(array[i]);
    puts("");

    quick_sort(array,begin,j-1);
    quick_sort(array,j+1,end);
}

int main()
{
    char * array[10]={"Hello","Bye","new","old","red","blue","white","green","let s go","letsz"};
    //printf("%d\n",my_strcmp("letsz","blue"));
    quick_sort(array,0,9);
    for (int i=0;i<10;i++)
        puts(array[i]);
    /* printf("A=%d\nБ=%d\n",'А','Б');
    printf("A=%d\nБ=%d\n",'а','б'); */
    return 0;
}
