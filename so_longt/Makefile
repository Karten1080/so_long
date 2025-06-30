NAME = so_longg

# Répertoires
MLX_DIR = ./mlx_linux
PRINTF_DIR = ./PRINTF
LIBFT = ./Libft

# Bibliothèques
MLX = $(MLX_DIR)/libmlx_Linux.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB = $(Libft)/libft.a

# Fichiers sources
SRC = so_long.c \
      map.c \
      get_next_line.c \
      get_next_line_utils.c\
	  coins.c\
	  player.c\
	  window.c\

# Objets
OBJ = $(SRC:.c=.o)

# Compilation
CC = gcc
CFLAGS = -g -I$(MLX_DIR) -I$(PRINTF_DIR)

# Flags de linkage
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Règle principale
all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(PRINTF_LIB) $(LDFLAGS)

# Build des bibliothèques
$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)
	
$(LIBFT):
	$(MAKE) -C $(LIBFT_LIB)

# Nettoyage
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re