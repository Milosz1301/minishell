/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 20:07:54 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/09 20:07:57 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Helper function for the ft_expand_dollar function, that returns the amount
//of character the expansion target has
static size_t	ft_varlen(char *start, int *in_braces, t_error *err)
{
	char	*end;
	size_t	result;

	end = start;
	while (*end && ft_isenvchar(*end) == 1)
		end++;
	result = 0;
	if (*end == '}')
		return ((size_t)(end - start));
	if ((!*end && *in_braces == 1) || end == start
		|| ((*in_braces == 1) && ft_isenvchar(*end) == 0))
	{
		err->env_len = 1;
		return (0);
	}
	err->env_len = 0;
	return ((size_t)(end - start));
}

//A give back the starting address for the expansion
static char	*ft_get_start(char *dollar, int *in_braces, t_error *err)
{
	char	*start;

	start = dollar + 1;
	if (ft_isdigit(*start) == 1 || start == NULL)
	{
		err->get_start = 1;
		return (NULL);
	}
	if (*start == '{')
	{
		*in_braces = 1;
		start++;
	}
	return (start);
}

//A function that sets the result char * of the expanding the $ sign
static char	*ft_get_result(char *start, t_shell *shell,
								int in_braces, t_error *err)
{
	char	*target;
	char	*result;
	char	*env;
	size_t	start_index;

	if (!start || !shell)
		return (NULL);
	env = NULL;
	if (*start == '?')
		ft_handle_qumark(&target, &result, start, shell);
	else
	{
		target = ft_calloc(ft_varlen(start, &in_braces, err) + 1, sizeof(char));
		ft_strlcpy(target, start, ft_varlen(start, &in_braces, err) + 1);
		env = ft_get_envar(shell->envc, target, err)->value;
		start_index = ft_varlen(start, &in_braces, err);
		if (in_braces == 1)
			start_index++;
		if (!env)
			result = ft_strjoin("", &start[start_index]);
		else
			result = ft_strjoin(env, &start[start_index]);
		free(target);
	}
	return (result);
}

//A function that returns a pointer to the first $ that can be expanded
char	*ft_get_dollar(char *str, t_error *err)
{
	int	in_squote;

	if (!str)
	{
		err->get_dollar = 1;
		return (NULL);
	}
	in_squote = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (in_squote == 0)
				in_squote = 1;
			else
				in_squote = 0;
		}
		if (*str == '$' && in_squote == 0)
			return (str);
		else
			str++;
	}
	return (NULL);
}

//A function that exapands the content of a dollar inside a string
int	ft_expand_dollar(char **str, char *dollar, t_shell *shell, t_error *err)
{
	char	*start;
	char	*result;
	char	*temp;
	char	*end;
	int		in_braces;

	if (!str)
		return (err->expand_dollar = 1);
	if (!*str || !dollar)
		return (err->expand_dollar = 0);
	in_braces = 0;
	start = ft_get_start(dollar, &in_braces, err);
	if (!start)
		return (err->expand_dollar = 1);
	temp = ft_substr(*str, 0, dollar - *str);
	end = ft_get_result(start, shell, in_braces, err);
	result = ft_strjoin(temp, end);
	free(temp);
	free(end);
	free(*str);
	*str = result;
	return (err->expand_dollar = 0);
}
