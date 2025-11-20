/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:55:10 by akonstan          #+#    #+#             */
/*   Updated: 2025/02/22 15:59:06 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putuns_r(unsigned int num)
{
	int		sum;
	char	numchar;

	sum = 0;
	numchar = 0;
	if (num > 9)
		sum += ft_putuns_r(num / 10);
	sum++;
	numchar = num % 10 + '0';
	write(1, &numchar, 1);
	return (sum);
}
