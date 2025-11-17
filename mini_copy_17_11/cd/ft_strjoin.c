/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:32:06 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:32:07 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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
