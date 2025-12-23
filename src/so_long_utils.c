/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:20:00 by asmati            #+#    #+#             */
/*   Updated: 2025/10/25 14:08:56 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_vars(t_vars *vars)
{
	vars->mur = NULL;
	vars->sol = NULL;
	vars->end = NULL;
	vars->feuille = NULL;
	vars->img1 = NULL;
	vars->img2 = NULL;
	vars->spawn = NULL;
	vars->win = NULL;
	vars->mlx = NULL;
	vars->map = NULL;
	vars->moves = 0;
	vars->current_frame = 0;
	vars->points_collected = 0;
	vars->x = 0;
	vars->y = 0;
}

static int	check_ber_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (ft_printf("Error: no map file provided.\n"), 1);
	len = ft_strlen(filename);
	if (len < 4 || !(filename[len - 4] == '.' && filename[len - 3] == 'b'
			&& filename[len - 2] == 'e' && filename[len - 1] == 'r'))
		return (ft_printf("Error: map file must have a .ber extension\n"), 1);
	return (0);
}

int	validate_and_load(t_vars *vars, char *map_file)
{
	t_point	exit_pos;

	if (check_ber_extension(map_file) == 1)
		return (1);
	vars->map = load_map(map_file);
	if (!vars->map)
		return (ft_printf("Error: failed to load map.\n"), 1);
	if (check_rectangle(vars->map) == 1)
		return (free_map(vars->map), 1);
	if (check_map_size(vars->map) == 1)
		return (free_map(vars->map), 1);
	if (check_map_entry(vars->map) == 1)
		return (free_map(vars->map), 1);
	if (check_map_elements(vars->map) == 1)
		return (free_map(vars->map), 1);
	if (check_map_validity(vars->map) == 1)
		return (free_map(vars->map), 1);
	if (is_player_blocked(vars->map) == 1)
		return (free_map(vars->map), 1);
	exit_pos = get_exit_position(vars->map);
	if (exit_pos.x != -1 && is_exit_blocked(vars->map, exit_pos.x, exit_pos.y))
		return (ft_printf("Error: Exit is blocked and cannot be used.\n"),
			free_map(vars->map), 1);
	return (0);
}

int	init_game(t_vars *vars, char *map_file)
{
	init_vars(vars);
	if (validate_and_load(vars, map_file) != 0)
		return (1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_printf("Erreur : échec de mlx_init.\n"), 1);
	if (mapmap(vars) != 0)
	{
		ft_printf("Erreur lors du chargement des images ou création.\n");
		free_all(vars);
		return (1);
	}
	return (0);
}

void	start_game(t_vars *vars)
{
	vars->current_frame = 0;
	vars->points_collected = 0;
	init_player_position(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img1, vars->x, vars->y);
	coin_counter(vars);
	mlx_hook(vars->win, 2, 1L << 0, key_touch, vars);
	mlx_hook(vars->win, 17, 0, close_winds, vars);
	mlx_loop(vars->mlx);
}
