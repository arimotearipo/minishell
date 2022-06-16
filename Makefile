SRCS_FILES = main.c initshell.c lexer.c error.c error_utils.c list_utils.c free_utils.c tokenlength.c parser.c \
			env_utils.c expander.c expander2.c ft_substrnoquote.c export.c unset.c chdir.c ft_echo.c ft_pwd.c ft_exit.c \
			exec_prog.c exec_builtin.c updateexit.c getallpath.c redirection.c runline.c get_next_line.c signalhandler.c \

OBJ_DIR = obj/

SRC_DIR = srcs/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))

SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))

INCLUDE = -I./includes -I./libft -I/usr/local/Cellar/readline/8.1.2/include

LINK = -L./libft -lft -lreadline -L/usr/local/Cellar/readline/8.1.2/lib

FLAGS = -Wall -Wextra -Werror -g
CC = gcc

NAME = minishell

all 	:	$(NAME)

$(NAME) :	$(OBJS)
			@make -C libft
			$(CC) $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME) $(LINK)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
				@mkdir -p obj
				$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean 	: 
			@make clean -C libft
			rm -rf $(OBJ_DIR)

fclean 	: 	clean
			@make fclean -C libft
			rm -rf $(NAME)

re 		:	fclean $(NAME)

m		:	all 
			./minishell

.PHONY: all clean fclean re