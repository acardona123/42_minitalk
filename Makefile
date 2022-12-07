CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = client
NAME1 = server
INCLUDE = minitalk.h

SRCS_CIENT = client.c ft_atoi.c
SRCS_SERV = server.c ft_putnbr_fd.c

OFILES_CLIENT = $(SRCS_CLIENT:c=o)
OFILES_SERV = $(SRCS_SERV:c=o)

all : $(NAME) $(NAME1)

%.o : %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OFILES_CLIENT) $(INCLUDE)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES_CLIENT)

$(NAME1) : $(OFILES_SERV) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME1) $(OFILES_SERV)

clean : 
	rm -rf $(OFILES_CLIENT)
	rm -rf $(OFILES_SERV)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME1)

re : fclean all

.PHONY = all clean fclean re
	