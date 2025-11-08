/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:01:39 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/01 17:01:41 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This file has redirection chain manipulation functions
//
//Creates a new redirection of type and target
t_redirect	*ft_new_redir(t_redir_type type, char *target, t_quote_type q_type)
{
	t_redirect	*red_chain;

	red_chain = ft_calloc(1, sizeof(t_redirect));
	red_chain->type = type;
	red_chain->target = ft_strdup(target);
	red_chain->q_type = q_type;
	red_chain->next = NULL;
	return (red_chain);
}

//Returns the last node on the red_chain
t_redirect	*ft_get_last_redir(t_redirect *red_chain)
{
	if (!red_chain)
		return (NULL);
	while (red_chain->next != NULL)
		red_chain = red_chain->next;
	return (red_chain);
}

//Append redirection to the redirection chain
void	ft_add_redir(t_redirect **red_chain, t_redirect *redirect)
{
	if (!red_chain)
		return ;
	if (!(*red_chain))
		(*red_chain) = redirect;
	else
		(ft_get_last_redir(*red_chain))->next = redirect;
}

//Get the length of the redirection
size_t	ft_redirlen(t_redirect *red_chain)
{
	size_t	res;

	if (!red_chain)
		return (0);
	res = 0;
	while (red_chain)
	{
		res++;
		red_chain = red_chain->next;
	}
	return (res);
}
