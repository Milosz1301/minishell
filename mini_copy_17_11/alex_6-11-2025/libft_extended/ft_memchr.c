/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:23:35 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/27 12:34:12 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*strrf;

	strrf = (unsigned char *)s;
	while (n > 0)
	{
		if ((unsigned char)(c % 256) == (unsigned char)*strrf)
			return ((void *)strrf);
		strrf++;
		n--;
	}
	return (NULL);
}
