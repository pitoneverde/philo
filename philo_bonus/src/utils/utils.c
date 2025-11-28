/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:59:05 by sabruma           #+#    #+#             */
/*   Updated: 2025/11/27 19:37:56 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_philo.h"

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

static size_t ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*c;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	c = (char *)malloc(len + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (i < len)
	{
		c[i] = s[i];
		i++;
	}
	c[len] = '\0';
	return (c);
}