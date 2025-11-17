/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:20:57 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/25 16:26:41 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	char			*ref;
	unsigned int	value;
	int				sign;

	ref = (char *)nptr;
	value = 0;
	sign = 1;
	while (ft_isspace((int)*ref) == 0)
		ref++;
	if (*ref == '-' || *ref == '+')
	{
		if (*ref == '-')
			sign *= -1;
		ref++;
	}
	while (ft_isdigit(*ref) == 1)
	{
		value = value * 10 + (*ref - '0');
		ref++;
	}
	return (sign * value);
}
