NAME = cub3D
SOURCES =		main.c \
				load_normal.c	\
				cast_rays.c	\
				loading.c \
				startmenu.c \
				cursor.c \
				options.c \

OBJECTS = $(SOURCES:.c=.o)
CC = cc
LIBFT = libft/libft.a
MLX42 = MLX42/libmlx42.a
PARSER = parsing/parser.a

all : $(NAME)
$(NAME):$(OBJECTS)
	gcc $(OBJECTS) $(MLX42) $(PARSER) -Iinclude -lglfw -L$(shell brew --prefix glfw)/lib -I$(shell brew --prefix glfw)/include -o $(NAME)

%.o: %.c 
	@$(CC)  -c $< -o $@

clean:
	rm -f $(OBJECTS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus libft clean fclean re