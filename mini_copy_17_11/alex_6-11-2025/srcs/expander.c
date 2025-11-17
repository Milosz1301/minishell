/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:23:36 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/07 16:23:37 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//A function that expands all $ in  a given string
int	ft_expand_str(char **str, t_shell *shell, t_error *err)
{
	if (!str)
		return (err->expand_str = 1);
	while (ft_get_dollar(*str, err) != NULL)
		ft_expand_dollar(str, ft_get_dollar(*str, err), shell, err);
	return (err->expand_str = 0);
}

//A function that expands all strings in the given redirection chain
static int	ft_expand_redir(t_redirect *red_chain, t_shell *shell, t_error *err)
{
	if (!red_chain)
		return (err->expand_redir = 1);
	while (red_chain)
	{
		ft_expand_str(&(red_chain->target), shell, err);
		red_chain = red_chain->next;
	}
	return (err->expand_redir = 0);
}

//A function that expands all strings in the given command chain
static int	ft_expand_cmd(t_token *cmd_chain, t_shell *shell, t_error *err)
{
	if (!cmd_chain)
		return (err->expand_cmd = 1);
	while (cmd_chain)
	{
		ft_expand_str(&(cmd_chain->string), shell, err);
		ft_rmquotes(&(cmd_chain->string), err);
		cmd_chain = cmd_chain->next;
	}
	return (err->expand_cmd = 0);
}

//This function will get inside the pipeline and expand on all the variables 
//that need to be expanded
//It only needs to handle $word , $? ,${word}line 
int	ft_expander(t_pipe *pipeline, t_shell *shell, t_error *err)
{
	t_token		*cmd_chain;
	t_redirect	*red_chain;

	if (!pipeline)
		return (err->expander = 1);
	while (pipeline != NULL)
	{
		cmd_chain = pipeline->command->cmd_chain;
		red_chain = pipeline->command->red_chain;
		ft_expand_cmd(cmd_chain, shell, err);
		ft_expand_redir(red_chain, shell, err);
		ft_set_cmd_argv(pipeline, shell, err);
		pipeline = pipeline->next;
	}
	return (err->expander = 0);
}
