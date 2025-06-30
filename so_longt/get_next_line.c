/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:35:44 by raamayri          #+#    #+#             */
/*   Updated: 2025/06/29 22:47:20 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_line_gnl(char *lo)
{
	char	*ln;
	int		lnlen;
	int		i;

	if (!lo)
		return (NULL);
	lnlen = strlen_gnl(lo, '\n');
	if (lo[lnlen] == '\n')
		lnlen++;
	ln = malloc(sizeof(char) * (lnlen + 1));
	if (!ln)
		return (free(lo), NULL);
	i = -1;
	while (++i < lnlen)
		ln[i] = lo[i];
	ln[i] = '\0';
	return (ln);
}

char	*update_leftover_gnl(char *lo)
{
	char	*new_lo;
	int		i;
	int		j;

	if (!lo)
		return (NULL);
	i = strlen_gnl(lo, '\n');
	if (lo[i] == '\n')
		i++;
	if (!lo[i])
		return (free(lo), NULL);
	new_lo = malloc(sizeof(char) * (strlen_gnl(lo, '\0') - i + 1));
	if (!new_lo)
		return (free(lo), NULL);
	j = -1;
	while (lo[i + (++j)])
		new_lo[j] = lo[i + j];
	new_lo[j] = '\0';
	return (free(lo), new_lo);
}

char	*read_filedescriptor_gnl(int fd, char *lo)
{
	char	*bf;
	int		br;

	bf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bf)
		return (NULL);
	br = 1;
	while (!ft_strchr_gnl(lo, '\n') && br != 0)
	{
		br = read(fd, bf, BUFFER_SIZE);
		if (br == -1)
			return (free(lo), free(bf), NULL);
		bf[br] = '\0';
		lo = strjoin_gnl(lo, bf);
		if (!lo)
			return (free(bf), NULL);
	}
	return (free(bf), lo);
}

char	*get_next_line(int fd)
{
	static char	*lo[1024];
	char		*ln;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	lo[fd] = read_filedescriptor_gnl(fd, lo[fd]);
	if (!lo[fd])
		return (NULL);
	ln = get_line_gnl(lo[fd]);
	if (!ln)
		return ((lo[fd] = NULL), NULL);
	lo[fd] = update_leftover_gnl(lo[fd]);
	if (!ln[0])
		return (free(ln), NULL);
	return (ln);
}
