/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:21:53 by asmati            #+#    #+#             */
/*   Updated: 2025/07/31 23:03:21 by asmati           ###   ########.fr       */
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
	SAFE_DESTROY(vars->mur);
	SAFE_DESTROY(vars->sol);
	SAFE_DESTROY(vars->end);
	SAFE_DESTROY(vars->feuille);
	SAFE_DESTROY(vars->img1);
	SAFE_DESTROY(vars->img2);
	SAFE_DESTROY(vars->spawn);

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
		SAFE_FREE(vars->mlx);
	}
}

int	main(int argc, char **argv)
{
	int count;
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

	vars.map = load_map(argv[1]);
	if (!vars.map)
		return (ft_printf("Error: failed to load map.\n"), 1);
	if(check_map_entry(vars.map) == 1)
		return (free_map(vars.map),0);
	if(check_multiple_exites(vars.map) == 1)
		return (free_map(vars.map),ft_printf("Error: multiple exits detected.\n"),0);
	if(check_rectangle(vars.map) == 1) 
		return (free_map(vars.map),0);
	if(check_map_validity(vars.map) == 1)
		return (free_map(vars.map),0);
	if(is_player_blocked(vars.map) == 1)
		return (free_map(vars.map),0);
	
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
