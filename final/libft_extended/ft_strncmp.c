/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:26:27 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:26:28 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*s1rf;
	char	*s2rf;

	s1rf = (char *)s1;
	s2rf = (char *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if ((unsigned char)*s1rf != (unsigned char)*s2rf)
			return ((unsigned char)*s1rf -(unsigned char)*s2rf);
		if (*s1rf && *s2rf)
		{
			s1rf++;
			s2rf++;
			n--;
		}
		else
			break ;
	}
	return (0);
}
