/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:07:56 by mstawski          #+#    #+#             */
/*   Updated: 2025/11/20 18:12:28 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sa_handler(int signal)
{
	g_received_signal = signal;
	if (signal == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signals(int signal)
{
	struct sigaction	sa_parent;

	sigemptyset(&sa_parent.sa_mask);
	if (signal == SIGQUIT)
	{
		sa_parent.sa_handler = SIG_IGN;
		sigaddset(&sa_parent.sa_mask, SIGINT);
	}
	else if (signal == SIGINT)
	{
		sa_parent.sa_handler = ft_sa_handler;
		sigemptyset(&sa_parent.sa_mask);
	}
	sa_parent.sa_flags = SA_RESTART;
	if (sigaction(signal, &sa_parent, NULL))
		exit(2);
}
