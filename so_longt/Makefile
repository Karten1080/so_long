NAME = so_long

# Chemin vers la MiniLibX Linux
MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx_Linux.a

# Fichiers sources
SRC = so_long.c
OBJ = $(SRC:.c=.o)

# Compilation
CC = gcc
CFLAGS = -I$(MLX_DIR)

# Flags de linkage (ajustés pour Linux)
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
