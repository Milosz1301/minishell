/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:47:22 by akonstan          #+#    #+#             */
/*   Updated: 2025/02/21 16:50:59 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_r(int num)
{
	unsigned int	number;
	char			numchar;
	int				sum;

	numchar = 0;
	sum = 0;
	if (num < 0)
	{
		write(1, "-", 1);
		sum++;
		number = -num;
	}
	else
		number = num;
	if (number > 9)
		sum += ft_putnbr_r(number / 10);
	numchar = number % 10 + '0';
	sum++;
	write(1, &numchar, 1);
	return (sum);
}
