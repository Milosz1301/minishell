/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:44:27 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/25 15:55:28 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*strrf;

	strrf = (char *)s;
	while (*strrf)
	{
		if (c % 256 == (unsigned char)*strrf)
			return (strrf);
		strrf++;
	}
	if (c == '\0')
		return (strrf);
	else
		return (NULL);
}
