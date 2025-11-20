/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:30:31 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//a function that handles export error
static int	ft_export_error(t_shell *shell)
{
	shell->err->ft_export = 1;
	return (shell->last_exit = 1);
}

//Helper for reassigning the envar values
static int	ft_reassign_value(t_envar *envar, char *value)
{
	if (value != NULL)
	{
		free(envar->value);
		envar->value = value;
	}
	envar->is_exported = 1;
	return (0);
}

//Check if passes key exists, if not, check if it has valid chars for env
//variable name, then create the envar with the passed key
int	ft_export(char **argv, t_shell *shell)
{
	char	*key;
	char	*value;
	size_t	env_amount;
	t_envar	*envar;

	if (!argv || argv[2] != NULL)
		ft_export_error(shell);
	key = ft_extract_key(argv[1], shell->err);
	value = ft_extract_value(argv[1], shell->err);
	env_amount = ft_envar_amount(shell->envc, shell->err);
	envar = ft_get_envar(shell->envc, key, shell->err);
	if (key == NULL || ft_valid_env(key, shell->err) == 1)
		ft_export_error(shell);
	if (envar == NULL)
		ft_add_envar(&(shell->envc), ft_new_envar(key, value, 1, shell->err),
			shell->err);
	else
		ft_reassign_value(envar, value);
	ft_freearr(shell->envp, env_amount);
	shell->envp = ft_set_envp(shell->envc, shell->err);
	return (shell->last_exit = 0);
}
