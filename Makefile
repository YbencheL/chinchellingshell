NAME = minishell

SRCS = main/minishell.c helper_functions/helper_function_1.c

LDFLAGS = -lreadline

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[32m🚀 Building Minishell...\033[0m"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "\033[32m✅ Build successful!\033[0m"

clean:
	@echo "\033[32m🧹 Cleaning up...\033[0m"
	rm -f $(OBJS)
	@echo "\033[32m✅ Clean complete!\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[32m✅ Full clean complete!\033[0m"

re: fclean all

.SECONDARY: $(OBJS)

.PHONY: all clean fclean re