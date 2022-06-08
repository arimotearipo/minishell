SRCS = main.c initshell.c lexer.c error.c error_utils.c list_utils.c free_utils.c tokenlength.c parser.c \
		env_utils.c expander.c expander2.c ft_substrnoquote.c export.c unset.c chdir.c \

OBJS = $(SRCS:.c=.o)

INCLUDE = -I./includes -I./libft

LINK = -L./libft -lft -lreadline

FLAGS = -Wall -Wextra -Werror -g
CC = gcc

NAME = minishell

all 	:	$(NAME)

$(NAME) :	$(OBJS)
			@make -C libft
			$(CC) $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME) $(LINK)

%.o		: 	%.c
			$(CC) $(FLAGS) $(INCLUDE) -c $<

clean 	: 
			@make clean -C libft
			rm -rf $(OBJS)

fclean 	: 	clean
			@make fclean -C libft
			rm -rf $(NAME)

re 		:	fclean $(NAME)

.PHONY: all clean fclean re