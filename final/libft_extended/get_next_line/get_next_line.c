/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:11:38 by akonstan          #+#    #+#             */
/*   Updated: 2025/02/19 15:05:41 by akonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*strrf;

	strrf = (char *)s;
	while (*strrf)
	{
		if (c % 256 == (unsigned char)*strrf)
			return (strrf);
		strrf++;
	}
	if (c == '\0')
		return (strrf);
	else
		return (NULL);
}

//Reads the file in BUFFER SIZE bits until it finds a \n or \0
char	*ft_read_file(int fd, char *book)
{
	char	*note;
	char	*temp;
	ssize_t	bytes_read;

	note = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, note, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(book);
			free(note);
			return (NULL);
		}
		note[bytes_read] = '\0';
		temp = ft_strjoin(book, note);
		free(book);
		book = temp;
		if (ft_strchr(book, '\n') || bytes_read == 0)
			break ;
	}
	free(note);
	return (book);
}

//Extracts the line from the book
char	*ft_extract_line(char *book)
{
	char			*line;
	unsigned int	counter;

	if (!book || *book == '\0')
		return (NULL);
	counter = 0;
	line = ft_calloc(ft_strlen(book) + 1, sizeof(char));
	while (book[counter] != '\0')
	{
		line[counter] = book[counter];
		if (book[counter] == '\n')
			break ;
		counter++;
	}
	return (line);
}

char	*ft_leftovers(char	*book)
{
	unsigned int	counter;
	char			*leftovers;
	unsigned int	i;

	if (!book)
		return (NULL);
	counter = 0;
	i = 0;
	while (book[counter] != '\0' && book[counter] != '\n')
		counter++;
	if (book[counter] == '\n')
		counter++;
	leftovers = ft_calloc((ft_strlen(book) - counter + 1), sizeof(char));
	while (book[counter] != '\0')
	{
		leftovers[i] = book[counter];
		i++;
		counter++;
	}
	free(book);
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, 1);
	buffer = ft_read_file(fd, buffer);
	if (!buffer || *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_extract_line(buffer);
	buffer = ft_leftovers(buffer);
	return (line);
}
