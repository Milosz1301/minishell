/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:26:13 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:26:14 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	unsigned int	counter;
	const char		*refer;

	if (!s)
		return (0);
	refer = s;
	counter = 0;
	while (*refer)
	{
		counter++;
		refer++;
	}
	return (counter);
}
