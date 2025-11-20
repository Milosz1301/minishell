/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 22:02:21 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function checks whether theres a built in being called
//and if it is, which one? (Yes, added +1 so that e.g cde input wont return 
// B_CD)
//There should be checked only the first argument (Yes exactly, if first string
//in argv is not a valid built-in or external command, we will give invalid 
//command error)
t_built_in	ft_built_in_check(char *string, t_error *err)
{
	if (!string)
		return (err->built_in_check = -1);
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
	err->built_in_check = 0;
	return (B_NONE);
}

//Not just a concept, the function will look very close to this
//	if (built_in == B_CD)
//		ft_cd(argv);
//ADD THIS BACK WHEN CD IS READYY!!!!!
int	ft_exec_built_in(t_built_in built_in, t_shell *shell
		, char **argv, t_pipe *pipeline)
{
	if (!argv || !*argv)
		return (shell->err->exec_built_in = 1);
	if (built_in == B_CD)
		ft_cd(argv, shell);
	else if (built_in == B_ECHO)
		ft_echo(argv, shell, shell->err);
	else if (built_in == B_ENV)
		ft_env(argv, shell);
	else if (built_in == B_EXIT)
		ft_exit(pipeline, shell);
	else if (built_in == B_EXPORT)
		ft_export(argv, shell);
	else if (built_in == B_PWD)
		ft_pwd(argv, shell);
	else if (built_in == B_UNSET)
		ft_unset(argv, shell);
	return (shell->err->exec_built_in = 0);
}

//This function creates the PATH possibilities array for the PATH env variable
int	ft_pathseter(t_envar *envc, t_shell *shell)
{
	t_envar	*path;

	if (!envc)
		return (-1);
	path = ft_get_envar(envc, "PATH", shell->err);
	if (!path)
		return (shell->err->pathseter = 1);
	shell->path_arr = ft_split(path->value, ':');
	return (shell->err->pathseter = 0);
}

//A funciton that looks for the program in every path and returns the path
//in which it found it, or NULL if it didn't find any path to the program
char	*ft_pathfinder(char *command, t_shell *shell)
{
	size_t	index;
	char	*path;
	char	*temp;

	if (!command || !shell->path_arr || !*(shell->path_arr))
		return (NULL);
	index = 0;
	path = NULL;
	temp = NULL;
	while (shell->path_arr[index])
	{
		temp = ft_strjoin("/", command);
		path = ft_strjoin(shell->path_arr[index], temp);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		index++;
	}
	shell->err->pathfinder = 0;
	return (NULL);
}

//This function will either execute the built in or call execve looking for
//external program passed in argv
//execve will send a SIGTRAP SIGNAL??
int	ft_exec_cmd(t_pipe *pipe, t_shell *shell, t_error *err, int pipefd)
{
	char	**argv_r;
	char	*cmd;
	char	*path;

	if (!pipe || !pipe->command || !shell || !pipe->command->argv)
		return (err->exec_cmd = 1);
	argv_r = pipe->command->argv;
	cmd = argv_r[0];
	ft_pathseter(shell->envc, shell);
	if (ft_built_in_check(cmd, err) != B_NONE)
	{
		ft_exec_built_in(ft_built_in_check(cmd, err), shell, argv_r, pipe);
		close(pipefd);
	}
	else
	{
		if (pipe->next)
			close(pipefd);
		path = ft_pathfinder(cmd, shell);
		if (path != NULL)
			execve(path, argv_r, shell->envp);
		perror("Error: INVALID COMMAND\n");
	}
	ft_exit(shell->pipeline, shell);
	return (err->exec_cmd = 0);
}
