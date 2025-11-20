/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:25:46 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:25:48 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		srclen;
	size_t		destlen;
	char		*destrf;
	const char	*srcrf;
	size_t		counter;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	srcrf = src;
	if (destlen >= size)
		return (size + srclen);
	destrf = dest + destlen;
	counter = size - destlen;
	while (*srcrf != '\0' && counter > 1)
	{
		*destrf = *srcrf;
		destrf++;
		srcrf++;
		counter--;
	}
	*destrf = '\0';
	return (destlen + srclen);
}
