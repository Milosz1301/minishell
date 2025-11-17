/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:30:22 by mstawski          #+#    #+#             */
/*   Updated: 2025/10/06 17:50:30 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function handles you the chain of tokens made from the input to the prog 
t_token	*lexer(char *input, t_error *err)
{
	t_token	*chain;

	chain = NULL;
	ft_create_chain(&chain, ft_split_mini(input, ' ', err));
	err->lexer = 0;
	return (chain);
}
/*
int	main(int argc, char **argv)
{
	t_token	*chain;

	if (argc == 2)
	{
		chain = lexer(argv[1]);
		print_token_chain(chain, ft_chainlen(chain));
	}
	return (1);
}*/