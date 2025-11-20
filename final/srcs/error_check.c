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

int	ft_error_check_lexer(t_error *err)
{
	if (err->word_amount == 1)
		perror("Error: INPUT ERROR\n");
	return (err->word_amount);
}

//This function will return 1 if there is ANY error in the parser, parser
//helper and parser helper 2 functions. If they are clear then returns 0
//excluding the ft_parser
int	ft_error_check_parser(t_error *err)
{
	int	res;

	res = 0;
	if (err->get_last_pipe != 0 || err->new_pipe != 0 || err->add_pipe != 0)
		res = 1;
	if (err->get_red_chain != 0 || err->purify_cmd_chain != 0)
		res = 1;
	if (err->get_cmd_chain == 1 || err->check_token_chain == 1)
		res = 1;
	if (res != 0)
		perror("Error: INVALID SYNATAX\n");
	return (res);
}

//Similar to the last one, returns 1 if any expander functions have errors
//excluding the ft_expander
int	ft_error_check_expander(t_error *err)
{
	int	res;

	res = 0;
	if (err->expand_str == 1 || err->expand_redir == 1 || err->expand_cmd == 1)
		res = 1;
	if (err->get_start == 1 || err->get_dollar == 1 || err->expand_dollar == 1)
		res = 1;
	if (err->expand_str == 1 || err->env_len == 1)
		res = 1;
	if (err->expand_redir == 1)
		res = 1;
	if (err->expand_cmd == 1)
		res = 1;
	if (err->rmquotes == 1)
		res = 1;
	if (err->set_cmd_argv == 1)
		res = 1;
	if (res != 0)
		perror("Error: EXPANSION ERROR\n");
	return (res);
}

int	ft_error_handle_env(t_error *err)
{
	int	res;

	res = 0;
	if (err->get_last_envar == 1 || err->new_envar == 1 || err->add_envar == 1)
		res = 1;
	if (err->del_envar == 1 || err->get_envar == 1 || err->set_envp == 1)
		res = 1;
	if (err->set_envc == 1 || err->extract_value == 1 || err->extract_key == 1)
		res = 1;
	if (err->valid_env != 0 || err->envar_amount != 0)
		res = 1;
	if (res != 0)
		perror("Error: ENV ERROR\n");
	return (res);
}

int	ft_error_check_redirections(t_error *err)
{
	int	res;

	res = 0;
	if (err->check_file_access != 0 || err->append != 0 || err->infile != 0)
		res = 1;
	if (err->outfile != 0 || err->handle_redir != 0 || err->redirector != 0)
		res = 1;
	if (res != 0)
		perror("Error: REDIRECTION ERROR\n");
	return (res);
}
