SRCS = server.c client.c ft_atoi.c ft_putnbr_fd.c
NAME = client
NAME1 = server

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME1) $(NAME)

$(NAME1) : server.o ft_putnbr_fd.o minitalk.h
	$(CC) $(CFLAGS) server.o ft_putnbr_fd.o -o server

$(NAME) : client.o ft_atoi.o minitalk.h
	$(CC) $(CFLAGS) client.o ft_atoi.o -o client

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf client server

re : fclean all

.PHONY :  all re clean fclean