SRC = main.c lexer.c get_prompt.c executer.c parsing.c \
								$(addprefix utils/, ft_atoi.c ft_calloc.c ft_itoa.c ft_split.c ft_strcmp.c ft_strjoin.c ft_strncmp.c\
     								list_operation.c ft_bzero.c ft_isdigit.c ft_putstr.c ft_strchr.c ft_strdup.c ft_strlen.c ft_substr.c)\
								$(addprefix builtin/, environment.c echo.c env.c print_help.c)

HEADER = minishell.h
NAME = minishell

OBJ = $(SRC:.c=.o)
CC = gcc
FLAGE = -Wall -Wextra -Werror 

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(NAME) : $(OBJ) 
	$(CC)  $(SRC) -lreadline -o $(NAME) 

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME) 

.PHONY: re clean fclean all