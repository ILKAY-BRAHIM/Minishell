NAME = test

HEADER = utils/utils.h

SRC = $(addprefix utils/, ft_bzero.c ft_calloc.c ft_strlen.c ft_substr.c ft_split.c) \
		$(addprefix builtins/, environment.c)

OBJM = $(SRC:.c=.o)

CC = gcc 

FLAGE = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(FLAGE) -c $< -o $@

$(NAME) : $(OBJM) $(HEADER)
	$(CC) $(FLAGE) $(SRC) -o $(NAME) -lreadline

all: $(NAME)

clean:
	rm -rf $(OBJM)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME) 

.PHONY: re clean fclean all