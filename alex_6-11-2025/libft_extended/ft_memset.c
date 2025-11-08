/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:24:54 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:24:56 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *buffer, int c, size_t n)
{
	unsigned char	*refer;
	unsigned char	i;

	refer = (unsigned char *)buffer;
	i = (unsigned char)c;
	while (n > 0)
	{
		*refer = i;
		refer++;
		n--;
	}
	return (buffer);
}
