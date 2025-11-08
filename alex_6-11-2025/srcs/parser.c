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

//Main parsing function
t_pipe	*ft_parser(t_token **chain, t_error *err)
{
	t_pipe	*pipeline;

	if (!chain || !(*chain) || ft_check_token_chain (*chain, err) == 1)
	{
		err->parser = 1;
		return (NULL);
	}
	pipeline = NULL;
	while ((*chain))
	{
		ft_add_pipe(&pipeline, chain, err);
		if (ft_error_check_parser(err) == 1)
		{
			err->parser = 1;
			return (pipeline);
		}
	}
	return (pipeline);
}
