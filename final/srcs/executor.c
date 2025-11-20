/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:23:09 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 21:50:43 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//A function that will return 1 if we have pipes or redirections
//If it returns 1 we have to fork. If it returns 0 we can execute on the parent
//proccess (the minishell) directly
//if it returns -1 we have error
int	ft_forking_check(t_pipe *pipeline, t_shell *shell, t_error *err)
{
	if (!pipeline || !shell)
		return (err->forking_check = -1);
	if (pipeline->next != NULL)
		return (1);
	if (pipeline->command->red_chain != NULL)
		return (1);
	if (ft_built_in_check((pipeline->command->argv)[0], err) == B_NONE)
		return (1);
	return (err->forking_check = 0);
}

//A function that will run on parent the built-in
int	ft_run_first_built_in(t_pipe **pipe, t_shell *shell)
{
	int			saved_fdin;
	int			saved_fdout;
	t_built_in	b_type;

	if (!*pipe)
		return (shell->err->run_first_built_in = 0);
	saved_fdin = dup(STDIN_FILENO);
	saved_fdout = dup(STDOUT_FILENO);
	b_type = ft_built_in_check((*pipe)->command->argv[0], shell->err);
	if ((*pipe)->command->red_chain != NULL)
		ft_redirector((*pipe)->command->red_chain, shell, shell->err);
	ft_exec_built_in(b_type, shell, (*pipe)->command->argv, *pipe);
	dup2(saved_fdin, STDIN_FILENO);
	dup2(saved_fdout, STDOUT_FILENO);
	close(saved_fdin);
	close(saved_fdout);
	*pipe = (*pipe)->next;
	return (0);
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
int	ft_executor(t_pipe *pipeline, t_shell *shell, t_error *err)
{
	pid_t	pid;
	int		pipefd[2];
	int		prev_fd;
	int		fork_check;

	ft_exec_init(&pid, &prev_fd, shell, pipeline);
	if (!pipeline->next && ft_built_in_check(pipeline->command->argv[0], err))
		ft_run_first_built_in(&pipeline, shell);
	fork_check = ft_forking_check(pipeline, shell, err);
	while (pipeline)
	{
		if (pipeline->next)
			pipe(pipefd);
		pid = -1;
		if (fork_check == 1)
			pid = fork();
		if (pid == 0)
			ft_run_in_child(pipeline, shell, pipefd, prev_fd);
		else
			ft_run_in_parent(pipeline, pipefd, &prev_fd);
		pipeline = pipeline->next;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (err->executor = 0);
}

int	ft_run_in_child(t_pipe *pipe, t_shell *shell, int pipefd[],
				int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pipe->command->red_chain != NULL)
		ft_redirector(pipe->command->red_chain, shell, shell->err);
	if (pipe->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	ft_exec_cmd(pipe, shell, shell->err, pipefd[0]);
	exit(0);
	return (0);
}

//Helper function to run in the parent process
int	ft_run_in_parent(t_pipe *pipe, int pipefd[], int *prev_fd)
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
