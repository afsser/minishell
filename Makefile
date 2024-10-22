# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nasser <nasser@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 16:58:43 by fcaldas-          #+#    #+#              #
#    Updated: 2024/10/17 21:09:03 by nasser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g3
BIN			:= ./bin/
LIB			:= ./libft/libft.a
INCLUDES	:= -I ./includes/ -I ./libft
SRCS		:= sources/expander/expand_heredoc.c \
				sources/expander/utils.c \
				sources/expander/expand_cmd.c \
				sources/expander/string_list.c \
				sources/expander/expand_string.c \
				sources/environment/env_func1.c \
				sources/environment/env_func2.c \
				sources/tokenizer/get_states.c \
				sources/tokenizer/token_states_1.c \
				sources/tokenizer/token_states_2.c \
				sources/tokenizer/tokenizer.c \
				sources/tokenizer/utils_list.c \
				sources/tokenizer/utils.c \
				sources/executor/create_argv.c \
				sources/executor/exec_and_or.c \
				sources/executor/exec_cmd_fork.c \
				sources/executor/exec_cmd.c \
				sources/executor/exec_pipe.c \
				sources/executor/exec_tree.c \
				sources/executor/fd_list.c \
				sources/executor/signals.c \
				sources/executor/signal_handler.c \
				sources/executor/signals_macros.c \
				sources/executor/utils.c \
				sources/builtin/cd.c \
				sources/builtin/echo.c \
				sources/builtin/env.c \
				sources/builtin/execution_utils.c \
				sources/builtin/execution.c \
				sources/builtin/exit.c \
				sources/builtin/export_utils.c \
				sources/builtin/export.c \
				sources/builtin/pwd.c \
				sources/builtin/unset.c \
				sources/parser/get_tree.c \
				sources/parser/here_doc.c \
				sources/parser/make_tree_cmd_recursive.c \
				sources/parser/make_tree_cmd.c \
				sources/parser/make_tree.c \
				sources/utils.c \
				sources/main.c
OBJS		:= ${SRCS:sources/%.c=bin/%.o}

# RULES

all: libft/libft.a $(NAME)

libft/libft.a:
	@make -sC ./libft

bin/%.o: sources/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $(HEADERS) $< -o $@
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME) $(LIB) -lreadline \
		&& printf "\-\-\-\- COMPILED -/-/-/-/\n"

val: readline.supp all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

readline.supp:
	@echo '{' > $@
	@echo '   ignore_libreadline_memory_errors' >> $@
	@echo '   Memcheck:Leak' >> $@
	@echo '   ...' >> $@
	@echo '   obj:*/libreadline.so.*' >> $@
	@echo '}' >> $@


clean:
	rm -rf $(BIN)
	@make clean -sC ./libft 

fclean: clean
	rm -rf $(NAME) 
	rm -rf ./libft/libft.a

bonus:

re: fclean all

.PHONY: all bonus clean fclean re val