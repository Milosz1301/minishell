/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:23:52 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:23:54 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1rf;
	unsigned char	*s2rf;

	s1rf = (unsigned char *)s1;
	s2rf = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1rf != *s2rf)
			return (*s1rf - *s2rf);
		s1rf++;
		s2rf++;
		n--;
	}
	return (0);
}
