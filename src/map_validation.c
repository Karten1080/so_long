/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:50:00 by asmati            #+#    #+#             */
/*   Updated: 2025/09/26 23:50:00 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_elements(char **map)
{
	int	i;
	int	j;
	int	exit_count;
	int	player_count;
	int	collectible_count;

	exit_count = 0;
	player_count = 0;
	collectible_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				exit_count++;
			else if (map[i][j] == 'P')
				player_count++;
			else if (map[i][j] == 'C')
				collectible_count++;
			j++;
		}
		i++;
	}
	if (exit_count != 1)
		return (ft_printf("Error: Map must have exactly 1 exit (E)\n"), 1);
	if (player_count != 1)
		return (ft_printf("Error: Map must have exactly 1 player start (P)\n"), 1);
	if (collectible_count < 1)
		return (ft_printf("Error: Map must have at least 1 collectible (C)\n"), 1);
	return (0);
}

int	check_map_validity(char **map)
{
	int	i;
	int	j;
	int	exit_count;

	i = 0;
	exit_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != '1'
				&& map[i][j] != '0' && map[i][j] != 'C' && map[i][j] != '\n')
				exit_count++;
			j++;
		}
		i++;
	}
	if (exit_count > 0)
	{
		ft_printf("Erreur : la map contient des caractères invalides.\n");
		return (1);
	}
	return (0);
}

int	check_map_entry(char **map)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	j = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1')
			return (ft_printf("Error: map not closed (top wall)\n"), 1);
		i++;
	}
	width = i;
	i = 1;
	while (map[i] && map[i + 1])
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (ft_printf("Error: map not closed (side walls)\n"), 1);
		i++;
	}
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (ft_printf("Error: map not closed (bottom wall)\n"), 1);
		j++;
	}
	return (0);
}

int	check_rectangle(char **map)
{
	int		i;
	size_t	len;

	if (!map || !map[0])
		return (1);
	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
		{
			ft_printf("Erreur : la map n'est pas rectangulaire.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_player_blocked(char **map)
{
	t_point	p;

	p = get_player_position(map);
	if (p.x == -1 || p.y == -1)
		return (1);
	if (map[p.y - 1][p.x] != '1')
		return (0);
	if (map[p.y + 1][p.x] != '1')
		return (0);
	if (map[p.y][p.x - 1] != '1')
		return (0);
	if (map[p.y][p.x + 1] != '1')
		return (0);
	else
	{
		ft_printf("Error: Player is blocked and cannot move.\n");
		return (1);
	}
}
