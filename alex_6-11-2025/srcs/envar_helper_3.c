/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/09/26 18:49:36 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function will be checking if a string consists of valid characters for
//an env variable name
int	ft_valid_env(char *key, t_error *err)
{
	if (!key)
		return (err->valid_env = 1);
	while (*key && ft_isenvchar(*key))
		key++;
	if (*key)
		return (err->valid_env = 1);
	return (err->valid_env = 0);
}

//A function that returns the amount of environment variables in the t_envar
//chain
size_t	ft_envar_amount(t_envar *envc, t_error *err)
{
	size_t	res;

	if (!envc)
	{
		err->envar_amount = 1;
		return (0);
	}
	res = 0;
	while (envc)
	{
		res++;
		envc = envc->next;
	}
	err->envar_amount = 0;
	return (res);
}
