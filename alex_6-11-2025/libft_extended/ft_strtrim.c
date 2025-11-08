/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:27:07 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:27:09 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_inset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*trim;
	size_t		trimlen;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && ft_inset(*start, set) == 1)
		start++;
	while (end > start && ft_inset(*(end - 1), set) == 1)
		end--;
	trimlen = end - start;
	trim = malloc((trimlen + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, start, trimlen + 1);
	return (trim);
}
