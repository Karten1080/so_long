/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/06 18:41:11 by asmati            #+#    #+#             */
/*   Updated: 2025/10/06 18:41:11 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clear_backn(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return ;
	while (s[len])
		len++;
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

char	**load_map(const char *filename)
{
	int		fd;
	int		i;
	int		lines;
	char	**map;

	lines = countline(filename);
	if (lines <= 0)
		return (0);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(map), NULL);
	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		clear_backn(map[i]);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	render_next_frame(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_clear_window(vars->mlx, vars->win);
	draw_map(vars);
	if (vars->current_frame == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img1, vars->x,
			vars->y);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img2, vars->x,
			vars->y);
	return (0);
}

int	is_exit_blocked(char **map, int x, int y)
{
	if (y - 1 >= 0 && map[y - 1][x] != '1')
		return (0);
	if (map[y + 1] != NULL && map[y + 1][x] != '1')
		return (0);
	if (x - 1 >= 0 && map[y][x - 1] != '1')
		return (0);
	if (map[y][x + 1] != '\0' && map[y][x + 1] != '1')
		return (0);
	return (1);
}

void	init_exit_position(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			if (vars->map[y][x] == 'E')
			{
				vars->x = x * TILE_SIZE;
				vars->y = y * TILE_SIZE;
				return ;
			}
			x++;
		}
		y++;
	}
}
