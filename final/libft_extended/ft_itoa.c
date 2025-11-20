/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:23:21 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/26 13:47:25 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static unsigned int	ft_abs(int n)
{
	unsigned int	value;

	if (n < 0)
		value = (unsigned int)(-(long)n);
	else
		value = n;
	return (value);
}

static unsigned int	ft_char_amount(int n)
{
	unsigned int	char_amount;
	unsigned int	abs_n;

	char_amount = 0;
	if (n < 0)
		char_amount++;
	abs_n = ft_abs(n);
	while (abs_n > 9)
	{
		char_amount++;
		abs_n = abs_n / 10;
	}
	char_amount++;
	return (char_amount);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	abs_n;
	int				index;
	unsigned int	char_amount;

	char_amount = ft_char_amount(n);
	index = char_amount - 1;
	result = malloc((char_amount + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	abs_n = ft_abs(n);
	while (index >= 0)
	{
		if (index == 0 && n < 0)
			break ;
		result[index] = (abs_n % 10) + '0';
		abs_n = abs_n / 10;
		index--;
	}
	result[char_amount] = '\0';
	return (result);
}
