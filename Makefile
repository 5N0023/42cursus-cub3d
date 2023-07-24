NAME = cub3D
SOURCES = test.c
OBJECTS = $(SOURCES:.c=.o)
CC = cc
LIBFT = libft/libft.a
MLX42 = MLX42/libmlx42.a

all : $(NAME)
$(NAME):$(OBJECTS)
	gcc test.c $(MLX42)  -Iinclude -lglfw -L$(shell brew --prefix glfw)/lib -I$(shell brew --prefix glfw)/include -o $(NAME)

%.o: %.c 
	@$(CC)  -c $< -o $@

clean:
	rm -f $(OBJECTS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus libft clean fclean re