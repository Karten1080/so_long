/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 22:12:46 by asmati            #+#    #+#             */
/*   Updated: 2025/10/23 22:12:46 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_top_wall(char **map, int *width)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1')
			return (ft_printf("Error: map not closed (top wall)\n"), 1);
		i++;
	}
	*width = i;
	return (0);
}

static int	check_side_walls(char **map, int width)
{
	int	i;

	i = 1;
	while (map[i] && map[i + 1])
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (ft_printf("Error: map not closed (side walls)\n"), 1);
		i++;
	}
	return (0);
}

static int	check_bottom_wall(char **map)
{
	int	j;
	int	i;

	i = 0;
	while (map[i] && map[i + 1])
		i++;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (ft_printf("Error: map not closed (bottom wall)\n"), 1);
		j++;
	}
	return (0);
}

int	check_map_entry(char **map)
{
	int	width;

	if (check_top_wall(map, &width))
		return (1);
	if (check_side_walls(map, width))
		return (1);
	if (check_bottom_wall(map))
		return (1);
	return (0);
}

int	check_xmp(t_vars *vars)
{
	if (!vars->mur)
		return (ft_printf("Error: Failed to load bedrock.xpm\n"), 1);
	if (!vars->sol)
		return (ft_printf("Error: Failed to load coin.xpm\n"), 1);
	if (!vars->img1)
		return (ft_printf("Error: Failed to load zaza.xpm\n"), 1);
	if (!vars->img2)
		return (ft_printf("Error: Failed to load zaza2.xpm\n"), 1);
	if (!vars->end)
		return (ft_printf("Error: Failed to load nether.xpm\n"), 1);
	if (!vars->feuille)
		return (ft_printf("Error: Failed to load netherblock.xpm\n"), 1);
	if (!vars->spawn)
		return (ft_printf("Error: Failed to load bed.xpm\n"), 1);
	return (0);
}
