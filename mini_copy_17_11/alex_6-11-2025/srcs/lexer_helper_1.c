/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:32:29 by mstawski          #+#    #+#             */
/*   Updated: 2025/10/09 14:23:44 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function checks whether the string of token has squotes
bool	ft_squote_check(char **s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			quote++;
		i++;
	}
	if (!quote)
		return (false);
	else if (quote % 2 == 0)
		return (true);
	else
		return (false);
}

//This function checks whether the string of token has dquotes
bool	ft_dquote_check(char **s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '"')
			quote++;
		i++;
	}
	if (!quote)
		return (false);
	else if (quote % 2 == 0)
		return (true);
	else
		return (false);
}

//This function sets correct qtype of the token
t_quote_type	ft_set_qtype(char *str)
{
	if (ft_dquote_check(&str) && ft_squote_check(&str))
		return (Q_BOTH);
	else if (ft_dquote_check(&str))
		return (Q_DOUBLE);
	else if (ft_squote_check(&str))
		return (Q_SINGLE);
	else
		return (Q_NONE);
}

//This function sets correct token type of the token
//what about this input: >>file >file ?
//This will return a T_REDIR and a whole token?
// we want to split the >>file to ">>" and "file"
t_token_type	ft_set_token_type(char *string)
{
	if (!string)
		return (T_END);
	else if (!ft_strncmp(string, ">", 1))
		return (T_REDIR);
	else if (!ft_strncmp(string, "<", 1))
		return (T_REDIR);
	else if (!ft_strncmp(string, "|", 1))
		return (T_PIPE_OP);
	else
		return (T_WORD);
}

//This function creates the chain of tokens 
void	ft_create_chain(t_token **chain, char **input_arr)
{
	int	i;

	if (!chain)
		return ;
	i = 0;
	while (input_arr[i])
	{
		ft_add_token(chain, ft_new_token(ft_set_token_type(input_arr[i]),
				input_arr[i], ft_set_qtype(input_arr[i])));
		ft_del_string(input_arr[i]);
		i++;
	}
	free(input_arr);
	ft_add_token(chain, ft_new_token(ft_set_token_type(NULL),
			"", ft_set_qtype("Q_NONE")));
}
