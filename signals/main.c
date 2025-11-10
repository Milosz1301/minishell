/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:54 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/03 19:30:25 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static volatile sig_atomic_t g_received_signal; // subject allows it

int	main(int argc, char	*argv[])
{
	t_pipe	*pipeline;
	t_shell	*shell;

	pipeline = NULL;
	shell = NULL;
	signals(); 
	if (argc == 1 && argv)
	{
		while (1)
		{
			g_received_signal = 0;
			shell = ft_calloc(1, sizeof(t_shell));
			shell->input = readline("minishell$> ");
			if (!shell->input)
			{
				if (errno == EINTR)
					continue;
				ft_exit(pipeline, shell, shell->err);
			}
			shell->err = ft_calloc(1, sizeof(t_error));
			shell->chain = lexer(shell->input, shell->err);
			pipeline = ft_parser(&(shell->chain), shell->err);
			ft_expander(pipeline, shell, shell->err);
			print_pipeline(pipeline);
			ft_del_pipeline(&pipeline, shell->err);
			free(shell->err);
			free(shell->input);
			free(shell);
		}
	}
	return (0);
}
