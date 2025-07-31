/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:38:24 by asmati            #+#    #+#             */
/*   Updated: 2025/07/31 04:21:28 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	mapmap(t_vars *vars)
{
	int	img_width;
	int	img_height;

	img_width = 0;
	img_height = 0;

	img_height = get_map_height(vars->map) * TILE_SIZE;
	img_width = get_map_width(vars->map) * TILE_SIZE;
	vars->win = mlx_new_window(vars->mlx, img_width, img_height, "HI");
	vars->mur = mlx_xpm_file_to_image(vars->mlx, "XPM/bedrock.xpm", &img_width, &img_height);
	vars->sol = mlx_xpm_file_to_image(vars->mlx, "XPM/coin.xpm", &img_width, &img_height);
	vars->img1 = mlx_xpm_file_to_image(vars->mlx, "XPM/zaza.xpm", &img_width,&img_height);
	vars->img2 = mlx_xpm_file_to_image(vars->mlx, "XPM/zaza2.xpm", &img_width, &img_height);
	vars->end = mlx_xpm_file_to_image(vars->mlx, "XPM/nether.xpm", &img_width, &img_height);
	vars->feuille = mlx_xpm_file_to_image(vars->mlx, "XPM/netherblock.xpm", &img_width, &img_height);
	vars->spawn = mlx_xpm_file_to_image(vars->mlx, "XPM/bed.xpm", &img_width, &img_height);
	return (0);
}

int	close_winds(t_vars *vars)
{
	free_all(vars);
	ft_printf("Fonction de fermeture appelée!\n");
	exit (0);
	return (0);
}

int	countline(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while ((line))
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}
