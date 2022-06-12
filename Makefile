SRCS = main.c initshell.c lexer.c error.c error_utils.c list_utils.c free_utils.c tokenlength.c parser.c \
		env_utils.c expander.c expander2.c ft_substrnoquote.c export.c unset.c chdir.c ft_echo.c ft_pwd.c ft_exit.c \
		execute.c updateexit.c getallpath.c redirection.c runline.c get_next_line.c \

OBJ_DIR = obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

INCLUDE = -I./includes -I./libft

LINK = -L./libft -lft -lreadline

FLAGS = -Wall -Wextra -Werror -g
CC = gcc

NAME = minishell

all 	:	$(NAME)

$(NAME) :	$(OBJS)
			@make -C libft
			$(CC) $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME) $(LINK)

$(OBJ_DIR)%.o	:	%.c
				@mkdir -p obj
				$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean 	: 
			@make clean -C libft
			rm -rf $(OBJ_DIR)

fclean 	: 	clean
			@make fclean -C libft
			rm -rf $(NAME)

re 		:	fclean $(NAME)

.PHONY: all clean fclean re