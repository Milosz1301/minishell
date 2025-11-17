/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:37:10 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/01 18:37:11 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//A functon that returns the redirection type (checking +1 len in case of >>>)
//This doesnt work in any case, all input will be assigned as valid redirection
//Can I have and empty redirection filename?
// >>>asd >> asgfas >>asfdahsd >>
//FIXED!!!! Everything handled correctly
static t_redir_type	ft_get_redir_type(char *string)
{
	if (!ft_strncmp(string, ">>", 3))
		return (RE_APPEND);
	if (!ft_strncmp(string, "<<", 3))
		return (RE_HEREDOC);
	if (!ft_strncmp(string, ">", 2))
		return (RE_OUT);
	if (!ft_strncmp(string, "<", 2))
		return (RE_IN);
	return (RE_NONE);
}

//A function that extracts the redirections from the cmd_chain
//What about empty redirections or redirections that have the 
//target in their token
t_redirect	*ft_get_red_chain(t_token *cmd_chain, t_error *err)
{
	t_redirect		*red_chain;
	t_token			*cur;
	t_redir_type	r_type;

	if (!cmd_chain)
		return (NULL);
	red_chain = NULL;
	cur = cmd_chain;
	while (cur && cur->type != T_END)
	{
		if (cur->type == T_REDIR)
		{
			if (cur->next->type != T_WORD)
			{
				err->get_red_chain = 1;
				return (NULL);
			}
			r_type = ft_get_redir_type(cur->string);
			ft_add_redir(&red_chain, ft_new_redir(r_type, cur->next->string,
					cur->next->q_type));
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (red_chain);
}

//I need a function to purify the cmd_chain from redirections and the filenames
int	ft_purify_cmd_chain(t_token **cmd_chain, t_error *err)
{
	t_token	*target;
	t_token	*temp;

	if (!cmd_chain)
		return (err->purify_cmd_chain = 1);
	if (!(*cmd_chain))
		return (err->purify_cmd_chain = 0);
	target = *cmd_chain;
	while (target && target->type != T_END)
	{
		if (target->type == T_REDIR)
		{
			if (!target->next)
				return (err->purify_cmd_chain = 1);
			temp = target->next->next;
			ft_del_token(cmd_chain, target->next, err);
			ft_del_token(cmd_chain, target, err);
			target = temp;
		}
		else
			target = target->next;
	}
	return (err->purify_cmd_chain = 0);
}

//Helper function to extract the command chain from the token chain
t_token	*ft_get_cmd_chain(t_token **chain, t_error *err)
{
	t_token	*temp;
	t_token	*cmd_chain;

	if (!chain)
	{
		err->get_cmd_chain = 1;
		return (NULL);
	}
	temp = NULL;
	cmd_chain = *chain;
	while ((*chain))
	{
		if ((*chain)->type == T_PIPE_OP)
		{
			temp = (*chain)->next;
			(*chain)->type = T_END;
			(*chain)->next = NULL;
			*chain = temp;
			break ;
		}
		*chain = (*chain)->next;
	}
	err->get_cmd_chain = 0;
	return (cmd_chain);
}

//A function that checks if the token chain is invalid
int	ft_check_token_chain(t_token *chain, t_error *err)
{
	t_token	*cur;

	if (!chain || chain->type == T_PIPE_OP)
		return (err->check_token_chain = 1);
	cur = chain;
	while (cur != NULL)
	{
		if (cur->type == T_NONE)
			return (err->check_token_chain = 1);
		if (cur->type == T_PIPE_OP)
		{
			if (!(cur->next))
				return (err->check_token_chain = 1);
			if (cur->next->type != T_WORD && cur->next->type != T_REDIR)
				return (err->check_token_chain = 1);
		}
		if (cur->type == T_REDIR
			&& (!(cur->next) || cur->next->type != T_WORD))
			return (err->check_token_chain = 1);
		cur = cur->next;
	}
	return (err->check_token_chain = 0);
}
