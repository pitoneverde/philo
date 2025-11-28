#include "bonus_philo.h"
#include <limits.h>

int	utoa_len(unsigned int num);

char	*utoa(unsigned int num)
{
	int		len;
	char	*res;

	if (num == 0)
		return (ft_strdup("0"));
	len = utoa_len(num);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len--] = 0;
	while (num != 0)
	{
		res[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}

int	utoa_len(unsigned int num)
{
	int len;

	if (num == 0)
		return (1);
	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int	lltoa_len(long long num);

char	*lltoa(long long num)
{
	int		len;
	int		neg;
	char	*res;

	if (num == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	if (num == 0)
		return (ft_strdup("0"));
	len = lltoa_len(num);
	neg = num < 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	if (neg)
		num = -num;
	res[len--] = 0;
	while (num != 0)
	{
		res[len--] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}

int	lltoa_len(long long num)
{
	int len;

	len = 0;
	if (num <= 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}