/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:52:58 by asmati            #+#    #+#             */
/*   Updated: 2025/06/29 22:34:37 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**load_map(const char *filename)
{
	int		fd;
	int		i;
	int		lines;
	char	**map;

	i = 0;
	lines = countline(filename);
	if (lines <= 0)
		return (0);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(map);
		return (0);
	}
	while (i < lines)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	close(fd);
	return (map);
}

void	draw_tile(t_vars *vars, char tile, int x, int y)
{
	int	px;
	int	py;

	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sol, px, py);
	if (tile == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->mur, px, py);
	else if (tile == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->end, px, py);
	else if (tile == '0')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->feuille, px, py);
	else if (tile == 'C')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->sol, px, py);
	else if (tile == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->spawn, px, py);
}

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			draw_tile(vars, vars->map[y][x], x, y);
			x++;
		}
		y++;
	}
	
}

int	get_map_width(char **map)
{
	int	width;

	width = 0;
	if (!map || !map[0])
		return (0);
	width = strlen(map[0]);
	width--;
	return (width);
}
int	get_map_height(char **map)
{
	int	height;

	height = 0;
	if (!map)
		return (0);
	while (map[height])
		height++;
	return (height);
}
