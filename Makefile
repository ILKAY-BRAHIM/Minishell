SRC = main.c lexer.c get_prompt.c $(addprefix utils/, ft_split.c ft_strlen.c ft_substr.c)

HEADER = minishell.h
NAME = minishell

OBJ = $(SRC:.c=.o)
CC = gcc -lreadline
FLAGE = -Wall -Wextra -Werror 

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC)  $(SRC) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME) 

.PHONY: re clean fclean all