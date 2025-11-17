/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:24:36 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:24:38 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_overlap(unsigned char *dest, unsigned char *src, size_t bytes)
{
	if (src < dest && dest < src + bytes)
	{
		return (1);
	}
	else
		return (0);
}

static void	ft_writefw(unsigned char *dest, unsigned char *src, size_t bytes)
{
	while (bytes > 0)
	{
		*dest = *src;
		dest++;
		src++;
		bytes--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destrf;
	unsigned char	*srcrf;

	destrf = dest;
	srcrf = (unsigned char *)src;
	if (ft_overlap(destrf, srcrf, n) == 1)
	{
		destrf += n - 1;
		srcrf += n - 1;
		while (n > 0)
		{
			*destrf = *srcrf;
			destrf--;
			srcrf--;
			n--;
		}
	}
	else
		ft_writefw(destrf, srcrf, n);
	return (dest);
}
