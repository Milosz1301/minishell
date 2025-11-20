/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_helper_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:54 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 20:25:16 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Function that deletes an allocated string
void	ft_del_string(char *string)
{
	if (string)
	{
		free(string);
		string = NULL;
	}
}

size_t	ft_count_arr(char **arr)
{
	size_t	res;

	if (!arr)
		return (0);
	res = 0;
	while (arr[res])
		res++;
	res++;
	return (res);
}

int	ft_freearr(char **arr, size_t index)
{
	size_t	counter;

	counter = index;
	while (counter > 0)
	{
		counter--;
		free(arr[counter]);
	}
	free(arr);
	return (0);
}

//check if ft_count_arr should count one extra for the NULL termination of the
//array
int	ft_del_shell(t_shell **shell)
{
	if (!*shell)
		return (0);
	if ((*shell)->input)
		free((*shell)->input);
	if ((*shell)->envp)
		ft_freearr((*shell)->envp,
			ft_envar_amount((*shell)->envc, (*shell)->err));
	if ((*shell)->path_arr)
		ft_freearr((*shell)->path_arr, ft_count_arr((*shell)->path_arr));
	if ((*shell)->envc)
		ft_del_envc(&((*shell)->envc), (*shell)->err);
	if ((*shell)->chain)
		ft_del_token_chain(&((*shell)->chain), (*shell)->err);
	if ((*shell)->err)
		free((*shell)->err);
	free(*shell);
	*shell = NULL;
	return (0);
}

//Function to clear ENVC chain
int	ft_del_envc(t_envar **envc, t_error *err)
{
	t_envar	*temp;

	if (!envc)
		return (1);
	temp = NULL;
	while (*envc)
	{
		temp = (*envc)->next;
		ft_del_string((*envc)->key);
		ft_del_string((*envc)->value);
		free(*envc);
		*envc = temp;
	}
	return (err->del_envc = 0);
}
