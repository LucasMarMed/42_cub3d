# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 19:24:47 by lumarque          #+#    #+#              #
#    Updated: 2024/06/04 22:54:20 by lumarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror -g
MAKE = make -C
RM = rm -f
DN = > /dev/null

LIBFT_PATH = libft
LFLAGS = -L ${LIBFT_PATH} -lft -L -lmlx_Linux -lXext -lX11 -lm
MLX_PATH = MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

# SRC_DIRS = src src/checker src/logic src/utils src/executor src/expand src/builtins
# SRC =	$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: libmlx ${OBJ}
		@${MAKE} ${LIBFT_PATH} $(DN)
		@echo "\n $(BOLD_GREEN)Libft has been compiled!\n$(NO_COLOR)" 
		@${CC} ${OBJ} ${LFLAGS} -o ${NAME}
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
		echo "$(BOLD_YELLOW)Cloning MLX42 repository...$(NO_COLOR)"; \
		git clone $(MLX_REPO) $(MLX_PATH)$(DN); \
	fi
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build $(DN) && make -C $(MLX_PATH)/build -j4 $(DN)
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

# test2: ${NAME}
# 	@bash ./test/test2.sh

# leaks: readline.supp
# 	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --log-file=output.log ./minishell

# readline.supp:
# 	@echo "{" > readline.supp
# 	@echo "    leak readline" >> readline.supp
# 	@echo "    Memcheck:Leak" >> readline.supp
# 	@echo "    ..." >> readline.supp
# 	@echo "    fun:readline" >> readline.supp
# 	@echo "}" >> readline.supp
# 	@echo "{" >> readline.supp
# 	@echo "    leak add_history" >> readline.supp
# 	@echo "    Memcheck:Leak" >> readline.supp
# 	@echo "    ..." >> readline.supp
# 	@echo "    fun:add_history" >> readline.supp
# 	@echo "}" >> readline.supp

.PHONY: all clean fclean re test1 test2 leaks
