NAME = minishell

SRC =	src/main.c\
		src/init_shell.c\
		src/parsing/parsing.c\
		src/builtins/builtins.c \
		src/free.c\
		src/builtins/env.c\
		src/builtins/env_utils.c \
		src/builtins/echo.c\
		src/builtins/cd.c\
		src/builtins/export.c\
		src/builtins/exit.c\
		src/signal.c\
		src/command.c\
		src/builtins/export_utils.c\
		src/builtins/unset.c\
		src/pipe.c\
		src/builtins/env_sort_par.c\
		src/dollar.c\
		src/parsing/parsing_utils.c\
		src/parsing/parsing_pipe.c \
		src/pipe_utils.c\
		src/pipe_utils2.c\
		src/parsing/parsing_utils2.c\
		src/parsing/parsing_utils3.c\
		src/parsing/parsing_utils4.c\
		src/parsing/ft_count_pipe.c\





OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g -std=c99

LIBFT = ./libft/libft.a
READLINELIB = -lreadline

REMOVE = rm -f

COMPILE = gcc $(CFLAGS) -o $(NAME) -I ./lib -L. $(LIBFT) $(READLINELIB)

LDFLAGS		= -L/${HOME}/.brew/opt/readline/lib
CPPFLAGS	 = -I/${HOME}/.brew/opt/readline/include

all: $(NAME)
$(NAME): $(OBJ)
	make -C libft
	$(COMPILE) $(OBJ) ${LDFLAGS} ${CPPFLAGS} -L. $(LIBFT)


clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

phony: fclean all re clean