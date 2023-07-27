NAME = parser.a

CC = cc

FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

OBJECTS	= $(SOURCE:.c=.o)

RM = rm -f

HEADERS = includes/parsing.h \
			includes/get_next_line.h \
			includes/libft.h \
			../cub3D.h 


SOURCE = parser.c GNL/get_next_line.c GNL/get_next_line_utils.c \
			libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c \
			libft/ft_isprint.c libft/ft_strlen.c libft/ft_bzero.c libft/ft_itoa.c \
			libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c libft/ft_strrchr.c \
			libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_atoi.c libft/ft_calloc.c \
			libft/ft_strdup.c libft/ft_substr.c libft/ft_split.c libft/ft_free.c\
			parsing/checker_path_extention.c parsing/parser.c\
			parsing/color_parser.c parsing/map_parser.c parsing/texture_parser.c parsing/map_reading.c \
			parsing/parsing_utils.c parsing/checking_function.c

$(NAME):$(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

%.o : %.c $(HEADERS)
	@$(CC) $(FLAGS) -c $< -o $@



all: $(NAME)

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY : re clean all fclean