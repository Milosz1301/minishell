/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:54 by akonstan          #+#    #+#             */
/*   Updated: 2025/09/26 18:49:55 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char	*argv[], char **envp)
{
	t_pipe	*pipeline;
	t_shell	*shell;

	if (argc == 1 && argv)
	{
		shell = ft_calloc(1, sizeof(t_shell));
		shell->err = ft_calloc(1, sizeof(t_error));
		shell->envc = ft_set_envc(envp, shell->err);
		shell->env_amount = ft_envar_amount(shell->envc, shell->err);
		shell->envp = ft_set_envp(shell->envc, shell->err);
		while (1)
		{
			shell->input = readline("minishell$> ");
			if (shell->input && *(shell->input))
				add_history(shell->input);
			else
			{
				ft_refresh_rl();
				continue;
			}
			shell->chain = lexer(shell->input, shell->err);
			pipeline = ft_parser(&(shell->chain), shell->err);
			ft_expander(pipeline, shell, shell->err);
			ft_executor(pipeline, shell, shell->err);
			ft_del_pipeline(&pipeline, shell->err);
			free(shell->input);
			ft_refresh_rl();
		}
	}
	return (0);
}
