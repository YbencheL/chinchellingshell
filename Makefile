NAME = minishell

SRCS = main/minishell.c \
helper_functions/helper_function_1.c helper_functions/helper_function_2.c helper_functions/helper_function_3.c \
helper_functions/helper_function_4.c helper_functions/helper_function_5.c helper_functions/helper_function_6.c helper_functions/ft_split.c \
parsing/1_first_check_quotes.c parsing/2_char_to_token_check.c parsing/parsing2.c parsing/parsing_tokens_to_cmds1.c \
tools/tool0.c tools/tool1.c tools/tool2.c tools/tool3.c tools/tool4.c \
execution/redirection_n_files.c \

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