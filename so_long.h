/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:31:18 by asmati            #+#    #+#             */
/*   Updated: 2025/07/31 22:32:21 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  so_long_h
# define so_long_h

#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "PRINTF/ft_printf.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define TILE_SIZE 30
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
#define SAFE_DESTROY(img) if (img) { mlx_destroy_image(vars->mlx, img); img = NULL; }
#define SAFE_FREE(ptr)    if (ptr) { free(ptr); ptr = NULL; }

typedef struct s_point {
	int x;
	int y;
}	t_point;

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

//SO_LONG
int		can_move_to(t_vars *vars, int new_x, int new_y, char **map);
int		coin(t_vars	*vars,int new_x, int new_y,char **map);
int		key_touch(int keycode, t_vars *vars);
int		render_next_frame(void *param);
int 	get_map_width(char **map);
int 	get_map_height(char **map);
int		countline(const char *filename);
void	draw_map(t_vars *vars);
void	init_player_position(t_vars *vars);
void	free_map(char **map);
char 	**load_map(const char *filename);
int		close_winds(t_vars *vars);
char	mapmap(t_vars *vars);
void	endgame(t_vars *vars);
void	new_y_x(int x, int y, t_vars *vars);
int		coin_counter(t_vars *vars);
int check_multiple_exites(char **map);
//GNL
char *ft_strchr(const char *s, int c);
char	*ft_strdup_gnl(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);


void	free_all(t_vars *vars);
int	 check_rectangle(char **map);


#endif