#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long int iterative_fib(unsigned long long int addedValue, unsigned long long int prev_term, unsigned long long int prev_2_terms);
unsigned long long int recursive_fib(unsigned long long int addedValue);
unsigned long long int memoized_fib(unsigned long long int addedValue, unsigned long long int (*fib_func)(unsigned long long int, unsigned long long int, unsigned long long int), const char *filename);
void load_memo(const char *filename, unsigned long long int *memo, unsigned long long int size);
void save_memo(const char *filename, unsigned long long int *memo, unsigned long long int size);

int main(int argc, char *argv[])
{
   char* ITERATIVE = "i";
   char* RECURSIVE = "r";
   char user_choice_i_or_r[2];
   unsigned long long int user_entered_integer;
   unsigned long long int prev_term = 1;
   unsigned long long int prev_2_terms = 0;

   if (argc != 3) {
        printf("Usage: %s <integer> <i/r>\n", argv[0]);
        return 1;
    }

   sscanf(argv[1], "%llu", &user_entered_integer);
   sscanf(argv[2], "%1s", user_choice_i_or_r);
  
   unsigned long long int addedValue = user_entered_integer;

   if (strcmp(ITERATIVE, user_choice_i_or_r) == 0)
   {
        unsigned long long int result = memoized_fib(addedValue, (unsigned long long int (*)(unsigned long long int, unsigned long long int, unsigned long long int))iterative_fib, "memo_iterative.txt");
        printf("%llu", result);
   }

   if (strcmp(RECURSIVE, user_choice_i_or_r) == 0)
   {
        addedValue--;
        unsigned long long int result = memoized_fib(addedValue, (unsigned long long int (*)(unsigned long long int, unsigned long long int, unsigned long long int))recursive_fib, "memo_recursive.txt");
        printf("%llu", result);
   }
   return 0;
}

unsigned long long int iterative_fib(unsigned long long int addedValue, unsigned long long int prev_term, unsigned long long int prev_2_terms)
{
    for (int i = 1; i <= addedValue; i++)
    {
        if (i > 2)
        {
            unsigned long long int current_term = prev_term + prev_2_terms;
            prev_2_terms = prev_term;
            prev_term = current_term;
        }
    }
    return prev_term;
}

unsigned long long int recursive_fib(unsigned long long int addedValue)
{
    if (addedValue == 0)
    {
        return 0;
    }
    if (addedValue == 1)
    {
        return 1;
    }

    else
    {
    return (recursive_fib(addedValue - 1) + recursive_fib(addedValue - 2));
    }
}

unsigned long long int memoized_fib(unsigned long long int addedValue, unsigned long long int (*fib_func)(unsigned long long int, unsigned long long int, unsigned long long int), const char *filename)
{
    unsigned long long int *memo = (unsigned long long int *)malloc((addedValue + 1) * sizeof(unsigned long long int));
    for (unsigned long long int i = 0; i <= addedValue; i++) 
    {
        memo[i] = -1;
    }

    load_memo(filename, memo, addedValue + 1);

    unsigned long long int result;
    if (memo[addedValue] != -1)
    {
        result = memo[addedValue];
    }
    else
    {
        result = fib_func(addedValue, 1, 0);
        memo[addedValue] = result;
    }

    save_memo(filename, memo, addedValue + 1);

    free(memo);
    return result;
}

void load_memo(const char *filename, unsigned long long int *memo, unsigned long long int size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return;
    }

    for (unsigned long long int i = 0; i < size; i++)
    {
        fscanf(file, "%llu", &memo[i]);
    }

    fclose(file);
}

void save_memo(const char *filename, unsigned long long int *memo, unsigned long long int size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return;
    }

    for (unsigned long long int i = 0; i < size; i++)
    {
        fprintf(file, "%llu\n", memo[i]);
    }

    fclose(file);
}