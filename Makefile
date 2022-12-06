CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = client
NAME1 = server
INCLUDE = minitalk.h
LIB = libft/libft.a
INCLUDE_LIB = -L./libft -lft

all : $(NAME) $(NAME1)

$(NAME) : $(NAME).c $(INCLUDE) $(LIB)
	$(CC) $(FLAGS) $(INCLUDE_LIB) -o $(NAME) 

$(NAME1) : $(NAME1).c $(INCLUDE) $(LIB)
	$(CC) $(FLAGS) $(INCLUDE_LIB) -o $(NAME1)

$(LIB) :
	@make -C libft/


clean : 
	@make clean -C libft/

fclean : clean
	@make fclean -C libft/
	rm -rf $(NAME)
	rm -rf $(NAME1)
	