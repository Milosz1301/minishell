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

//A function that deletes the specififed token from the chain
int	ft_del_token(t_token **chain, t_token *token, t_error *err)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*temp;

	if (!chain || !token)
		return (err->del_token = 1);
	cur = (*chain);
	if (!cur)
		return (err->del_token = 0);
	prev = NULL;
	while (cur && cur != token)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return (err->del_token = 1);
	temp = cur->next;
	ft_del_string(cur->string);
	free(cur);
	if (!prev)
		(*chain) = temp;
	else
		prev->next = temp;
	return (err->del_token = 0);
}

//A function that deletes a token chain;
int	ft_del_token_chain(t_token **chain, t_error *err)
{
	t_token	**ref;
	t_token	*temp;

	if (!chain)
		return (err->del_token_chain = 1);
	ref = chain;
	temp = NULL;
	if (!(*ref))
		return (err->del_token_chain = 0);
	while (*ref != NULL)
	{
		temp = (*ref)->next;
		ft_del_string((*ref)->string);
		free(*ref);
		*ref = temp;
	}
	return (err->del_token_chain = 0);
}

//A function that deletes a redirection chain;
int	ft_del_redir_chain(t_redirect **red_chain, t_error *err)
{
	t_redirect	**ref;
	t_redirect	*temp;

	if (!red_chain)
		return (err->del_redir_chain = 1);
	ref = red_chain;
	temp = NULL;
	if (!(*ref))
		return (err->del_redir_chain = 0);
	while (*ref != NULL)
	{
		temp = (*ref)->next;
		ft_del_string((*ref)->target);
		if ((*ref)->here_fd >= 0)
			close((*ref)->here_fd);
		free(*ref);
		*ref = temp;
	}
	*red_chain = NULL;
	return (err->del_redir_chain = 0);
}

//A function to delete a cmd struct
int	ft_del_cmd(t_cmd **command, t_error *err)
{
	char	**ref;
	int		i;

	if (!command)
		return (err->del_cmd = 1);
	ref = NULL;
	i = 0;
	if ((*command) && (*command)->argv)
	{
		ref = (*command)->argv;
		while (ref[i])
		{
			ft_del_string(ref[i]);
			i++;
		}
		free(ref);
	}
	if ((*command)->red_chain)
		ft_del_redir_chain(&((*command)->red_chain), err);
	ft_del_token_chain(&((*command)->cmd_chain), err);
	if (err->del_token_chain == 1 || err->del_redir_chain == 1)
		return (err->del_cmd = 1);
	free (*command);
	*command = NULL;
	return (err->del_cmd = 0);
}

//A function that deletes a pipeline
int	ft_del_pipeline(t_pipe **pipeline, t_error *err)
{
	t_pipe	**ref;
	t_pipe	*temp;

	if (!pipeline)
		return (err->del_pipeline = 1);
	ref = pipeline;
	temp = NULL;
	if (!(*ref))
		return (err->del_pipeline = 0);
	while (*ref != NULL)
	{
		temp = (*ref)->next;
		if ((*ref)->command)
			ft_del_cmd(&((*ref)->command), err);
		free(*ref);
		*ref = temp;
	}
	*pipeline = NULL;
	return (err->del_pipeline = 0);
}
