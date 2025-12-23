/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:21:53 by asmati            #+#    #+#             */
/*   Updated: 2025/10/25 14:10:32 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	endgame(t_vars *vars)
{
	ft_printf("Fin du jeu\n");
	free_all(vars);
	exit(0);
}

void	new_y_x(int x, int y, t_vars *vars)
{
	vars->x = x;
	vars->y = y;
	coin(vars, x, y, vars->map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_all(t_vars *vars)
{
	safe_destroy(vars->mlx, &vars->mur);
	safe_destroy(vars->mlx, &vars->sol);
	safe_destroy(vars->mlx, &vars->end);
	safe_destroy(vars->mlx, &vars->feuille);
	safe_destroy(vars->mlx, &vars->img1);
	safe_destroy(vars->mlx, &vars->img2);
	safe_destroy(vars->mlx, &vars->spawn);
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->map)
		free_map(vars->map);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		safe_free((void **)&vars->mlx);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (ft_printf("Usage: %s <map_file>\n", argv[0]), 1);
	if (init_game(&vars, argv[1]) != 0)
		return (1);
	start_game(&vars);
	free_map(vars.map);
	return (0);
}
