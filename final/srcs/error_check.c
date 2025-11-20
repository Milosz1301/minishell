/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:11:48 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/10 20:11:50 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function will return 1 if there is ANY error in the parser, parser
//helper and parser helper 2 functions. If they are clear then returns 0
//excluding the ft_parser
int	ft_error_check_parser(t_error *err)
{
	if (err->get_last_pipe == 1)
		return (1);
	if (err->new_pipe == 1)
		return (1);
	if (err->add_pipe == 1)
		return (1);
	if (err->get_red_chain == 1)
		return (1);
	if (err->purify_cmd_chain == 1)
		return (1);
	if (err->get_cmd_chain == 1)
		return (1);
	if (err->check_token_chain == 1)
		return (1);
	return (0);
}

//Similar to the last one, returns 1 if any expander functions have errors
//excluding the ft_expander
int	ft_error_check_expander(t_error *err)
{
	if (err->expand_str == 1)
		return (1);
	if (err->expand_redir == 1)
		return (1);
	if (err->expand_cmd == 1)
		return (1);
	if (err->get_start == 1)
		return (1);
	if (err->get_dollar == 1)
		return (1);
	if (err->expand_dollar == 1)
		return (1);
	if (err->expand_str == 1)
		return (1);
	if (err->expand_redir == 1)
		return (1);
	if (err->expand_cmd == 1)
		return (1);
	if (err->rmquotes == 1)
		return (1);
	if (err->set_cmd_argv == 1)
		return (1);
	return (0);
}
