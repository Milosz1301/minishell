/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:31:19 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 19:08:16 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function handles the redirections in write word
int	ft_ww_redir(char **s)
{
	if (!s || !*s)
		return (-1);
	if (**s == '>')
	{
		while (**s && **s == '>')
			(*s)++;
	}
	else if (**s == '<')
	{
		while (**s && **s == '<')
			(*s)++;
	}
	return (0);
}

void	ft_inquote(char c, int *s_quote, int *d_quote)
{
	if (c == '\'')
	{
		if (*s_quote)
			*s_quote = 0;
		else
			*s_quote = 1;
	}
	else if (c == '"')
	{
		if (*d_quote)
			*d_quote = 0;
		else
			*d_quote = 1;
	}
	else
		return ;
}

//Word amount had a bug with redirections not being accounted for 
//both possible forms (form1 : >>append form2: >> append)
//in_arr[0] = in_word, in_arr[1] = in_squote, in_arr[2] = in_dquote
size_t	ft_word_amount(char *s, char c, t_error *err)
{
	size_t	words;
	int		in_arr[3];

	ft_wa_init(&words, in_arr);
	while (*s)
	{
		if (*s == '"' || *s == '\'')
			ft_inquote(*s, &in_arr[1], &in_arr[2]);
		else if (*s == c && !(in_arr[1] || in_arr[2]))
			in_arr[0] = 0;
		else if (*s == '>' || *s == '<')
		{
			ft_ww_redir(&s);
			words++;
			continue ;
		}
		else if (*s == '|')
			ft_wa_pipe(&s, &words);
		else if (*s != c && in_arr[0] == 0)
			ft_wa_handle_word(in_arr, &words, s);
		s++;
	}
	if (in_arr[1] || in_arr[2])
		return (err->word_amount = 1);
	return (words);
}

char	**ft_split_mini(char *s, char c, t_error *err)
{
	char		**str_arr;

	if (!s || *s == '\0')
	{
		str_arr = malloc(1 * sizeof(char *));
		str_arr[0] = NULL;
		return (str_arr);
	}
	str_arr = malloc((ft_word_amount(s, c, err) + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	if (!ft_split_logic(str_arr, s, c))
	{
		free(str_arr);
		return (NULL);
	}
	return (str_arr);
}
