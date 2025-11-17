/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:21:09 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:21:11 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
