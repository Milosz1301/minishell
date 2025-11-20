/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:23:09 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:24:32 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Redirections need to happen before execution and in a CHILD proccess
//So executor must fork a new process if a redirection or a pipe is detected
//
//We need a function that will plug and replug the redirections based on the 
//redirection chain
static int	ft_handle_redir(t_redirect *red_chain, t_shell *shell, t_error *err)
{
	if (!red_chain || !shell || red_chain->type == RE_NONE)
		return (err->handle_redir = 1);
	if (red_chain->type == RE_IN)
		ft_infile(red_chain->target, err);
	else if (red_chain->type == RE_OUT)
		ft_outfile(red_chain->target, err);
	else if (red_chain->type == RE_APPEND)
		ft_append(red_chain->target, err);
	else if (red_chain->type == RE_HEREDOC)
	{
		dup2(red_chain->here_fd, STDIN_FILENO);
		close(red_chain->here_fd);
	}
	return (err->handle_redir = 0);
}

//Main redirection handling function
int	ft_redirector(t_redirect *red_chain, t_shell *shell, t_error *err)
{
	t_redirect	*ref;

	if (!red_chain || !shell)
		return (err->redirector = 1);
	ref = red_chain;
	while (ref)
	{
		ft_handle_redir(ref, shell, err);
		ref = ref->next;
	}
	return (err->redirector = 0);
}
