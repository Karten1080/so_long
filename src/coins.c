/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:38:41 by asmati            #+#    #+#             */
/*   Updated: 2025/10/25 14:12:06 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_coin_blocked(char **map, int x, int y)
{
	if (y - 1 >= 0 && map[y - 1][x] != '1')
		return (0);
	if (map[y + 1] != NULL && map[y + 1][x] != '1')
		return (0);
	if (x - 1 >= 0 && map[y][x - 1] != '1')
		return (0);
	if (map[y][x + 1] != '\0' && map[y][x + 1] != '1')
		return (0);
	return (1);
}

int	coin_counter(t_vars *vars)
{
	int	x;
	int	y;
	int	allcoins;

	allcoins = 0;
	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			if (vars->map[y][x] == 'C')
			{
				allcoins++;
				if (is_coin_blocked(vars->map, x, y))
					return (ft_printf("Error: Coin blocked.\n"), endgame(vars),
						0);
			}
			x++;
		}
		y++;
	}
	return (allcoins);
}

int	coin(t_vars *vars, int new_x, int new_y, char **map)
{
	int	x;
	int	y;

	x = new_x / TILE_SIZE;
	y = new_y / TILE_SIZE;
	if (map[y][x] == 'C')
	{
		map[y][x] = '0';
		vars->points_collected++;
		ft_printf("Bien joué ! Une pièce a été récoltée\n");
		return (1);
	}
	return (0);
}
