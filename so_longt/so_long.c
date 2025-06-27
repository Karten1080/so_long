/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:21:53 by asmati            #+#    #+#             */
/*   Updated: 2025/06/26 22:04:17 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/get_next_line.h"
#include "PRINTF/ft_printf.h"
#include "so_long.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TILE_SIZE 30

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*img1;
	void	*img2;
	void	*mur;
	void	*sol;
	void	*end;
	void	*spawn;
	void	*feuille;
	char	*relative_path;
	int		points_collected;
	int		x;
	int		y;
	int		current_frame;
	int		perso_width;
	int		perso_height;
	char	**map;
}			t_vars;

typedef struct s_line
{
	char *line;          // La ligne de texte (une ligne de la map)
	struct s_line *next; // Pointeur vers la ligne suivante
}			t_line;

/*char *map[] = {
	"1111111111111111111111",
	"1C100000P00000000001E1",
	"1010000000000000000001",
	"1010000000000000000101",
	"1010000000000000000101",
	"1011111111111000000111",
	"1010000000000000000001",
	"101000000000000C000001",
	"1010000000000000000001",
	"1010000000000000000001",
	"1010000000000000000001",
	"1010000000000000000001",
	"1010000000000000000001",
	"1010000000000000000001",
	"1011111111111111100001",
	"1111111111111111111111",
	NULL
};*/

int	can_move_to(t_vars *vars, int new_x, int new_y, char **map)
{
	int	map_x;
	int	map_y;

	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	/*if (!map[map_y] || !map[map_y][map_x])
		return (0);  // hors map*/
	if (map[map_y][map_x] == '1')
		return (0);
	if (map[map_y][map_x] == 'E')
		return (2);
	return (1);
}
int	coin(t_vars *vars, int new_x, int new_y, char **map)
{
	int	x;
	int	y;

	x = new_x / TILE_SIZE;
	y = new_y / TILE_SIZE;
	if (map[y][x] == 'C')
	{
		map[y][x] = '0';
		vars->points_collected++;
		printf("gg tas pris une piece pd va %d", vars->points_collected);
		return (1);
	}
	return (0);
}
/*void	draw_map(t_vars *vars)
{
	int		x;
	int		y;
	char	title;
	int		px;
	int		py;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			title = vars->map[y][x];
			px = x * TILE_SIZE;
			py = y * TILE_SIZE;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sol, px, py);
			if (title == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->mur, px,
					py);
			if (title == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->end, px,
					py);
			if (title == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->feuille, px,
					py);
			if (title == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sol, px,
					py);
			if (title == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->spawn, px,
					py);
			x++;
		}
		y++;
	}
}*/

int	coin_counter(t_vars *vars)
{
	int		x;
	int		y;
	char	title;
	int		allcoins;

	allcoins = 0;
	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			title = vars->map[y][x];
			if (title == 'C')
				allcoins++;
			x++;
		}
		y++;
	}
	return (allcoins);
}
void	init_player_position(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			if (vars->map[y][x] == 'P')
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

int	key_touch(int keycode, t_vars *vars)
{
	int	new_x;
	int	new_y;
	int	move_result;
	int	coins;

	new_x = vars->x;
	new_y = vars->y;
	coins = coin_counter(vars);
	printf("%d", coins);
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == XK_Left)
		new_x -= 30;
	else if (keycode == XK_Right)
		new_x += 30;
	else if (keycode == XK_Up)
		new_y -= 30;
	else if (keycode == XK_Down)
		new_y += 30;
	// Vérifier collision AVANT de déplacer
	move_result = can_move_to(vars, new_x, new_y, vars->map);
	if (move_result == 1)
	{
		vars->x = new_x;
		vars->y = new_y;
		coin(vars, new_x, new_y, vars->map);
		coins--;
	}
	else if (move_result == 2 && coins == 0
		/*mettre on condision et si plus aucun points dispo bah confition ok*/)
	{
		printf("Bienjouer");
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	printf("Position perso: x=%d y=%d\n", vars->x, vars->y);
	return (0);
}

int	render_next_frame(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_clear_window(vars->mlx, vars->win);
	draw_map(vars);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	if (vars->current_frame == 0)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img1, vars->x,
			vars->y);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img2, vars->x,
			vars->y);
	vars->current_frame = 1 - vars->current_frame; // alterne entre 0 et 1
	// usleep(100000);                                // délai (~0.2 sec)
	return (0);
}

/*int	get_map_width(char **map)
{
	int	width;

	width = 0;
	if (!map || !map[0])
		return (0);
	return (strlen(map[0])); // pas oublier dutiliser ma libft
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
}*/

int	countline(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	count = 0;
	line = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

/*char	**load_map(const char *filename)
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
	if (fd < 0)
		return (0);
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		/*if(map[i] && map[i][strlen(map[i]) - 1] == '\n')
			map[i][strlen(map[i]) - 1] = '\0';*/
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}*/

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
int	main(void)
{
	t_vars	vars;
	int		img_width;
	int		img_height;

	vars.map = load_map("MAP/map.ber");
	printf("Longueur de la première ligne : %lu\n", strlen(vars.map[0]));
	// printf("%d",coin_counter(&vars));
	if (!vars.map)
		return (0);
	img_height = get_map_height(vars.map) * TILE_SIZE;
	img_width = get_map_width(vars.map) * TILE_SIZE; // 5 lignes
														// 7 colonnes
														// printf("%d%d",img_height,img_width);
	if (img_width == img_height)
	{
		printf("Bro c trop carrer on kiff pas les carrer ici");
		return (0);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "HI");
	/*vars.img =  mlx_xpm_file_to_image(vars.mlx, "back.xpm", &img_width,
			&img_height);*/
	vars.mur = mlx_xpm_file_to_image(vars.mlx, "XPM/zaza.xpm", &img_width,
			&img_height);
	vars.sol = mlx_xpm_file_to_image(vars.mlx, "XPM/coin.xpm", &img_width,
			&img_height);
	vars.img1 = mlx_xpm_file_to_image(vars.mlx, "XPM/zaza.xpm",
			&vars.perso_height, &vars.perso_width);
	vars.img2 = mlx_xpm_file_to_image(vars.mlx, "XPM/zaza2.xpm",
			&vars.perso_height, &vars.perso_width);
	vars.end = mlx_xpm_file_to_image(vars.mlx, "XPM/nether.xpm", &img_width,
			&img_height);
	vars.feuille = mlx_xpm_file_to_image(vars.mlx, "XPM/netherblock.xpm",
			&img_width, &img_height);
	vars.spawn = mlx_xpm_file_to_image(vars.mlx, "XPM/bed.xpm", &img_width,
			&img_height);
	vars.current_frame = 0;
	vars.points_collected = 0;
	vars.x = TILE_SIZE;
	vars.y = TILE_SIZE;
	// vars.map = map;
	vars.perso_height = img_height;
	vars.perso_width = img_width;
	init_player_position(&vars);
	draw_map(&vars);
	coin_counter(&vars);
	// mlx_key_hook(vars.win,key_touch, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_touch, &vars);
	mlx_loop(vars.mlx);
	free_map(vars.map); // PAS OUBLIER DE FREE MAP
		/////////////////////////////////////////////////////////
	return (0);
}

/*int	mouse_move_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!%d\n", keycode);
	return (0);
}
int	mouse_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!%d\n", keycode);
	return (0);
}

int	key_hook(int keycode,
		t_vars🚨 2. Tu appelles free_map(vars.map) avant la fin du programme *vars)
{
	if(keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx,vars->win);
		exit (0);
	}
	printf("Hello from key_hook!%d\n", keycode);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 6, 1L << 6, mouse_move_hook, &vars);
	mlx_loop(vars.mlx);
}
#include <mlx.h>

int	render_next_frame(void *vars)
{
	printf("Salut toi");
}

int	main(void)
{
	t_vars	vars;
	vars.mlx = mlx_init();
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_loop(vars.mlx);
}*/
