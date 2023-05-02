SRC = $(addprefix parsing/, main.c get_prompt.c ft_strnchr.c new_token.c parsing_v3.c  check_token.c ft_strtok.c ft_memmove.c cont_sp.c expanding.c sp_strjoin.c  free_lst.c join_tokens.c  r_qutes.c check_sp.c\
	get_part.c lexer.c join_tokens2.c free_array.c back_space.c)\
								$(addprefix utils/, ft_atoi.c ft_calloc.c ft_itoa.c ft_split.c ft_strcmp.c ft_strjoin.c ft_strncmp.c\
     								list_operation.c ft_bzero.c ft_isdigit.c ft_putstr.c ft_strchr.c ft_strdup.c ft_strlen.c ft_substr.c)\
								$(addprefix builtin/, environment.c)

HEADER = minishell.h
NAME = minishell

OBJ = $(SRC:.c=.o)
CC = gcc
FLAGE = -Wall -Wextra -Werror 
# -fsanitize=address -g
%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(NAME) : $(OBJ) 
	$(CC) $(FLAGE) $(SRC) -lreadline -o $(NAME) 

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME) 

.PHONY: re clean fclean all