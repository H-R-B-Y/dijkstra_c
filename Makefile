
NAME			= dijkstra.a
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0

HEADERS			:= -I ./include

LIBFT_DIR		= ./lib/libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRCS			= dijkstra.c dijkstra_utils.c
OBJS			= ${SRCS:.c=.o}


all: $(NAME)

$(LIBFT):
		@$(MAKE) --directory $(LIBFT_DIR) all bonus

$(NAME): $(OBJS) $(LIBFT)
		@mv $(LIBFT) ./$(NAME)
		@ar rcs $(NAME) $(OBJS)

main: $(NAME)
		$(CC) $(CFLAGS) main.c $(NAME) $(HEADERS) -o main.out

debug: $(NAME)
		ar d $(NAME) dijkstra.o
		$(CC) $(CFLAGS) -c debug_dijkstra.c $(HEADERS) -o debug_dijkstra.o
		$(CC) $(CFLAGS) -c debug_print_dijkstra.c $(HEADERS) -o debug_print_dijkstra.o
		ar rcs $(NAME) debug_dijkstra.o debug_print_dijkstra.o

.o.c:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

clean:
		@rm -rf $(OBJS)
		@$(MAKE) --directory $(LIBFT_DIR) clean

fclean: clean
		@rm -rf $(NAME)
		@rm -rf $(LIBFT)
		@rm -rf ./*.out

re: fclean all

.PHONY: all, clean, fclean, re, main, debug
