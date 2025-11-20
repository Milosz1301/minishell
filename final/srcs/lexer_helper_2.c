/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:31:19 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 20:23:09 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_dquote_scope(char **s)
{
	(*s)++;
	while (**s && **s != '"')
		(*s)++;
}

static void	ft_squote_scope(char **s)
{
	(*s)++;
	while (**s && **s != '\'')
		(*s)++;
}

//This function handles the quotes in write word
int	ft_handle_quotes(char **s)
{
	if (!s || !*s)
		return (-1);
	if (**s == '"')
		ft_dquote_scope(s);
	else if (**s == '\'')
		ft_squote_scope(s);
	return (0);
}

//Added redirection case where it will always treat redirections
//and the target as different tokens
//Also fixed a small bug for starting or trailing spaces (check)
static char	*ft_write_word(char **s, char c)
{
	char const	*start;
	char		*word;

	start = *s;
	while (**s)
	{
		if (**s == '"' || **s == '\'')
			ft_handle_quotes(s);
		else if (**s == '>' || **s == '<')
		{
			ft_ww_redir(s);
			break ;
		}
		else if (**s == c || **s == '|')
			break ;
		(*s)++;
	}
	word = malloc((*s - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, *s - start + 1);
	return (word);
}

//(Check)
int	ft_split_logic(char **str_arr, char *s, char c)
{
	size_t		index;
	int			quote;

	index = 0;
	quote = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (*s == '|')
			{
				str_arr[index] = ft_strdup("|");
				s++;
			}
			else
				str_arr[index] = ft_write_word(&s, c);
			if (!str_arr[index])
				return (ft_freearr(str_arr, index));
			index++;
		}
	}
	str_arr[index] = NULL;
	return (1);
}

/*int	main(int argc, char *argv[])
{
	char	**array;
	int	i;

	array = ft_split_mini(argv[1], ' ');
	i = -1;
	while (array[++i])
		printf("ARRAY[%i]: %s\n",i , array[i]);
}*/
