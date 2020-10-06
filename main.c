#include <stdlib.h>
#include "function.h"
#include <assert.h>
#include "test.h"


int main(int argc, char *argv[])
{
    assert(argc>=2);

    if (!strcmp(argv[1],"test"))
    {
       $unittest_simple(is_punkt('a'),0);
       $unittest_simple(is_punkt(';'),1);
       $unittest_simple(my_strcmp("dbc", "     -acd",1),-1);
       char * testing[] = {"abd","dbc","qwe","try","ddda"};
       char * after_qsort_direct[] = {"abd","dbc","ddda","qwe","try"};
       quick_sort(testing,0,4,1);
       $unittest_qsort(testing,after_qsort_direct,5);
    }

    else {
        assert(argc==5);

        char * source_file = copy_file_to_memory(argv[1]);

        int size = 0;
        char ** array_for_text = create_array_of_pointers(source_file,&size);

        char ** array_for_reverse_order = copy_array(array_for_text,size);
        char ** array_for_direct_order  = copy_array(array_for_text,size);

        quick_sort(array_for_direct_order,0,size-1, 1);
        quick_sort(array_for_reverse_order,0,size-1, 0);


        write_to_file(array_for_direct_order, size, argv[2]);
        write_to_file(array_for_reverse_order, size, argv[3]);
        write_to_file(array_for_text, size, argv[4]);

        free(source_file);
    }

    return 0;
}
