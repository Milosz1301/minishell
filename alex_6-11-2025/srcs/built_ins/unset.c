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

#include "../../minishell.h"

//Main unset function
int	ft_unset(char **argv, t_shell *shell)
{
	size_t	index;
	t_envar	*target;

	if (!argv || !argv[0] || !argv[1])
		return (shell->last_exit = 1);
	index = 1;
	target = NULL;
	while (argv[index])
	{
		target = ft_get_envar(shell->envc, argv[index], shell->err);
		if (target != NULL)
			ft_del_envar(&(shell->envc), target, shell->err);
		index++;
	}
	ft_freearr(shell->envp, ft_count_arr(shell->envp));
	shell->envp = ft_set_envp(shell->envc, shell->err);
	return (shell->last_exit = 0);
}
