# ══════════════════════════════════════════════════════════════════════════════
#  NOM DE L'EXÉCUTABLE
# ══════════════════════════════════════════════════════════════════════════════

NAME		= minishell

# ══════════════════════════════════════════════════════════════════════════════
#  SOURCES (architecture séparée par responsabilité)
# ══════════════════════════════════════════════════════════════════════════════

SRC			= srcs/main.c \
			  srcs/env/env.c \
			  srcs/env/env_vars.c \
			  srcs/signals/signal.c \
			  srcs/memory/cleanup.c \
			  srcs/memory/free.c \
			  srcs/exec/path.c \
			  srcs/exec/child_process.c \
			  srcs/exec/ast_exec.c \
			  srcs/exec/cmd_dispatch.c \
			  srcs/exec/exec_simple.c \
			  srcs/exec/io.c \
			  srcs/exec/pipe_left.c \
			  srcs/exec/pipe_right.c \
			  srcs/exec/redir.c \
			  srcs/exec/exec_error.c \
			  srcs/exec/builtin.c \
			  srcs/exec/builtin_echo.c \
			  srcs/exec/builtin_cd.c \
			  srcs/exec/builtin_pwd.c \
			  srcs/exec/builtin_env.c \
			  srcs/exec/builtin_export.c \
			  srcs/exec/builtin_unset.c \
			  srcs/exec/builtin_exit.c \
			  srcs/exec/builtin_hymne.c \
			  srcs/exec/builtin_utils.c \
			  srcs/parse/parsing.c \
			  srcs/parse/parser_exec.c \
			  srcs/parse/tokenize/split_count.c \
			  srcs/parse/tokenize/split.c \
			  srcs/parse/tokenize/list.c \
			  srcs/parse/syntax/check_syntax.c \
			  srcs/parse/expand/expand_utils.c \
			  srcs/parse/expand/expand_helpers.c \
			  srcs/parse/expand/expand.c \
			  srcs/parse/redir/heredoc.c \
			  srcs/parse/struct_cmd.c

# ══════════════════════════════════════════════════════════════════════════════
#  FICHIERS OBJETS
# ══════════════════════════════════════════════════════════════════════════════

OBJS		= $(SRC:.c=.o)			# Un .o par source

# ══════════════════════════════════════════════════════════════════════════════
#  LIBFT
# ══════════════════════════════════════════════════════════════════════════════

LIBFT_DIR	= ./libft/
LIBFT		= $(LIBFT_DIR)libft.a

# ══════════════════════════════════════════════════════════════════════════════
#  COMPILATEUR & FLAGS
# ══════════════════════════════════════════════════════════════════════════════

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I./includes
RM			= rm -f

# ══════════════════════════════════════════════════════════════════════════════
#  BARRE DE PROGRESSION
# ══════════════════════════════════════════════════════════════════════════════

TOT_FILES		= $(words $(SRC))
COMPILED_FILES	= 0
MESSAGE			= "Compiling: $(COMPILED_FILES)/$(TOT_FILES) ($(shell expr $(COMPILED_FILES) \* 100 / $(TOT_FILES))%)"
BAR_LEN			= 70
BAR				= $(shell expr $(COMPILED_FILES) \* $(BAR_LEN) / $(TOT_FILES))

# ══════════════════════════════════════════════════════════════════════════════
#  COULEURS & MESSAGES
# ══════════════════════════════════════════════════════════════════════════════

GREEN		= \033[32m
RED			= \033[31m
BLUE		= \033[34m
BG_BLUE		= \033[44m
ENDCOLOR	= \033[0m
BOLD		= \033[1m

END			= echo "$(GREEN)$(BOLD)✔ Compilation finished\n$(ENDCOLOR)"
CLEAN_MSG	= echo "$(RED)$(BOLD)✖ Deleting object files\n$(ENDCOLOR)"
FCLEAN_MSG	= echo "$(RED)$(BOLD)✖ Deleting program\n$(ENDCOLOR)"

# ══════════════════════════════════════════════════════════════════════════════
#  RÈGLES
# ══════════════════════════════════════════════════════════════════════════════

all:		logo $(NAME) end

logo:
			@tput setaf 5; tput bold; cat ./art/logo; echo "\n"; tput init;

end:
			@tput setaf 2; tput bold; cat ./art/end; echo "\n"; tput init;

# Compile chaque .c en .o
%.o : %.c
			@$(CC) $(CFLAGS) -c $< -o $@
			$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
			@printf "$(BLUE)%s\r\n$(ENDCOLOR)" $(MESSAGE)
			@sleep 0.1
			@printf "$(BG_BLUE)%*s$(ENDCOLOR)\r" $(BAR) " "
			@printf "\033[F"

# Compile libft silencieusement
lib:
			@$(MAKE) -C $(LIBFT_DIR) all --silent

# Édition de liens : libft + tous les .o → exécutable
$(NAME):	lib $(OBJS)
			@printf "\n\n"
			@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
			@$(END)

clean:
			@$(CLEAN_MSG)
			@$(RM) $(OBJS)
			@tput setaf 1; tput bold; cat ./art/trash; tput init;
			@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean:		clean
			@$(FCLEAN_MSG)
			@$(RM) $(NAME)
			@$(MAKE) -C $(LIBFT_DIR) fclean --silent

re:			fclean all

install-audio:
			@echo "$(BLUE)Installing audio tools...$(ENDCOLOR)"
			@sudo apt-get update && sudo apt-get install -y alsa-utils

.PHONY:		all clean fclean re lib logo end install-audio