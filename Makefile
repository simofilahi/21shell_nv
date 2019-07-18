# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 16:07:14 by mfilahi           #+#    #+#              #
#    Updated: 2019/07/09 17:50:57 by aariss           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

OBJS_DIR = objs
LIBFT_HEADER = -I libft/
SRCS_SH_DIR = minishell/srcs
SRCS_RL_DIR = readline/srcs
SRCS_PR_DIR = minishell/srcs/parsin
INCS_RL_DIR = -I readline/includes/  $(LIBFT_HEADER)
INCS_SH_DIR = -I minishell/includes/ $(INCS_RL_DIR)
LIBS_DIR = libft/libft.a -ltermcap

SRCS_RL = $(SRCS_RL_DIR)/arrowskeys.c \
		  $(SRCS_RL_DIR)/arrowskeys_2.c \
		  $(SRCS_RL_DIR)/arrowskeys_3.c \
		  $(SRCS_RL_DIR)/copy_cut.c \
		  $(SRCS_RL_DIR)/cursor_actions.c \
		  $(SRCS_RL_DIR)/ft_readline.c \
		  $(SRCS_RL_DIR)/get_pos.c \
		  $(SRCS_RL_DIR)/history.c \
		  $(SRCS_RL_DIR)/line_editing.c \
		  $(SRCS_RL_DIR)/manipulatestring.c \
		  $(SRCS_RL_DIR)/paste.c \
		  $(SRCS_RL_DIR)/term_capios_config.c \
		  $(SRCS_RL_DIR)/srcs/write.c \
		  $(SRCS_RL_DIR)/gline.c

SRCS_SH = $(SRCS_SH_DIR)/execute.c \
		  $(SRCS_SH_DIR)/builtin_cmds.c \
		  $(SRCS_SH_DIR)/list.c \
		  $(SRCS_SH_DIR)/list_1.c \
		  $(SRCS_SH_DIR)/minishell.c \
		  $(SRCS_SH_DIR)/own_cmds.c \
		  $(SRCS_SH_DIR)/srcs.c \
		  $(SRCS_SH_DIR)/voidy.c \
		  $(SRCS_SH_DIR)/next_voidy.c \
		  $(SRCS_SH_DIR)/sec_count.c \
		  $(SRCS_SH_DIR)/darlin.c \
		  $(SRCS_SH_DIR)/recall_readline.c \

SRCS_PR = $(SRCS_PR_DIR)/extras.c \
		  $(SRCS_PR_DIR)/parsin.c \
		  $(SRCS_PR_DIR)/dollar.c \
		  $(SRCS_PR_DIR)/count.c \
		  $(SRCS_PR_DIR)/check.c

OBJECT_RL = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_RL:.c=.o)))
OBJECT_SH = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_SH:.c=.o)))
OBJECT_PR = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_PR:.c=.o)))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

BoldRed = 
BoldGreen =
BoldBlue = 
BoldYellow = 
ED = 

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJECT_RL) $(OBJECT_SH) $(OBJECT_PR)
	@make -C libft/
	@echo "$(BoldBlue)Linking...$(ED)"
	@$(CC) $(OBJECT_RL) $(OBJECT_SH) $(OBJECT_PR) $(LIBS_DIR) -o $(NAME)
	@echo "\033[1;34m                                                    ";
	@echo '      ___           ___           ___           ___       ___ ';
	@echo '     /\  \         /\__\         /\  \         /\__\     /\__\';
	@echo '    /::\  \       /:/  /        /::\  \       /:/  /    /:/  /';
	@echo '   /:/\ \  \     /:/__/        /:/\:\  \     /:/  /    /:/  / ';
	@echo '  _\:\~\ \  \   /::\  \ ___   /::\~\:\  \   /:/  /    /:/  /  ';
	@echo ' /\ \:\ \ \__\ /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/    /:/__/   ';
	@echo ' \:\ \:\ \/__/ \/__\:\/:/  / \:\~\:\ \/__/ \:\  \    \:\  \   ';
	@echo '  \:\ \:\__\        \::/  /   \:\ \:\__\    \:\  \    \:\  \  ';
	@echo '   \:\/:/  /        /:/  /     \:\ \/__/     \:\  \    \:\  \ ';
	@echo '    \::/  /        /:/  /       \:\__\        \:\__\    \:\__\';
	@echo '     \/__/         \/__/         \/__/         \/__/     \/__/';
	@echo "                                                         $(ED)";
 
$(OBJS_DIR) :
	@echo "$(BoldBlue)Creating Bins Folder...$(ED)"
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : $(SRCS_RL_DIR)/%.c
	@echo "$(BoldRed)Compiling Readline Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_RL_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_SH_DIR)/%.c
	@echo "$(BoldYellow)Compiling 21shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_PR_DIR)/%.c
	@echo "$(BoldYellow)Compiling 21shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@
clean:
	@echo "$(BoldRed)Remove Libft binaries...$(ED)"
	@make -C libft/ clean
	@echo "$(BoldRed)Remove Objs Folder...$(ED)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(BoldRed)Remove Libft Binaries & Static Library...$(ED)"
	@make -C libft/ fclean
	@echo "$(BoldRed)Remove Executable 21sh...$(ED)"
	@rm -f $(NAME)

val : re
	valgrind --leak-check=full \
	--track-origins=yes \
	./21sh
	#--log-file=valgrind-out.txt \
	 ./21sh

help :
	@echo "SRCS_RL : $(SRCS_RL)"
	@echo "OBJECT_RL : $(OBJECT_RL)"
	@echo "\n"
	@echo "SRCS_SH : $(SRCS_SH)"
	@echo "OBJECT_SH : $(OBJECT_SH)"

re: fclean all
