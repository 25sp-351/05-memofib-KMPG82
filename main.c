#include <stdio.h>

#define MAX_MEMOIZED 100
#define ARRAY_SIZE (MAX_MEMOIZED + 1)
#define NO_VALUE_YET -1

typedef long (*long_func_ptr)(int param);

long_func_ptr factorial_provider;
long_func_ptr _original_provider;
long _memoization_data[ARRAY_SIZE];

/* calculates factorial for a number */
long factorial(int of_num) {
    if (of_num < 2)
        return of_num;

    return of_num * (*factorial_provider)(of_num - 1);
}

/* checks cache if the value has been stored */
long cache_func(int of_num) {
    if (of_num > MAX_MEMOIZED)
        return (*_original_provider)(of_num);

    if (_memoization_data[of_num] == NO_VALUE_YET)
        _memoization_data[of_num] = (*_original_provider)(of_num);
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
    factorial_provider = init_cache(factorial);

    for (int ix = 1; ix <= 10; ix++)
        printf("The factorial of %d is %ld\n", ix, (factorial_provider)(ix));

    return 0;
}
