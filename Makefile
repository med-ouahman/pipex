
COMPILER = cc # clang

COMPILER_FLAGS = -Wall -Wextra -Werror

SOURCE_FILES = pipex.c get_cmds.c add_command.c execute.c\
extract_path.c check_access.c clear.c here_doc.c write_heredoc.c clean.c error.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

BONUS_FILES = pipex_bonus.c

NAME = pipex

LIB_DIR = libft

LIBFT = libft/libft.a

RM = rm -f

%.o: %.c 
	$(COMPILER) $(COMPILER_FLAGS) -I pipex.h -c $< -o $@

$(NAME): $(OBJECT_FILES)  $(LIBFT)
	$(COMPILER) $(COMPILER_FLAGS) $(OBJECT_FILES) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

all: $(NAME)

bonus: all

clean:
	$(RM) $(OBJECT_FILES) $(BONUS_OBJECTS) 
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
