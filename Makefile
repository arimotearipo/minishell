SRCS = shell.c error.c list_utils.c freeall.c \

OBJS = $(SRCS:.c=.o)

INCLUDE = -I./includes -I./libft

LINK = -L./libft -lft -lreadline

FLAGS = -Wall -Wextra -Werror -g

CC = gcc

NAME = minishell

all 	:	$(NAME)

$(NAME) :	$(OBJS)
			make -C libft
			$(CC) $(FLAGS) $(INCLUDE) $(LINK) $(OBJS) -o $(NAME)

%.o		: 	%.c
			$(CC) $(FLAGS) $(INCLUDE) -c $<

clean 	: 
			make clean -C libft
			rm -rf $(OBJS)

fclean 	: 	clean
			make fclean -C libft
			rm -rf $(NAME)

re 		:	fclean $(NAME)

.PHONY: all clean fclean re