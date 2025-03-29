
COMPILER = cc

COMPILER_FLAGS = -Wall -Wextra -Werror

MANDATORY_FILES = mandatory/pipex.c mandatory/execute.c mandatory/clean.c mandatory/check_access.c\
mandatory/extract_path.c mandatory/error.c mandatory/clear.c

BONUS_FILES = bonus_src/pipex_bonus.c bonus_src/write_heredoc_bonus.c bonus_src/heredoc_bonus.c\
bonus_src/execute_bonus.c bonus_src/check_access_bonus.c bonus_src/pipes_bonus.c\
bonus_src/extract_path_bonus.c bonus_src/clear_bonus.c bonus_src/error_bonus.c\
bonus_src/execute_heredoc.c

MANDATORY_OBJS = $(MANDATORY_FILES:.c=.o)

BONUS_OBJS = $(BONUS_FILES:.c=.o)


NAME = pipex

BONUS = bonus

LIB_DIR = libft

LIBFT = libft/libft.a

RM = rm -f

%.o: %.c 
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

$(NAME): $(MANDATORY_OBJS) $(LIBFT)
	$(COMPILER) $(COMPILER_FLAGS) $(MANDATORY_FILES) $(LIBFT) -o $(NAME)

$(BONUS): $(BONUS_OBJS) $(LIBFT)
	$(COMPILER) $(COMPILER_FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	@touch $(BONUS)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

all: $(NAME)

clean:
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(NAME) $(BONUS)

re: fclean all


.PHONY: all clean fclean re
