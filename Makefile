#VARIABLES

# name and files
NAME = ft_minishell1
SRC =	ft_sh1.c 		sh_en.c			sh_error.c			sh_builtin.c\
		sh_split.c		sh_bt_setenv.c	sh_bt_unsetenv.c	sh_bt_cd.c\
		sh_getenv.c

SRCD = ./src/
OBJ = $(SRC:.c=.o)
SRCF = ${addprefix $(SRCD), $(SRC)}

# compilator
CC	= clang
CFLAGS	= -Wall -Werror -Wextra
LIB = -L libft/ -lft

#COMPILATION

all: libs $(NAME) 

libs:
	@printf "\033[1;37mcompiling: \033[4;37mlibft\e[0m\n"
	@make re -C libft
	@printf "\033[1;37m      end: \033[4;37mlibft\t\t\t\t\e[0m" "$<"
	@printf "\t\033[1;37m[✔]\033[0m\n"

# for all *.o...
#  $@=.o, @<=.c
%.o: $(SRCD)%.c
	@printf "\033[1;34mcompiling: \033[0;34m%-41s\e[0m" "$<"
	@printf "\t\033[1;34m[✔]\033[0m\n"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@printf "\033[1;32m building: \033[0;32m%-41s\e[0m" "$(NAME)"
	@printf "\t\033[1;32m[✔]\033[0m\n"
	@$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	@printf "\033[1;31m removing: \033[0;31mobjects\033[0m"
	@printf "\t\t\t\t\t\033[1;31m[X]\033[0m\n"
	@rm -f $(OBJ)

fclean: clean
	@printf "\033[1;31m removing: \033[0;31mlib file\033[0m"
	@printf "\t\t\t\t\t\033[1;31m[X]\033[0m\n"
	@rm -f $(NAME)

re: fclean all

launch: re
	./ft_minishell1
