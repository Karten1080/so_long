/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:52:58 by asmati            #+#    #+#             */
/*   Updated: 2025/07/31 23:02:44 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// char	**load_map(const char *filename)
// {
// 	int		fd;
// 	int		i;
// 	int		lines;
// 	char	**map;
// 	char	*line;

// 	lines = countline(filename);
// 	if (lines <= 0)
// 		return (NULL);
// 	map = malloc(sizeof(char *) * (lines + 1));
// 	if (!map)
// 		return (NULL);
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		free(map);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < lines)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		map[i] = ft_strtrim(line, "\n");
// 		free(line);
// 		if (!map[i])
// 		{
// 			// Libère en cas d'échec
// 			while (--i >= 0)
// 				free(map[i]);
// 			free(map);
// 			close(fd);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	map[i] = NULL;
// 	close(fd);
// 	return (map);
// }

char	**load_map(const char *filename)
{
	int		fd;
	int		i;
	int		lines;
	char	**map;

	i = 0;
	lines = countline(filename);
	if (lines <= 0)
		return (0);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(map);
		return (0);
	}
	while (i < lines)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	close(fd);
	return (map);
}
int check_multiple_exites(char **map){

	int	i;
	int	j;
	int	exit_count;
	
	exit_count = 0;
	i = 0;
	while(map[i]){
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'E' || map[i][j] == 'P')
				exit_count++;
			j++;
		}
		i++;
	}
	if (exit_count > 2)
		return (1);
	return (0);
}
#include <stdio.h>

t_point	get_player_position(char **map)
{
	t_point	pos;
	int		i = 0, j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

// Vérifie si le joueur est bloqué à sa position
int	is_player_blocked(char **map)
{
	t_point	p = get_player_position(map);

	if (p.x == -1 || p.y == -1)
		return (1); // Joueur introuvable = erreur = bloqué

	// Directions valides = pas un mur ('1') ou autre obstacle
	if (map[p.y - 1][p.x] != '1') return (0); // Haut
	if (map[p.y + 1][p.x] != '1') return (0); // Bas
	if (map[p.y][p.x - 1] != '1') return (0); // Gauche
	if (map[p.y][p.x + 1] != '1') return (0); // Droite
	else{
		ft_printf("Erreur joueur blocker.\n");
		return (1); // Si aucune direction n’est accessible	
	}
	
}


int check_map_validity(char **map)
{
	int i;
	int j;
	int exit_count;

	i = 0 ;
	exit_count = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != '1'  \
				&& map[i][j] != '0' && map[i][j] != 'C' && map[i][j] != '\n')
				exit_count++;
			j++;
		}
		i++;
	}
	if(exit_count > 0)
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
	while(map[0][i])
	{
		if(map[0][i] != '1')
			return (printf("map pas fermer brother"),1);
		i++;
	}
	width = i;
	i = 1;
	while(map[i + 1][j])
	{
		if(map[i][0] != '1' || map[i][width] != '1')
			return (printf("map pas fermer brother"),1);
		i++;
	}
	j = 0;
	while(map[i][j])
	{
		if(map[i][j] != '1')
			return (printf("map pas fermer brother"),1);
		j++;
	}
	return (0);
}
int	 check_rectangle(char **map)
{
	int i;
	size_t len;
	
	if (!map || !map[0])
		return (1);
	len = strlen(map[0]);
	i = 1;
	while(map[i])
	{
		if(ft_strlen(map[i]) != len)
		{
			ft_printf("Erreur : la map n'est pas rectangulaire.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	draw_tile(t_vars *vars, char tile, int x, int y)
{
	int	px;
	int	py;

	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	if (tile == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->mur, px, py);
	else if (tile == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->end, px, py);
	else if (tile == '0')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->feuille, px, py);
	else if (tile == 'C')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->sol, px, py);
	else if (tile == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->spawn, px, py);
}

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			draw_tile(vars, vars->map[y][x], x, y);
			x++;
		}
		y++;
	}
}



int	get_map_width(char **map)
{
	int	width;

	width = 0;
	if (!map || !map[0])
		return (0);
	width = strlen(map[0]);
	width--;
	return (width);
}

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	if (!map)
		return (0);
	while (map[height])
		height++;
	return (height);
}
