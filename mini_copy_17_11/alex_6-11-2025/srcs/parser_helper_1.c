/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:51:30 by akonstan          #+#    #+#             */
/*   Updated: 2025/09/28 15:51:36 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//In every case we pass the **token is because we will alter the head
//or/and the values inside the token chain (token list)
//
//A function that counts the amount of tokens a pipe has
size_t	ft_pipelen(t_token *chain)
{
	size_t	token_amount;

	if (!chain)
		return (0);
	token_amount = 0;
	while (chain->type != T_PIPE_OP && chain->type != T_END)
	{
		token_amount++;
		chain = chain->next;
	}
	return (token_amount);
}

//A function that returns a pointer to the last pipe in the pipeline
t_pipe	*ft_get_last_pipe(t_pipe *pipeline, t_error *err)
{
	if (!pipeline)
	{
		err->get_last_pipe = 1;
		return (NULL);
	}
	while (pipeline->next != NULL)
		pipeline = pipeline->next;
	return (pipeline);
}

//A function that initializes a pipe
t_pipe	*ft_new_pipe(t_token **chain, t_error *err)
{
	t_pipe	*pipe;

	if (!chain)
	{
		err->new_pipe = 1;
		return (NULL);
	}
	pipe = ft_calloc(1, sizeof(t_pipe));
	pipe->command = ft_calloc(1, sizeof(t_cmd));
	pipe->command->cmd_chain = ft_get_cmd_chain(chain, err);
	pipe->cmd_amount = ft_chainlen(pipe->command->cmd_chain);
	pipe->command->red_chain = ft_get_red_chain(pipe->command->cmd_chain, err);
	ft_purify_cmd_chain(&(pipe->command->cmd_chain), err);
	pipe->next = NULL;
	return (pipe);
}

//A function that adds a new pipe to the pipeline
int	ft_add_pipe(t_pipe **pipeline, t_token **chain, t_error *err)
{
	if (!pipeline || !chain)
		return (err->add_pipe = 1);
	if (!(*chain))
		return (err->add_pipe = 0);
	if (!(*pipeline))
		*pipeline = ft_new_pipe(chain, err);
	else
		(ft_get_last_pipe(*pipeline, err))->next = ft_new_pipe(chain, err);
	return (err->add_pipe = 0);
}
