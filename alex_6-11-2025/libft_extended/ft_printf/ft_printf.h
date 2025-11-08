/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:35:35 by akonstan          #+#    #+#             */
/*   Updated: 2025/02/22 15:58:43 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft.h"
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putptr_r(void *ptr);
int	ft_putstr_r(char *str);
int	ft_putchar_r(int c);
int	ft_puthex_r(unsigned int num, char specifier);
int	ft_putnbr_r(int num);
int	ft_putuns_r(unsigned int num);

#endif
