/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:54 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 21:20:00 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_received_signal = 0;

void	ft_main_initialization(t_shell **shell, char **envp)
{
	g_received_signal = 0;
	ft_signals(SIGINT);
	ft_signals(SIGQUIT);
	*shell = ft_calloc(1, sizeof(t_shell));
	(*shell)->err = ft_calloc(1, sizeof(t_error));
	(*shell)->envc = ft_set_envc(envp, (*shell)->err);
	(*shell)->env_amount = ft_envar_amount((*shell)->envc, (*shell)->err);
	(*shell)->envp = ft_set_envp((*shell)->envc, (*shell)->err);
}

void	ft_loop_functionality(t_shell **shell)
{
	(*shell)->chain = lexer((*shell)->input, (*shell)->err);
	(*shell)->pipeline = ft_parser(&((*shell)->chain), (*shell)->err);
	ft_expander((*shell)->pipeline, *shell, (*shell)->err);
	ft_executor((*shell)->pipeline, *shell, (*shell)->err);
	ft_del_pipeline(&(*shell)->pipeline, (*shell)->err);
	free((*shell)->input);
	ft_refresh_rl();
}

int	main(int argc, char	*argv[], char **envp)
{
	t_shell	*shell;

	if (argc == 1 && argv)
	{
		ft_main_initialization(&shell, envp);
		while (1)
		{
			shell->input = readline("minishell$> ");
			if (shell->input && *(shell->input))
				add_history(shell->input);
			else if (!shell->input)
				ft_exit(shell->pipeline, shell);
			else
			{
				ft_refresh_rl();
				continue ;
			}
			ft_loop_functionality(&shell);
		}
	}
	return (0);
}
