/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:55:51 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/20 20:48:49 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wa_handle_word(int in_arr[], size_t *words, char *s)
{
	in_arr[0] = 1;
	(*words)++;
	if (!in_arr[1] && *s == '"')
		ft_inquote(*s, &in_arr[1], &in_arr[2]);
	else if (!in_arr[2] && *s == '\'')
		ft_inquote(*s, &in_arr[1], &in_arr[2]);
}

int	ft_wa_pipe(char **s, size_t *words)
{
	if (!s || !*s)
		return (1);
	if (!**s || !*(*s - 1) || !*(*s + 1))
		return (1);
	if (*(*s - 1) != ' ' || *(*s + 1) != ' ')
	{
		if (*(*s - 1) != ' ')
			(*words)++;
		if (*(*s + 1) != ' ')
			(*words)++;
	}
	else
		(*words)++;
	return (0);
}

void	ft_wa_init(size_t *words, int in_arr[3])
{
	*words = 0;
	in_arr[0] = 0;
	in_arr[1] = 0;
	in_arr[2] = 0;
}
