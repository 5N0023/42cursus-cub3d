NAME = cub3D
SOURCES =		main.c \
				load_normal.c	\
				load_valorant.c \
				cast_rays.c	\
				loading.c \
				startmenu.c \
				cursor.c \
				options.c \
				textures.c \
				door.c \
				valorant.c

OBJECTS = $(SOURCES:.c=.o)
CC = cc
LIBFT = libft/libft.a
MLX42 = MLX42/libmlx42.a
PARSER = parsing/parser.a

all :  parser $(NAME)

parser:
	@make -s -C parsing

$(NAME):$(OBJECTS)
	gcc $(OBJECTS) $(MLX42) $(PARSER) -Iinclude -lglfw -L$(shell brew --prefix glfw)/lib -I$(shell brew --prefix glfw)/include -o $(NAME)

%.o: %.c 
	@$(CC)  -c $< -o $@

clean:
	make -s -C parsing clean
	rm -f $(OBJECTS)
	
fclean: clean
	make -s -C parsing fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re