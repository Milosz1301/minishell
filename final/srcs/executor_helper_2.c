/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:04:49 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/20 19:07:30 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

static int	ft_run_in_child(t_pipe *pipe, t_shell *shell, int pipefd[],
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
