/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:51:00 by asmati            #+#    #+#             */
/*   Updated: 2025/09/26 23:51:00 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_vars *vars, char tile, int x, int y)
{
	int	px;
	int	py;

	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
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
	width = ft_strlen(map[0]);
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

t_point	get_player_position(char **map)
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
			if (map[i][j] == 'P')
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
