#include <stdio.h>
#include <string.h>


#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#define $unittest_simple(calc_value, real_value)\
    if (calc_value!=real_value)\
    {\
        printf("[TEST FAILED] ");\
    }\
    else\
    {\
        printf("[TEST PASSED] ");\
    }\
    printf("%d %d %s %d\n",calc_value,real_value,__FILE__,__LINE__);\

#define $unittest_qsort(calc_array_after_sort, real_array_after_sort, size)\
    int unittest_qsort_i = 0;\
    for (unittest_qsort_i;unittest_qsort_i<size;unittest_qsort_i++)\
    {\
        if (strcmp(calc_array_after_sort[unittest_qsort_i],real_array_after_sort[unittest_qsort_i]))\
        {\
            printf("[TEST FAILED] ");\
            printf("%s %s %s %d\n",calc_array_after_sort[unittest_qsort_i],real_array_after_sort[unittest_qsort_i],__FILE__,__LINE__);\
            break;\
        }\
    }\
    if (unittest_qsort_i==size)\
        printf("[TEST PASSED] %s %d\n",__FILE__,__LINE__);\

#endif // TEST_H_INCLUDED
