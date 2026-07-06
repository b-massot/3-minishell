#####################################################
#					# VARIABLES #					#
NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42

RM = rm -f

AR = ar rcs

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		ft_tolower.c ft_toupper.c \
		ft_printf.c ft_print_hex.c ft_print_ptr.c ft_print_unsigned.c \
		ft_print_utils.c get_next_line.c

SRCS_BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			 ft_lstlast.c ft_lstmap.c ft_lstnew.c  ft_lstsize.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

#####################################################
#					# RULES #			

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}

bonus: ${OBJS} ${OBJS_BONUS}
	${AR} ${NAME} ${OBJS} ${OBJS_BONUS}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
	
