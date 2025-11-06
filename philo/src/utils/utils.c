#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 0x30 && c <= 0x39)
		return (c);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == 0x20 || (c >= 0x09 && c <= 0x0d))
		return (c);
	return (0);
}