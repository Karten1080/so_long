# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adel <adel@student.42.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02                                #+#    #+#              #
#    Updated: 2025/07/02                                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du programme
NAME        = so_long

# Compilateur et flags
CC          = cc
CFLAGS      = 

# Répertoires
MLX_DIR     = ./minilibx-linux
PRINTF_DIR  = ./PRINTF
LIBFT_DIR   = ./Libft

# Bibliothèques
MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

# Fichiers source et objets
SRCS        = so_long.c map.c player.c coins.c window.c get_next_line.c get_next_line_utils.c
OBJS        = $(SRCS:.c=.o)

# Flags spécifiques pour linker la MLX
LDFLAGS     = -L$(MLX_DIR) -lmlx_Linux -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft \
			  -lXext -lX11 -lm -lz

# Règle par défaut
all: $(NAME)

# Compilation du binaire
$(NAME): $(OBJS) $(MLX_LIB) $(PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compilation des librairies
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Nettoyage des objets
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

# Nettoyage complet
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild complet
re: fclean all

.PHONY: all clean fclean re
