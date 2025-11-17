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

int	ft_pwd(char **argv, t_shell *shell)
{
	t_envar	*pwd_var;
	char	*pwd_str;

	if (argv[1])
		return (shell->last_exit = -1);
	pwd_var = ft_get_envar(shell->envc, "PWD", shell->err);
	pwd_str = NULL;
	if (!pwd_var)
		pwd_str = getcwd(NULL, 0);
	else
		pwd_str = ft_strdup(pwd_var->value);
	ft_putendl_fd(pwd_str, STDOUT_FILENO);
	free(pwd_str);
	return (shell->last_exit = 0);
}
