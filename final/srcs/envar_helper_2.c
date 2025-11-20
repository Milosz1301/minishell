/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:27:40 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//we will use the 3 argument form of int main(argc, argv, envc)
//envc is a pointer to the environment variable array from the system
//We need to create our own copy of this array in the form of a linked list
//is_exported will always be set to 1 in our minishell because we will only
//be adding env variables using export. It will still be added as a flag to
//keep it accurate and close to the bash version of the export function
//
//A helper function for set_envp
static void	ft_assign_envp(t_envar *envc, char ***envp)
{
	char	**ref;
	char	*key;
	char	*value;

	ref = *envp;
	key = NULL;
	value = NULL;
	while (envc)
	{
		key = ft_strjoin(envc->key, "=");
		value = ft_strdup(envc->value);
		*ref = ft_strjoin(key, value);
		free(key);
		free(value);
		ref++;
		envc = envc->next;
	}
	*ref = NULL;
}

//We need a function that returns the envp array with all available envar
char	**ft_set_envp(t_envar *envc, t_error *err)
{
	char	**envp;

	if (!envc)
	{
		err->set_envp = 1;
		return (NULL);
	}
	envp = ft_calloc(ft_envar_amount(envc, err) + 1, sizeof(char *));
	ft_assign_envp(envc, &envp);
	err->set_envp = 0;
	return (envp);
}

//This functions extracts the key and the value from the passed envp[index]
char	*ft_extract_key(char *str, t_error *err)
{
	char	*key;
	char	*start;
	char	*end;
	size_t	amount;

	if (!str)
		return (NULL);
	start = str;
	end = NULL;
	key = NULL;
	while (*str && *str != '=')
		str++;
	end = str;
	if (end == start || *str != '=')
	{
		err->extract_key = 1;
		return (NULL);
	}
	amount = ((size_t)(end - start)) + 1;
	key = ft_calloc(amount, sizeof(char));
	ft_strlcpy(key, start, amount);
	return (key);
}

//This fuinction extracts the value from the passed envp[index]
char	*ft_extract_value(char *str, t_error *err)
{
	char	*value;
	char	*start;
	char	*end;
	size_t	amount;

	if (!str)
	{
		err->extract_value = 1;
		return (NULL);
	}
	value = NULL;
	start = NULL;
	end = (str + ft_strlen(str));
	while (*str && *str != '=')
		str++;
	if (!*str)
		return (NULL);
	str++;
	start = str;
	amount = ((size_t)(end - start)) + 1;
	value = ft_calloc(amount, sizeof(char));
	ft_strlcpy(value, start, amount);
	return (value);
}

//A function that creates the envc chain from the envp
t_envar	*ft_set_envc(char **envp, t_error *err)
{
	t_envar	*envc;
	t_envar	*new_env;
	int		i;

	if (!envp || !*envp)
	{
		err->set_envc = 1;
		return (NULL);
	}
	envc = NULL;
	new_env = NULL;
	i = 0;
	while (envp[i])
	{
		new_env = ft_new_envar(ft_extract_key(envp[i], err),
				ft_extract_value(envp[i], err), 1, err);
		ft_add_envar(&envc, new_env, err);
		i++;
	}
	return (envc);
}
