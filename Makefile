
# ------------------------------ Colors ------------------------------
BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_GREEN	=	\033[1;32m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m

# ------------------------------ Message ------------------------------
COMP_START	=	echo "\n $(BOLD_YELLOW)Make: $(NO_COLOR)Starting the compilation...\n"
READY		=	echo "\n $(BOLD_GREEN)Ready$(NO_COLOR) : The program$(BOLD_CYAN) cub3d $(NO_COLOR)has been compiled!\n"
CLEANED		=	echo "\n $(BOLD_PURPLE)Clean: $(NO_COLOR)Removed all the \".o\" files \n"
FCLEANED	=	echo "\n $(BOLD_PURPLE)Fclean: $(NO_COLOR)Removed the executables \n"

# ------------------------------ Variables ------------------------------
NAME = cub
NAME_BONUS = cub3d_bonus
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
MAKE = make -C
RM = rm -f
DN = > /dev/null

SRC_DIR = src
INCLUDE_DIR = include
UTILS_DIR = utils
LIBFT_DIR = lib/libft
MLX_DIR = lib/mlx


LIBFT_PATH = libft
LFLAGS = -L ${LIBFT_PATH} -lft
MLXFLAG = -L ${MLX_PATH} -lmlx_Linux -lbsd -lXext -lX11 -lm
MLX_PATH = minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux

SRC_DIRS = src utils
SRC =	$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

OBJ = ${SRC:.c=.o}
#OBJ_BONUS = ${SRC_BONUS:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: libmlx ${OBJ}
		@${MAKE} ${LIBFT_PATH} $(DN)
		@echo "\n $(BOLD_GREEN)Libft has been compiled!\n$(NO_COLOR)" 
		@${CC} ${OBJ} ${LFLAGS} ${MLXFLAG} -o ${NAME}
		@$(READY)

${NAME_BONUS}: ${OBJ_BONUS}
		@${MAKE} ${LIBFT_PATH} $(DN)
		@echo "\n $(BOLD_GREEN)Libft has been compiled!\n$(NO_COLOR)" 
		@${CC} ${OBJ} ${LFLAGS} -o ${NAME}
		@$(READY)

all: ${NAME}

libmlx:
	@$(COMP_START)
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "$(BOLD_YELLOW)Cloning minilibx-linux repository...$(NO_COLOR)"; \
		git clone $(MLX_REPO) $(MLX_PATH)$(DN); \
	fi
	@make -C $(MLX_PATH) $(DN)
	@echo "\n $(BOLD_GREEN)MLX has been compiled!\n$(NO_COLOR)"

bonus: $(OBJ_BONUS) $(NAME_BONUS)

clean:
	@${MAKE} ${LIBFT_PATH} clean $(DN)
	@${MAKE} ${MLX_PATH} clean $(DN)
	@${RM} ${OBJ}
	@${RM} ${OBJ_BONUS}
	@$(CLEANED)

fclean: clean
	@${MAKE} ${LIBFT_PATH} fclean $(DN)
	@${RM} ${NAME}
	@$(FCLEANED)

re: fclean all

test1: ${NAME}
	@bash ./test/test1.sh

.PHONY: all clean fclean re test1 test2 leaks
