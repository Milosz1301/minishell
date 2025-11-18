/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:17:59 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/13 17:33:43 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd_op(char *operand, t_envar *pwd, t_envar *old_pwd)
{
	struct stat	st;
	char	*temp;

	temp = NULL;
	if (!stat(operand, &st))
	{
		if (S_ISDIR(st.st_mode))
		{
			if (!access(operand, X_OK))
			{
				temp = pwd->value;
				free(old_pwd->value);
				old_pwd->value = ft_strdup(temp);
				chdir(operand);
				free(pwd->value);
				pwd->value = getcwd(NULL, 0);
			}
		}
	}
}

int	ft_cd(char **argv, t_shell *shell)
{
	//char	*pwd_value;
	//char	*old_pwd_value;
	t_envar	*pwd;
	t_envar	*old_pwd;

	if (!argv || !*argv)
	{
		shell->err->cd = 1;
		return (shell->last_exit = 1);
	}
	pwd = ft_get_envar(shell->envc, "PWD", shell->err);
	old_pwd = ft_get_envar(shell->envc, "OLDPWD", shell->err);
	/*if (!pwd)
		pwd_value = NULL;
	else
		pwd_value = pwd->key;
	if (!old_pwd)
		old_pwd_value = NULL;
	else
		old_pwd_value = old_pwd->key;*/
	ft_cd_op(argv[1], pwd, old_pwd);
	shell->err->cd = 0;
	return (shell->last_exit = 0);
}
