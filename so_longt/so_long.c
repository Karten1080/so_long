#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
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


char *map[] = {
    "1111111111111111111111",
    "1C100000000000000001E1",
    "1010000000000000000001",
    "1010000000000000000101",
    "1010000000000000000101",
	"1011111111111000000111",
	"1010000000000000000001",
	"1011111111111111110001",
	"1000000000000000000001",
	"1P11111111111111100001",
    "1111111111111111111111",
	NULL
};

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
int	coin(t_vars	*vars,int new_x, int new_y,char **map)
{
	int	x;
	int	y;

	x = new_x / TILE_SIZE;
	y = new_y / TILE_SIZE;
	

	if(map[y][x] == 'C')
	{
		map[y][x] = '0';
		vars->points_collected++;
		printf("gg tas pris une piece pd va ");
		return 1;
	}	
	return (0);
}
void	draw_map(t_vars *vars)
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
				mlx_put_image_to_window(vars->mlx, vars->win, vars->mur, px,py);
			if (title == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->end, px,py);
			if (title == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->feuille, px,py);
			x++;
		}
		y++;
	}
}
void	init_player_position(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while(vars->map[y] != NULL)
	{
		x = 0;
		while(vars->map[y][x] != '\0')
		{
			if(vars->map[y][x] == 'P')
			{
				vars-> x = x * TILE_SIZE;
				vars-> y = y * TILE_SIZE;
				return;
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
 	int move_result;
	new_x = vars->x;
	new_y = vars->y;
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
	}
	else if (move_result == 2)
	{
		printf("Bienjouer");
		mlx_destroy_window(vars->mlx,vars->win);
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
	usleep(200000);                                // délai (~0.2 sec)
	return (0);
}
int	main(void)
{
	t_vars	vars;
	int		img_width;
	int		img_height;

	int win_width = 22 * TILE_SIZE;  // 7 colonnes
	int win_height = 11 * TILE_SIZE; // 5 lignes
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, win_width, win_height, "HI");
	/*vars.img =  mlx_xpm_file_to_image(vars.mlx, "back.xpm", &img_width,
			&img_height);*/
	vars.mur = mlx_xpm_file_to_image(vars.mlx, "back.xpm", &img_width,
			&img_height);
	vars.sol = mlx_xpm_file_to_image(vars.mlx, "brik.xpm", &img_width,
			&img_height);
	vars.img1 = mlx_xpm_file_to_image(vars.mlx, "zaza.xpm", &vars.perso_height,
			&vars.perso_width);
	vars.img2 = mlx_xpm_file_to_image(vars.mlx, "zaza2.xpm", &vars.perso_height,
			&vars.perso_width);
	vars.end = mlx_xpm_file_to_image(vars.mlx, "za.xpm", &img_width,
			&img_height);
	vars.feuille = mlx_xpm_file_to_image(vars.mlx, "koe.xpm", &img_width,
			&img_height);
	vars.current_frame = 0;
	vars.points_collected = 0;
	vars.x = TILE_SIZE;
	vars.y = TILE_SIZE;
	vars.map = map;
	vars.perso_height = img_height;
	vars.perso_width = img_width;
	init_player_position(&vars);
	draw_map(&vars);
	
	// mlx_key_hook(vars.win,key_touch, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_touch, &vars);
	mlx_loop(vars.mlx);
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

int	key_hook(int keycode, t_vars *vars)
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