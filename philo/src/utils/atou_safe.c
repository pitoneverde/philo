/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atou_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:06:31 by sabruma           #+#    #+#             */
/*   Updated: 2025/11/07 00:10:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <ctype.h>

// Parses only valid positive numbers, they can be surrounded by spaces.
// Included check on overflow to avoid invalid values
unsigned int	atou_safe(char *num, int *check)
{
	unsigned int	result;
	unsigned int	digit;

	*check = 0;
	while (ft_isspace((unsigned char)*num))
		num++;
	if (*num == 0)
		return (0);
	result = 0;
	while (ft_isdigit((unsigned char)*num))
	{
		digit = *num - '0';
		if (result > UINT_MAX / 10)
			return (*check = 0, UINT_MAX);
		result *= 10;
		if (result > UINT_MAX - digit)
			return (*check = 0, UINT_MAX);
		result += digit;
		num++;
	}
	while (isspace((unsigned char)*num))
		num++;
	return (*check = (*num == 0), result);
}
