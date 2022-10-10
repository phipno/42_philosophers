NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c ft_atoi.c routine.c init.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(wildcard *.o)

fclean: clean
	rm -f $(NAME)

re: fclean all