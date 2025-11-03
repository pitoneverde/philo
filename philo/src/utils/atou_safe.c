#include "philo.h"
#include <limits.h>
#include <ctype.h>

unsigned int	atou_safe(char *num, int *check)
{
    unsigned int result;
    unsigned int digit;

    *check = 0;
    while (isspace((unsigned char)*num))
        num++;
    if (*num == 0)
        return (0);
    result = 0;
    while (isdigit((unsigned char)*num))
    {
        digit = *num - '0';
        if (result > UINT_MAX / 10)     // Mult overflow
            return (*check = 0, UINT_MAX);
        result *= 10;
        if (result > UINT_MAX - digit)  // Add overflow
            return (*check = 0, UINT_MAX);
        result += digit;
        num++;
    }
    while (isspace((unsigned char)*num))
        num++;
    return (*check = (*num == 0), result);
}