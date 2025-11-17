/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:17:59 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/13 18:43:11 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd_operation(char *operand, char **pwd_value, char **old_pwd_value)
{
	struct stat	st;

	if (!stat(operand, &st))
	{
		if (S_ISDIR(st.st_mode))
		{
			if (!access(operand, X_OK))
			{
				*old_pwd_value = getcwd(NULL, 0);
				chdir(operand);
				*pwd_value = getcwd(NULL, 0);
			}
		}
	}
}

int	ft_cd(char **argv, t_shell *shell)
{
	char	*pwd_value;
	char	*old_pwd_value;
	t_envar	*pwd;
	t_envar	*old_pwd;

	if (!argv || !*argv)
	{
		shell->err->cd = 1;
		return (shell->last_exit = 1);
	}
	pwd = ft_get_envar(shell->envc, "PWD", shell->err);
	old_pwd_value = ft_get_envar(shell->envc, "OLDPWD", shell->err);
	if (!pwd)
		pwd_value = NULL;
	else
		pwd_value = &(pwd->key);
	if (!old_pwd)
		old_pwd_value = NULL;
	else
		old_pwd_value = &(old_pwd->key);
	ft_cd_op(*++argv, &pwd_value, &old_pwd_value);
	err->cd = 0;
	return (shell->last_exit = 0);
}
