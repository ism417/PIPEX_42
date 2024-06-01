CC := cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

NAME = pipex

ifdef BONUS
SRC := bonus/pipex_bonus.c bonus/utils_bonus.c bonus/exec_utils_bonus.c bonus/pars_utils_bonus.c bonus/split_utils_bonus.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
HEADER := bonus/pipex_bonus.h
else
SRC := pipex.c utils.c exec_utils.c pars_utils.c split_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
HEADER := pipex.h
endif

BONUS_SRC := bonus/pipex_bonus.c bonus/utils_bonus.c bonus/exec_utils_bonus.c bonus/pars_utils_bonus.c bonus/split_utils_bonus.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
BONUS_HEADER := bonus/pipex_bonus.h
BONUS_OBJ := $(BONUS_SRC:.c=.o)

LIBFT_H := libft/libft.h


GREEN = \033[32m
RESET = \033[0m

OBJ := $(SRC:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER) $(LIBFT_H)
	@make -C libft
	@echo "libft $(GREEN)[Done]$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "pipex $(GREEN)[Done]$(RESET)"

bonus :
	@make BONUS=1

clean :
	@make clean -C libft
	@echo "clean libft $(GREEN)[Done]$(RESET)"
	@rm -rf $(OBJ) $(BONUS_OBJ)
	@echo "clean pipex $(GREEN)[Done]$(RESET)"

fclean : clean
	@make fclean -C libft
	@echo "fclean libft $(GREEN)[Done]$(RESET)"
	@rm -rf $(NAME)
	@echo "fclean pipex $(GREEN)[Done]$(RESET)"

re : clean fclean all

.PHONY : all clean fclean bonus re