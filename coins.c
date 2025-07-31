/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:38:41 by asmati            #+#    #+#             */
/*   Updated: 2025/07/30 00:00:47 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	coin_counter(t_vars *vars)
{
	int		x;
	int		y;
	char	title;
	int		allcoins;

	allcoins = 0;
	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			title = vars->map[y][x];
			if (title == 'C')
				allcoins++;
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
		ft_printf("Bien jouer une piece a ete recolter%d", vars->points_collected);
		return (1);
	}
	return (0);
}
