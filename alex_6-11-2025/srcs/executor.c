/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:23:09 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/02 14:23:10 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//A function that will return 1 if we have pipes or redirections
//If it returns 1 we have to fork. If it returns 0 we can execute on the parent
//proccess (the minishell) directly
//if it returns -1 we have error
static int	ft_forking_check(t_pipe *pipeline, t_shell *shell, t_error *err)
{
	if (!pipeline || !shell)
		return (err->forking_check = -1);
	if (pipeline->next != NULL)
		return (1);
	if (pipeline->command->red_chain != NULL)
		return (1);
	if (ft_check_for_built_in((pipeline->command->argv)[0], err) == B_NONE)
		return (1);
	return (err->forking_check = 0);
}

//A function that will run on parent the built-in
int	ft_run_first_built_in(t_pipe *pipe, int *is_first_pipe, t_shell *shell)
{
	int			saved_fdin;
	int			saved_fdout;
	t_built_in	b_type;

	if (!pipe)
		return (shell->err->run_first_built_in = 0);
	saved_fdin = dup(STDIN_FILENO);
	saved_fdout = dup(STDOUT_FILENO);
	*is_first_pipe = 0;
	b_type = ft_check_for_built_in(pipe->command->argv[0], shell->err);
	if (pipe->command->red_chain != NULL)
		ft_redirector(pipe->command->red_chain, shell, shell->err);
	ft_exec_built_in(b_type, shell, pipe->command->argv, pipe);
	dup2(STDIN_FILENO, saved_fdin);
	dup2(STDOUT_FILENO,saved_fdout);
	return (0);
}

//A function to run in the child process
static int	ft_run_in_child(t_pipe *pipe, t_shell *shell, int pipefd[],
				int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pipe->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (pipe->command->red_chain != NULL)
		ft_redirector(pipe->command->red_chain, shell, shell->err);
	ft_exec_cmd(pipe, shell, shell->err);
	return (shell->err->run_in_child = 0);
}

//Helper function to run in the parent process
static int	ft_run_in_parent(t_pipe *pipe, int pipefd[], int *prev_fd)
{
	if (*prev_fd != -1)
		close (*prev_fd);
	if (pipe->next != NULL)
	{
		*prev_fd = pipefd[0];
		close(pipefd[1]);
	}
	return (0);
}

//Helper function to refresh the prompt after the execution of a command
void	ft_refresh_rl(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//The whole process of the executor will be like this:
//	1)Check if there is a second pipe or a Redirection
//	2)If yes, then fork a child process and do in order:
//		a)Set the redirections up FIRST
//		b)Set the pipeline (stdout to next pipe's stdin)
//		c)Execute the command (built-in or external, doesn't matter)
//	3)If not, then you check if the command given is a built-in
//		a)If it is a built-in, execute immediately on the parent proccess
//		b)If it is an external command, fork a child process, look for the 
//			command in the path and if you find it then execute the command
//	4)Main proccess should wait for the child processes to finish first
int	ft_executor(t_pipe  *pipeline, t_shell *shell, t_error *err)
{
	pid_t	pid;
	int		is_first_pipe;
	int		pipefd[2];
	int		prev_fd;
	int		wstatus;

	if (!pipeline || !shell)
		return (err->executor = 1);
	pid = -1;
	prev_fd = -1;
	is_first_pipe = 1;
	while (pipeline)
	{
		if (is_first_pipe && ft_check_for_built_in(pipeline->command->argv[0], err))
			ft_run_first_built_in(pipeline, &is_first_pipe, shell);
		if (pipeline->next)
			pipe(pipefd);
		if (ft_forking_check(pipeline, shell, err) == 1)
			pid = fork();
		if (pid == 0)
			ft_run_in_child(pipeline, shell, pipefd, prev_fd);
		else
			ft_run_in_parent(pipeline, pipefd, &prev_fd);
		pipeline = pipeline->next;
	}
	waitpid(-1, &wstatus, 0);
	return (err->executor = 0);
}
