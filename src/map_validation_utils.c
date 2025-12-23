/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:30:00 by asmati            #+#    #+#             */
/*   Updated: 2025/10/25 14:26:04 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	count_elements(char **map, int *exit_c, int *player_c, int *coll_c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				(*exit_c)++;
			else if (map[i][j] == 'P')
				(*player_c)++;
			else if (map[i][j] == 'C')
				(*coll_c)++;
			j++;
		}
		i++;
	}
}

int	check_map_elements(char **map)
{
	int	exit_count;
	int	player_count;
	int	collectible_count;

	exit_count = 0;
	player_count = 0;
	collectible_count = 0;
	count_elements(map, &exit_count, &player_count, &collectible_count);
	if (exit_count != 1)
		return (ft_printf("Error: Map must have exactly 1 exit (E)\n"), 1);
	if (player_count != 1)
		return (ft_printf("Error: Map must have exactly 1 player start (P)\n"),
			1);
	if (collectible_count < 1)
		return (ft_printf("Error: Map must have at least 1 collectible (C)\n"),
			1);
	return (0);
}
