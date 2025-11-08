/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:00:44 by akonstan          #+#    #+#             */
/*   Updated: 2025/10/13 14:00:46 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function will be the last to be run in the expander. It will set the
// pointer argv** in the *command in the pipe passed
//Additionally it will fill the last command string in the shell status struct
int	ft_set_cmd_argv(t_pipe *pipe, t_shell *shell, t_error *err)
{
	t_token	*cmd_chain;
	char	*ref;
	int		i;

	if (!shell || !pipe)
		return (err->set_cmd_argv = 1);
	cmd_chain = pipe->command->cmd_chain;
	ref = NULL;
	i = 0;
	pipe->command->argv = ft_calloc(pipe->cmd_amount + 1, sizeof(char *));
	while (cmd_chain->type != T_END)
	{
		ref = cmd_chain->string;
		(pipe->command->argv)[i] = ft_strdup(ref);
		i++;
		cmd_chain = cmd_chain->next;
	}
	(pipe->command->argv)[i] = NULL;
	return (err->set_cmd_argv = 0);
}

//A function that detects if the currect character is a valid characted for
//an env variable
//charcter can be a letter, a number (NOT IN FIRST SPOT),
int	ft_isenvchar(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	ft_handle_qumark(char **target, char **result, char *start, t_shell *shell)
{
	*target = ft_itoa(shell->last_exit);
	*result = ft_strjoin(*target, start + 1);
	free(target);
	return (0);
}
