/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:31:30 by akonstan          #+#    #+#             */
/*   Updated: 2024/12/23 17:31:32 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*sdup;

	sdup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sdup)
		return (NULL);
	ft_strlcpy(sdup, s, ft_strlen(s) + 1);
	return (sdup);
}
