/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:21:53 by asmati            #+#    #+#             */
/*   Updated: 2025/07/02 03:45:53 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	endgame(t_vars *vars)
{
	ft_printf("Fin du jeu");
	free_all(vars);
	exit (0);
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
	if (vars->mur)
		mlx_destroy_image(vars->mlx, vars->mur);
	if (vars->sol)
		mlx_destroy_image(vars->mlx, vars->sol);
	if (vars->end)
		mlx_destroy_image(vars->mlx, vars->end);
	if (vars->feuille)
		mlx_destroy_image(vars->mlx, vars->feuille);
	if (vars->img1)
		mlx_destroy_image(vars->mlx, vars->img1);
	if (vars->img2)
		mlx_destroy_image(vars->mlx, vars->img2);
	if (vars->spawn)
		mlx_destroy_image(vars->mlx, vars->spawn);

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
		free(vars->mlx);
		vars->mlx = NULL;
	}
}

int	main(void)
{
	t_vars	vars;

	vars.mur = NULL;
	vars.sol = NULL;
	vars.end = NULL;
	vars.feuille = NULL;
	vars.img1 = NULL;
	vars.img2 = NULL;
	vars.spawn = NULL;
	vars.win = NULL;
	vars.mlx = NULL;
	vars.map = NULL;

	vars.map = load_map("MAP/map.ber");
	if (!vars.map)
		return (ft_printf("Erreur : chargement de la map échoué.\n"), 1);
	//printf("Longueur de la première ligne : %lu\n", strlen(vars.map[0])); //mettre le ft strlen
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (ft_printf("Erreur : échec de mlx_init.\n"), 1);
	if (mapmap(&vars) != 0)
	{
		ft_printf("Erreur lors du chargement des images ou création fenêtre.\n");
		free_all(&vars);
		return (1);
	}
	vars.current_frame = 0;
	vars.points_collected = 0;
	vars.x = TILE_SIZE;
	vars.y = TILE_SIZE;

	init_player_position(&vars);
	draw_map(&vars);
	coin_counter(&vars);

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_touch, &vars);
	mlx_hook(vars.win, 17, 0, close_winds, &vars);
	mlx_loop(vars.mlx);
	free_map(vars.map);
	return (0);
}