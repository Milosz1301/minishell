/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:48:18 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/20 21:48:21 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//Function will handle redirections and keep the heredoc file descriptors
//in the redirections structure
int	ft_get_heredocs(t_pipe *pipeline, t_shell *shell)
{
	t_redirect	*ref;

	if (!pipeline || !pipeline->command || !shell)
		return (-1);
	ref = NULL;
	while (pipeline)
	{
		ref = pipeline->command->red_chain;
		while (ref)
		{
			ref->here_fd = -1;
			if (ref->type == RE_HEREDOC)
				ref->here_fd = ft_heredoc(ref->target, ref->q_type, shell);
			ref = ref->next;
		}
		pipeline = pipeline->next;
	}
	return (0);
}

//A function to run in the child process
//Helper function to refresh the prompt after the execution of a command
void	ft_refresh_rl(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ft_exec_init(pid_t *pid, int *prevfd, t_shell *shell, t_pipe *pipeline)
{
	*pid = -1;
	*prevfd = -1;
	ft_get_heredocs(pipeline, shell);
}
