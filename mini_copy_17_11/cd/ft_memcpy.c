/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:24:14 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:24:17 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destrf;
	unsigned char	*srcrf;

	destrf = (unsigned char *)dest;
	srcrf = (unsigned char *)src;
	while (n > 0)
	{
		*destrf = *srcrf;
		srcrf++;
		destrf++;
		n--;
	}
	return (dest);
}
