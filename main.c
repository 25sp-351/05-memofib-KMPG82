#include <stdio.h>

#define MAX_MEMOIZED 1000
#define ARRAY_SIZE (MAX_MEMOIZED + 1)
#define NO_VALUE_YET -1

typedef long (*long_func_ptr)(int param);

long_func_ptr fibonacci_provider;
long_func_ptr _original_provider;
long _memoization_data[ARRAY_SIZE];

/* calculates fibonacci for a number */
long fibonacci(int of_num) {
    if (of_num <= 1)
        return of_num;

    return (*fibonacci_provider)(of_num - 1) +
           (*fibonacci_provider)(of_num - 2);
}

/* checks cache if the value has been stored */
long cache_func(int of_num) {
    if (of_num > MAX_MEMOIZED)
        return (*_original_provider)(of_num);

    if (_memoization_data[of_num] == NO_VALUE_YET) {
        _memoization_data[of_num] = (*_original_provider)(of_num);
    }
    
    return _memoization_data[of_num];
}

/* initializes cache */
long_func_ptr init_cache(long_func_ptr real_provider) {
    for (int ix = 0; ix < ARRAY_SIZE; ix++)
        _memoization_data[ix] = NO_VALUE_YET;

    _original_provider = real_provider;
    
    return cache_func;
}

int main() {
    fibonacci_provider = init_cache(fibonacci);

    for (int ix = 0; ix <= 10; ix++)
        printf("%ld ", (*fibonacci_provider)(ix));

    printf("\n");

    printf("%lu\n", (*fibonacci_provider)(10));

    printf("%lu\n", (*fibonacci_provider)(20));

    printf("%lu\n", (*fibonacci_provider)(40));

    printf("%lu\n", (*fibonacci_provider)(60));

    printf("%lu\n", (*fibonacci_provider)(70));

    printf("%lu\n", (*fibonacci_provider)(90));

    return 0;
}
