/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:56:14 by akonstan          #+#    #+#             */
/*   Updated: 2025/02/15 14:26:38 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

void	ft_bzero(void *buffer, size_t n)
{
	unsigned char	*refer;

	refer = (unsigned char *)buffer;
	while (n > 0)
	{
		*refer = 0;
		refer++;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	size_max;

	size_max = (size_t)-1;
	buffer = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (size > size_max / nmemb)
		return (NULL);
	buffer = malloc(nmemb * size);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, nmemb * size);
	return (buffer);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	size_max;
	char	*result;
	size_t	totallen;

	size_max = (size_t)-1;
	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len > size_max - s2len - 1)
		return (NULL);
	totallen = s1len + s2len + 1;
	if (totallen > size_max / sizeof(char))
		return (NULL);
	result = malloc(totallen * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1len + 1);
	ft_strlcpy(result + s1len, s2, s2len + 1);
	return (result);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	counter;
	const char		*refer;

	refer = s;
	counter = 0;
	while (*refer)
	{
		counter++;
		refer++;
	}
	return (counter);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		src_len;
	const char	*srcrf;
	char		*destrf;

	src_len = ft_strlen(src);
	srcrf = src;
	destrf = dest;
	if (size == 0)
		return (src_len);
	while (size > 1 && *srcrf != '\0')
	{
		*destrf = *srcrf;
		destrf++;
		srcrf++;
		size--;
	}
	if (size > 0)
		*destrf = '\0';
	return (src_len);
}
