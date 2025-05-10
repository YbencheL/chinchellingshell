NAME = minishell

SRCS = main/minishell.c \
helper_functions/helper_function_1.c helper_functions/helper_function_2.c helper_functions/helper_function_3.c \
helper_functions/helper_function_4.c helper_functions/helper_function_5.c helper_functions/helper_function_6.c helper_functions/ft_split.c \
parsing/1_first_check_quotes.c parsing/2_char_to_token_check.c parsing/3_expand_fun.c parsing/4_expand_variables.c \
parsing/5_field_spliting.c parsing/6_tokenize.c parsing/7_parsing.c parsing/8_parsing.c parsing/9_check_files.c parsing/10_remove_quotes.c \
tools/tool0.c tools/tool1.c tools/tool2.c tools/tool3.c tools/tool4.c tools/tool5.c tools/tool6.c \
execution/redirection_n_files.c execution/1_handle_heredoc.c execution/get_cmd_dir.c execution/bin_pwd.c execution/bin_cd.c execution/bin_unset.c \
execution/bin_export.c execution/bin_env.c execution/bin_echo.c execution/execution.c execution/bin_exit.c  execution/excution_multip_cmd.c execution/built_in.c \
execution/update_env.c

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