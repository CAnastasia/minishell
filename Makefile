NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_PATH = ./includes/

INC_DIR = ./includes/minishell.h

OBJ_PATH = ./obj/

SRC_PATH = ./src/

SRC = cd \
	cd_tools \
	dollar_split \
	echo \
	env_cmd \
	exec_functions \
	input_treatment \
	main \
	print_vars \
	quotation_mark \
	setenv \
	unset \
	var_search \
	env \

GREEN = \033[0;32m

#SRC_MINISHELL = $(addprefix $(SRC_PATH), $(SRC))

#OBJ = $(SRC_MINISHELL:.c=.o)
SRC_MINISHELL = $(addprefix $(SRC_PATH),$(addsuffix .c,$(SRC)))
OBJ = $(addprefix $(OBJ_PATH),$(addsuffix .o,$(SRC)))

INC	= $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	@$(CC) $(OBJ) -o $(NAME) -L ./libft/ -lft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_DIR)
	@mkdir -p $(OBJ_PATH)
	@printf "$(GREEN)Created $@\n"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	$(MAKE) fclean -C libft


re: fclean all

.PHONY : clean fclean all re
