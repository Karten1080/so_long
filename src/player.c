/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:53:52 by asmati            #+#    #+#             */
/*   Updated: 2025/10/20 15:43:11 by asmati           ###   ########.fr       */
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

static int	get_new_position(int keycode, int *new_x, int *new_y)
{
	if (keycode == XK_Escape)
		return (-1);
	else if (keycode == 'a' || keycode == XK_Left)
		*new_x -= TILE_SIZE;
	else if (keycode == 'd' || keycode == XK_Right)
		*new_x += TILE_SIZE;
	else if (keycode == 'w' || keycode == XK_Up)
		*new_y -= TILE_SIZE;
	else if (keycode == 's' || keycode == XK_Down)
		*new_y += TILE_SIZE;
	else
		return (1);
	return (0);
}

static void	handle_move(t_vars *vars, int new_x, int new_y, int move_result)
{
	new_y_x(new_x, new_y, vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img1, vars->x,
		vars->y);
	vars->moves++;
	ft_printf("Moves: %d\n", vars->moves);
	if (move_result == 2 && coin_counter(vars) == 0)
		endgame(vars);
}

int	key_touch(int keycode, t_vars *vars)
{
	int	new_x;
	int	new_y;
	int	move_result;
	int	pos_result;

	new_x = vars->x;
	new_y = vars->y;
	pos_result = get_new_position(keycode, &new_x, &new_y);
	if (pos_result == -1)
		endgame(vars);
	if (pos_result == 1)
		return (0);
	move_result = can_move_to(vars, new_x, new_y, vars->map);
	if (move_result == 1 || move_result == 2)
		handle_move(vars, new_x, new_y, move_result);
	return (0);
}
