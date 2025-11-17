/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:26:49 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/25 15:56:53 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*cur_char;
	char	*last_occ;

	cur_char = (char *)s;
	last_occ = NULL;
	while (*cur_char)
	{
		if (c % 256 == (unsigned char)*cur_char)
			last_occ = cur_char;
		cur_char++;
	}
	if (c == '\0')
		return (cur_char);
	return (last_occ);
}
