/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:51:33 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 21:21:05 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_check_execution(t_error *err)
{
	int	res;

	res = 0;
	if (err->forking_check != 0 || err->run_first_built_in != 0)
		res = 1;
	if (err->executor != 0 || err->check_for_built_in != 0)
		res = 1;
	if (err->exec_built_in != 0 || err->pathseter != 0 || err->pathfinder != 0)
		res = 1;
	if (err->exec_cmd != 0)
		res = 1;
	if (res != 0)
		perror("Error: EXECUTION ERROR\n");
	return (res);
}

int	ft_error_check(t_shell *shell)
{
	if (ft_error_check_lexer(shell->err) != 0)
		return (1);
	if (ft_error_check_parser(shell->err) != 0)
		return (1);
	if (ft_error_check_expander(shell->err) != 0)
		return (1);
	if (ft_error_handle_env(shell->err) != 0)
		return (1);
	if (ft_error_check_redirections(shell->err) != 0)
		return (1);
	if (ft_error_check_execution(shell->err) != 0)
		return (1);
	return (0);
}
