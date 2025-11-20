/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:51:04 by akonstan          #+#    #+#             */
/*   Updated: 2025/09/29 16:51:06 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This file will have tokens list handling functions
//
//This function will create a token on the list of the specified type
//And with the specified string text.
//All content is set to null (twice for the next node pointer, just in case)
t_token	*ft_new_token(t_token_type type, char *str, t_quote_type q_type)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->string = ft_strdup(str);
	token->q_type = q_type;
	token->next = NULL;
	return (token);
}

//This function will return the last token in the token chain
t_token	*ft_get_last_token(t_token *chain)
{
	if (!chain)
		return (NULL);
	while (chain->next != NULL)
		chain = chain->next;
	return (chain);
}

//This function will append a new token of specified type and string
//to the token chain
void	ft_add_token(t_token **chain, t_token *token)
{
	if (!chain)
		return ;
	if (!(*chain))
		*chain = token;
	else
		ft_get_last_token((*chain))->next = token;
}

//This function will give you the length of the token chain
size_t	ft_chainlen(t_token *chain)
{
	size_t	res;

	if (!chain)
		return (0);
	res = 0;
	while (chain && chain->type != T_END)
	{
		res++;
		chain = chain->next;
	}
	return (res);
}
