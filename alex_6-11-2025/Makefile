NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ./libft_extended
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
OBJS_DIR = objs
SRCS_DIR = srcs
SRCS = srcs/cleaner.c srcs/cleaner_helper_1.c srcs/envar_helper_1.c \
srcs/envar_helper_2.c srcs/envar_helper_3.c srcs/error_check.c srcs/expander.c \
srcs/expander_helper_1.c srcs/expander_helper_2.c srcs/expander_helper_3.c \
srcs/parser.c srcs/parser_helper_1.c srcs/parser_helper_2.c \
srcs/redir_struct_helper.c srcs/tokens_helper.c srcs/main.c srcs/debugger.c \
srcs/lexer_helper_2.c srcs/lexer.c srcs/lexer_helper_1.c srcs/lexer_helper_3.c \
srcs/redirector_helper.c srcs/redirector.c srcs/built_ins/echo.c \
srcs/built_ins/env.c srcs/built_ins/exit.c srcs/built_ins/export.c \
srcs/built_ins/pwd.c srcs/built_ins/unset.c \
srcs/executor.c srcs/executor_helper.c srcs/built_ins/cd.c srcs/signal.c 
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -lreadline -lhistory -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re