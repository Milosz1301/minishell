/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:17:59 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/20 18:28:53 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_expand_home(char **argv, char *homepath)
{
	char	*temp;

	if (!*argv)
		return (0);
	temp = NULL;
	if (**argv == '~')
	{
		temp = ft_strjoin(homepath, (*argv + 1));
		free(*argv);
		*argv = temp;
	}
	return (0);
}

void	ft_cd_op(char *operand, t_envar *pwd, t_envar *old_pwd)
{
	struct stat	st;
	char		*temp;

	temp = NULL;
	if (!stat(operand, &st) && S_ISDIR(st.st_mode) && !access(operand, X_OK))
	{
		temp = pwd->value;
		free(old_pwd->value);
		old_pwd->value = ft_strdup(temp);
		chdir(operand);
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
}

int	ft_cd(char **argv, t_shell *shell)
{
	t_envar	*pwd;
	t_envar	*old_pwd;
	t_envar	*home;

	if (!argv || !*argv || (argv[1] && argv[2]))
	{
		shell->err->cd = 1;
		return (shell->last_exit = 1);
	}
	pwd = ft_get_envar(shell->envc, "PWD", shell->err);
	old_pwd = ft_get_envar(shell->envc, "OLDPWD", shell->err);
	home = ft_get_envar(shell->envc, "HOME", shell->err);
	if (!argv[1])
		ft_cd_op(home->value, pwd, old_pwd);
	else
	{
		ft_expand_home(&argv[1], home->value);
		ft_cd_op(argv[1], pwd, old_pwd);
	}
	ft_freearr(shell->envp, ft_envar_amount(shell->envc, shell->err));
	shell->envp = ft_set_envp(shell->envc, shell->err);
	return (shell->last_exit = 0);
}
