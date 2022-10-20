NAME = philo
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
TFLAG = -lpthread
SRC = main.c ft_atoi.c routine.c init.c utils.c mutex.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(TFLAG)

clean:
	rm -f $(wildcard *.o)

fclean: clean
	rm -f $(NAME)

re: fclean all