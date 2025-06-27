/*#ifndef  so_long_h
# define so_long_h

#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "PRINTF/ft_printf.h"
#include "GNL/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int		can_move_to(t_vars *vars, int new_x, int new_y, char **map);
int		coin(t_vars	*vars,int new_x, int new_y,char **map);
int	key_touch(int keycode, t_vars *vars);
int	render_next_frame(void *param);
int get_map_width(char **map);
int get_map_height(char **map);
int	countline(const char *filename);


void	draw_map(t_vars *vars);
void	init_player_position(t_vars *vars);
void	free_map(char **map);

char **load_map(const char *filename);

#endif*/