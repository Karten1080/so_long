/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:53:52 by asmati            #+#    #+#             */
/*   Updated: 2025/09/26 23:47:23 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	can_move_to(t_vars *vars, int new_x, int new_y, char **map)
{
	int	map_x;
	int	map_y;

	(void)vars;
	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (map[map_y][map_x] == '1')
		return (0);
	if (map[map_y][map_x] == 'E')
		return (2);
	return (1);
}

void	init_player_position(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			if (vars->map[y][x] == 'P')
			{
				vars->x = x * TILE_SIZE;
				vars->y = y * TILE_SIZE;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	key_touch(int keycode, t_vars *vars)
{
	int	new_x;
	int	new_y;
	int	move_result;

	new_x = vars->x;
	new_y = vars->y;
	if (keycode == XK_Escape)
		endgame(vars);
	else if (keycode == XK_Left)
		new_x -= TILE_SIZE;
	else if (keycode == XK_Right)
		new_x += TILE_SIZE;
	else if (keycode == XK_Up)
		new_y -= TILE_SIZE;
	else if (keycode == XK_Down)
		new_y += TILE_SIZE;
	move_result = can_move_to(vars, new_x, new_y, vars->map);
	if (move_result == 1 || move_result == 2)
	{
		new_y_x(new_x, new_y, vars);
		if (move_result == 2 && coin_counter(vars) == 0)
			endgame(vars);
	}
	return (0);
}

int	render_next_frame(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	draw_map(vars);
	if (vars->current_frame == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img1, vars->x,
			vars->y);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img2, vars->x,
			vars->y);
	return (0);
}
