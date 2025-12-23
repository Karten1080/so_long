/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:45:00 by asmati            #+#    #+#             */
/*   Updated: 2025/10/25 14:22:50 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_size(char **map)
{
	int	width;
	int	height;

	if (!map || !map[0])
		return (1);
	width = get_map_width(map) * TILE_SIZE;
	height = get_map_height(map) * TILE_SIZE;
	if (width > MAX_WIDTH || height > MAX_HEIGHT)
	{
		ft_printf("Error: Map is too big (max %dx%d pixels)\n", MAX_WIDTH,
			MAX_HEIGHT);
		return (1);
	}
	return (0);
}

int	check_map_validity(char **map)
{
	int	i;
	int	j;
	int	exit_count;

	i = 0;
	exit_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != '1'
				&& map[i][j] != '0' && map[i][j] != 'C' && map[i][j] != '\n')
				exit_count++;
			j++;
		}
		i++;
	}
	if (exit_count > 0)
	{
		ft_printf("Erreur : la map contient des caractères invalides.\n");
		return (1);
	}
	return (0);
}

t_point	get_exit_position(char **map)
{
	t_point	pos;
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}
