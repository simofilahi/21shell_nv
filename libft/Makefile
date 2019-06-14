# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 15:49:32 by mfilahi           #+#    #+#              #
#    Updated: 2019/05/10 13:31:13 by mfilahi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = *.c 
FLAGS = -Wextra -Werror -Wall  
HEADERS = libft.h
OBJ = $(SRCS:%.c=%.o)

BoldBlue = \033[1;34m
ED = \033[0m

all : $(NAME)

$(NAME) :
	@gcc -c $(FLAGS) $(SRCS) -I .
	@echo "$(BoldBlue)Build Static Library$(ED)"
	@ar rc $(NAME) $(OBJ)

clean : 
	@rm -f $(OBJ)

fclean : clean 
	@rm -f $(NAME)

re : fclean all
