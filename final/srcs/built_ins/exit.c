/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:32:23 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_pipe *pipeline, t_shell *shell)
{
	if (pipeline)
		ft_del_pipeline(&pipeline, shell->err);
	if (shell)
		ft_del_shell(&shell);
	rl_clear_history();
	exit(0);
}
