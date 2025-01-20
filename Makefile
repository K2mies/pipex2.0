#colors------------------------------------------------------------------------------
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Name------------------------------------------------
NAME					= pipex

# Directories----------------------------------------

LIBFT					= ./libft/libft.a
INC						= include/
SRC_DIR					= src/
OBJ_DIR					= obj/

#Compiler and Cflags---------------------------------

CC 						= cc
CFLAGS					= -Wall -Werror -Wextra -I
RM						= rm -f

#Source Files---------------------------------------
SRCS 					= $(SRC_DIR)pipex.c \
						$(SRC_DIR)utils.c \
#Obj Files-----------------------------------------------------------------
OBJ						= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#Build rules---------------------------------------------------------------

start:
						make all

$(LIBFT):
						make -C ./libft


all:					$(NAME)

$(NAME):				$(OBJ) $(LIBFT)
								$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

#Compile object files from source files-------------------------------------------
$(OBJ_DIR)%.o:			$(SRC_DIR)%.c
								mkdir -p $(@D)
								$(CC) $(CFLAGS) $(INC) -c $< -o $@
#Clean----------------------------------------------------------------------------
clean:
								$(RM) -r $(OBJ_DIR)
								make clean -C ./libft

fclean:					clean
								$(RM) $(NAME)
								$(RM) $(LIBFT)
								@echo "$(CYAN)pipex executable files cleaned!$(DEF_COLOR)"
								@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:						fclean all
								@echo "$(GREEN)Cleaned and rebuilt everything for pipex!$(DEF_COLOR)"

.PHONY:					start all clean fclean re
