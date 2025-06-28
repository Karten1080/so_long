# Nom de l'exécutable
NAME = so_long

# Répertoires
MLX_DIR = ./mlx_linux
GNL_DIR = ./GNL

# Bibliothèques
MLX = $(MLX_DIR)/libmlx_Linux.a

# Fichiers sources
SRC = so_long.c \
		map.c\
      $(GNL_DIR)/get_next_line.c \
      $(GNL_DIR)/get_next_line_utils.c \
	  

OBJ = $(SRC:.c=.o)

# Compilation
CC = gcc
CFLAGS = -g -I$(MLX_DIR) -I$(GNL_DIR)

# Flags de linkage
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Règles-Wall -Wextra -Werror 
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

.PHONY: all clean fclean re
