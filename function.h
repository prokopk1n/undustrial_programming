#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

int is_punkt(char c);

int my_strcmp(char * str1, char *str2,int flag);

void swap(char ** array, int from, int to);

void pre_sort(char ** array, int begin, int end,int flag);

void quick_sort(char ** array, int begin, int end, int flag) ;

char * copy_file_to_memory(char * name);

char ** create_array_of_pointers(char * source_file, int * size);

char ** copy_array(char ** origin_array, int size);

void write_to_file(char ** array, int size, char * name);

#endif // FUNCTION_H_INCLUDED
