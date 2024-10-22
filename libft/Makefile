NAME = libft.a

BIN = bin

SRCS = \
	file/ft_putstr_fd.c \
	file/ft_putendl_fd.c\
	file/ft_putnbr_fd.c \
	file/ft_putchar_fd.c \
	\
	lst/ft_lstadd_back.c \
	lst/ft_lstadd_front.c\
	lst/ft_lstclear.c\
	lst/ft_lstdelone.c\
	lst/ft_lstiter.c\
	lst/ft_lstlast.c\
	lst/ft_lstmap.c\
	lst/ft_lstnew.c\
	lst/ft_lstsize.c\
	lst/ft_lstrm.c\
	lst/ft_lst_to_array.c\
	\
	mem/ft_memset.c \
	mem/ft_bzero.c \
	mem/ft_calloc.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memmove.c \
	\
	nbr/ft_atoi.c \
	nbr/ft_itoa.c \
	\
	is/ft_isprint.c \
	is/ft_isdigit.c \
	is/ft_isalnum.c \
	is/ft_isalpha.c \
	is/ft_isascii.c \
	is/ft_isspace.c \
	\
	str/ft_count_words.c \
	str/ft_strjoin.c \
	str/ft_strdup.c \
	str/ft_tolower.c \
	str/ft_strtrim.c \
	str/ft_strlcat.c \
	str/ft_substr.c \
	str/ft_strlcpy.c \
	str/ft_strlen.c \
	str/ft_toupper.c \
	str/ft_strmapi.c \
	str/ft_split.c \
	str/ft_strncmp.c \
	str/ft_strchr.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_striteri.c \
	\
	get_next_line/get_next_line.c \
	\
	ft_printf/ft_printf.c \
	\
	ft_printf/ft_putnbr_base.c \
	ft_printf/ft_printf_utils.c \
	ft_printf/ft_printptr.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(addprefix $(BIN)/, $(SRCS:%.c=%.o))

HEADER = libft.h

SUBDIRS := file lst mem nbr is str get_next_line ft_printf

BIN_SUBDIRS := $(addprefix $(BIN)/,$(SUBDIRS))

all: $(BIN) $(BIN_SUBDIRS) $(OBJS) $(NAME)

$(BIN)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@  && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(HEADER)
	@ar -rc $(NAME) $(OBJS)

$(BIN):
	@mkdir -p $(BIN)

$(BIN)/file:
	@mkdir -p $(BIN)/file

$(BIN)/lst:
	@mkdir -p $(BIN)/lst

$(BIN)/mem:
	@mkdir -p $(BIN)/mem

$(BIN)/nbr:
	@mkdir -p $(BIN)/nbr

$(BIN)/is:
	@mkdir -p $(BIN)/is

$(BIN)/str:
	@mkdir -p $(BIN)/str

$(BIN)/get_next_line:
	@mkdir -p $(BIN)/get_next_line

$(BIN)/ft_printf:
	@mkdir -p $(BIN)/ft_printf

clean:
	@rm -rf $(BIN)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
