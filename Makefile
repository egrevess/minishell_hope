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

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g -std=c99

LDFLAGS	= -L$(HOME)/.brew/opt/readline/lib
CPPFLAGS = -I$(HOME)/.brew/opt/readline/include
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(OBJ) Includes/minishell.h
	@make -C ./libft
	$(CC) $(FLAGS) $(LDFLAGs) $(CPPFLAGS) -lreadline $(SRC) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

phony: fclean all re clean