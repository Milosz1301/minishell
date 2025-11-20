/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:23:09 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/20 18:22:17 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Redirections need to happen before execution and in a CHILD proccess
//So executor must fork a new process if a redirection or a pipe is detected
//
//This function will return 0 if you have the permissions to write on the file
//and 1 if you don't (also set the respective error as 1)
static int	ft_check_file_access(char *filepath, t_error *err)
{
	if (!access(filepath, R_OK | W_OK))
		return (err->check_file_access = 0);
	return (err->check_file_access = 1);
}

//Handles the >> redirection
int	ft_append(char *filepath, t_error *err)
{
	int	fd;

	fd = -1;
	if (!access(filepath, F_OK) && ft_check_file_access(filepath, err) == 1)
		return (err->append = 1);
	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (fd == -1)
		return (err->append = 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (err->append = 0);
}

//Handles the < redirection
int	ft_infile(char *filepath, t_error *err)
{
	int	fd;

	fd = -1;
	if (!access(filepath, F_OK) && ft_check_file_access(filepath, err) == 1)
		return (err->infile = 1);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (err->infile = 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (err->infile = 0);
}

//Handles the > redirection
int	ft_outfile(char *filepath, t_error *err)
{
	int	fd;

	fd = -1;
	if (!access(filepath, F_OK) && ft_check_file_access(filepath, err) == 1)
		return (err->outfile = 1);
	fd = open (filepath, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
		return (err->outfile = 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (err->outfile = 0);
}

//Handles the << here-doc redirection
//We will use a pipe to do the heredoc
//Heredocs need to be handled separately for every pipe in the pipeline
//and save the heredoc fd of the pipe in a separate field
int	ft_heredoc(char *delimeter, t_quote_type q_type, t_shell *shell)
{
	int		herefd[2];
	char	*line;

	pipe(herefd);
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(line, delimeter, ft_strlen(delimeter) + 1))
		{
			if (line)
				free(line);
			break ;
		}
		if (q_type == Q_NONE)
			ft_expand_str(&line, shell, shell->err);
		ft_putstr_fd(line, herefd[1]);
		write(herefd[1], "\n", 1);
		free(line);
	}
	close(herefd[1]);
	return (herefd[0]);
}
