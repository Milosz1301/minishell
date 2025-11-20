/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:32:29 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//This function checks whether theres a built in being called
//and if it is, which one? (Yes, added +1 so that e.g cde input wont return 
// B_CD)
//There should be checked only the first argument (Yes exactly, if first string
//in argv is not a valid built-in or external command, we will give invalid 
//command error)
/*t_built_in	ft_check_for_built_in(char *string, t_error *err)
{
	if (!string)
		return(err->check_for_built_in = 1);
	if (!ft_strncmp(string, "cd", ft_strlen("cd") + 1))
		return (B_CD);
	else if (!ft_strncmp(string, "echo", ft_strlen("echo") + 1))
		return (B_ECHO);
	else if (!ft_strncmp(string, "env", ft_strlen("env") + 1))
		return (B_ENV);
	else if (!ft_strncmp(string, "exit", ft_strlen("exit") + 1))
		return (B_EXIT);
	else if (!ft_strncmp(string, "export", ft_strlen("export") + 1))
		return (B_EXPORT);
	else if (!ft_strncmp(string, "pwd", ft_strlen("pwd") + 1))
		return (B_PWD);
	else if (!ft_strncmp(string, "unset", ft_strlen("unset") + 1))
		return (B_UNSET);
	err->check_for_built_in = 0;
	return (B_NONE);
}*/
//Not just a concept, the function will look very close to this
/*int	ft_exec_built_in(t_built_in built_in, t_shell *shell, char **argv)
{
	if (!argv || !*argv)
		return (shell->err->exec_built_in = 1);
	if (built_in == B_CD)
		ft_cd(argv);
	else if (built_in == B_ECHO)
		ft_echo(argv);
	else if (built_in == B_ENV)
		ft_env(argv);
	else if (built_in == B_EXIT)
		ft_exit(argv);
	else if (built_in == B_EXPORT)
		ft_export(argv);
	else if (built_in == B_PWD)
		ft_pwd(arvg);
	else if (built_in == B_UNSET)
		ft_unset(argv);
	return (shell->err->exec_built_in = 0);
}*/
/*
static char    *ft_make_it_one_string(char **array)
{
	char	*str;
	int		i;

	i = 1;
	str = ft_strdup(array[i]);
	while (array[++i])
		str = ft_strjoin(str, array[i]);
	return (str);
}*/
//Flag can only be in second spot in echo
static bool	ft_check_for_nflag(char *argv)
{
	if (ft_strncmp(argv, "-n", 3) == 0)
		return (true);
	return (false);
}

//syntax will be checked earlier (before calling the echo function)
//No need for file descriptor usage, redirections and pipes will be replugging
//the stdin and stdout anyways. Pay attention that echo does not take input
//from stdin, just puts the string passed to the stdout (again, redirections
//and pipes are replugging it)
int	ft_echo(char **argv, t_shell *shell, t_error *err)
{
	int		i;

	if (!argv || !argv[0])
	{
		err->echo = 1;
		return (shell->last_exit = 1);
	}
	i = 1;
	if (argv[1] && ft_check_for_nflag(argv[1]) == 1)
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (argv[1] && ft_check_for_nflag(argv[1]) == 0)
		write(STDOUT_FILENO, "\n", 1);
	err->echo = 0;
	return (shell->last_exit = 0);
}
