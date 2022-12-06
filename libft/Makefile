NAME = libft.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror

C_ROOT = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper

C_ROOT_BONUS = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

C_FILES = $(addsuffix .c, $(C_ROOT))
C_FILES_BONUS = $(addsuffix .c, $(C_ROOT_BONUS))

O_FILES = $(C_FILES:c=o)
O_FILES_BONUS = $(C_FILES_BONUS:c=o)

LIBFT = libft/libft.a

H_INCLUDES = ./libft.h

all: ${NAME}

%.o: %.c ${H_INCLUDES}
	${CC} ${C_FLAGS} -c $< -o $@

${NAME}: $(O_FILES)
	ar rc $(NAME) ${O_FILES}

bonus : $(O_FILES) $(O_FILES_BONUS) 
	ar rc $(NAME) ${O_FILES} $(O_FILES_BONUS)

clean:
	@rm -f $(O_FILES) $(O_FILES_BONUS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

test: debug
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re debug bonus