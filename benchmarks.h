#ifndef BENCHMARKS_h
#define BENCHMARKS_h
/*=====================================================================
    UTILS.h
    Description         : Utility functions to be shared between 
                          measurement modules
======================================================================*/

/*=====================================================================
    Defines
======================================================================*/

/*=====================================================================
    Typedefs
======================================================================*/

/*=====================================================================
    Constants
======================================================================*/

const int NUM_COLLECTIONS = 1000000;

/*=====================================================================
    Functions
======================================================================*/

unsigned long long getMeasureOverhead(void);

int bogus_test_func0(void);

int bogus_test_func1(int a1);

int bogus_test_func2(int a1, int a2);

int bogus_test_func3(int a1, int a2, int a3);

int bogus_test_func4(int a1, int a2, int a3, int a4);

int bogus_test_func5(int a1, int a2, int a3, int a4, int a5);

int bogus_test_func6(int a1, int a2, int a3, int a4, int a5, int a6);

int bogus_test_func7(int a1, int a2, int a3, int a4, int a5, int a6, int a7);

void getProcedureCallOverhead(unsigned long long average[]);

#endif