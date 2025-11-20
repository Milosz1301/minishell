/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:33:18 by akonstan          #+#    #+#             */
/*   Updated: 2025/02/22 15:58:02 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_specifier(va_list cur_arg, char specifier)
{
	int	sum;

	sum = 0;
	if (specifier == 'c')
		return (sum += ft_putchar_r(va_arg(cur_arg, int)));
	if (specifier == 's')
		return (sum += ft_putstr_r(va_arg(cur_arg, char *)));
	if (specifier == 'p')
		return (sum += ft_putptr_r(va_arg(cur_arg, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (sum += ft_putnbr_r(va_arg(cur_arg, int)));
	if (specifier == 'u')
		return (sum += ft_putuns_r(va_arg(cur_arg, unsigned int)));
	if (specifier == 'x' || specifier == 'X')
		return (sum += ft_puthex_r(va_arg(cur_arg, unsigned int), specifier));
	if (specifier == '%')
	{
		write(1, "%", 1);
		sum++;
	}
	return (sum);
}

int	ft_printf(const char *format, ...)
{
	int		sum;
	va_list	list;

	sum = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format != '%')
			sum += ft_putchar_r(*format);
		else
		{
			format++;
			sum += ft_specifier(list, *format);
		}
		if (*format)
			format++;
	}
	va_end(list);
	return (sum);
}
