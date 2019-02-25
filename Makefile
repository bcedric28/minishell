# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcedric <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 00:11:18 by bcedric           #+#    #+#              #
#    Updated: 2019/02/21 00:11:19 by bcedric          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

FLAG = -Wall -Wextra

SOURCE = minishell.c echo.c env.c parse_inputs.c create_g_env.c erroc.c \
		setenv.c

LIBFT_DIR = Libft/

COMP_OBJ = ./obj/*.o

OBJ_DIR = ./obj
SRC_DIR = ./srcs
INCLUDE = ./includes

GGCOLORCYAN = \033[96m
GGCOLORGREEN = \033[32m
GGCOLORRED = \033[31m
GGMAG = \033[1;35m
GGRESET = \033[39m

SRC = $(addprefix $(SRC_DIR)/, $(SOURCE))
OBJ = $(addprefix $(OBJ_DIR)/, $(subst .c,.o, $(SOURCE)))

all: comp
	@mkdir -p $(OBJ_DIR)
	@make $(NAME)

comp:
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@gcc $(FLAG) $(COMP_OBJ) -I $(INCLUDE) -L $(LIBFT_DIR) -lft  -o $(NAME)
	@echo "$(GGCOLORCYAN)Creation$(GGRESET) du binaire $(GGMAG)./minishell$(GGRESET)..."
	@echo "$(GGCOLORGREEN)Success!$(GGRESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[$(GGCOLORGREEN)✔$(GGRESET)] "$(subst .c,,$<)
	@mkdir -p $(dir $@) && gcc $(FLAG) -I $(INCLUDE) -o $@ -c $<

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@echo "$(GGCOLORRED)Suppresion$(GGRESET) de ft_ls..."

re: fclean all

.PHONY: clean fclean re all