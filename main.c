#include <stdio.h>

#define MAX_MEMOIZED 1000
#define ARRAY_SIZE (MAX_MEMOIZED + 1)
#define NO_VALUE_YET -1

typedef long (*long_func_ptr)(int number);

long fibonacci(int number);
long cache_func(int number);
long_func_ptr init_cache(long_func_ptr real_provider);

long_func_ptr fibonacci_provider;
long_func_ptr original_provider;
long memoization_data[ARRAY_SIZE];

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

/* calculates nth number of fibonacci sequence */
long fibonacci(int number) {
    if (number <= 1)
        return number;

    return (*fibonacci_provider)(number - 1) +
           (*fibonacci_provider)(number - 2);
}

/* checks cache if the value has been stored */
long cache_func(int number) {
    if (number > MAX_MEMOIZED)
        return (*original_provider)(number);

    if (memoization_data[number] == NO_VALUE_YET)
        memoization_data[number] = (*original_provider)(number);

    return memoization_data[number];
}

/* initializes cache */
long_func_ptr init_cache(long_func_ptr real_provider) {
    for (int ix = 0; ix < ARRAY_SIZE; ix++)
        memoization_data[ix] = NO_VALUE_YET;

    original_provider = real_provider;

    return cache_func;
}
