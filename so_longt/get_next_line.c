/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 01:37:14 by asmati            #+#    #+#             */
/*   Updated: 2025/07/10 00:41:56 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static char	*_fill_line_buffer(int fd, char *stash, char *buffer);
static char	*_set_line(char **line_buffer);

static char	*_set_line(char **line_buffer)
{
	size_t	i;
	char	*tab;
	char	*rest;

	i = 0;
	if (!*line_buffer || (*line_buffer)[0] == '\0')
		return (NULL);
	while ((*line_buffer)[i] != '\n' && (*line_buffer)[i] != '\0')
		i++;
	if ((*line_buffer)[i] == '\n')
		i++;
	tab = ft_substr(*line_buffer, 0, i);
	if (!tab)
		return (NULL);
	if (i >= ft_strlen(*line_buffer))
		return (free(*line_buffer),*line_buffer = NULL,tab);
	rest = ft_substr(*line_buffer, i, ft_strlen(*line_buffer) - i);
	if (!rest)
		return (free(tab),NULL);
	return (free(*line_buffer),*line_buffer = rest,tab);
}

static char	*_fill_line_buffer(int fd, char *stash, char *buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	if (!stash)
	{
		stash = ft_strdup_gnl("");
		if (!stash)
			return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0 )
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)			
			return (free(stash),stash = NULL,NULL);
		if(bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(stash, buffer);
		if(!stash)
			return(free(tmp),NULL);
		free(tmp);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(buffer),NULL);
	stash = _fill_line_buffer(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = _set_line(&stash);
	if (!line || line[0] == '\0')
		return (free(line),free(stash),stash = NULL,NULL);
	return (line);
}
