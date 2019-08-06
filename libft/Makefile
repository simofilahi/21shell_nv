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
CC = gcc
CFLAGS = -Wextra -Werror -Wall  
HEADERS = -I .
LIBFT_SRCS = ft_atoi.c ft_bzero.c ft_free2d.c ft_isalnum.c \
			 ft_isalpha.c ft_isascii.c ft_isblank.c ft_isdigit.c \
			 ft_islower.c ft_isprint.c ft_isspace.c ft_isupper.c \
			 ft_isxdigit.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
			 ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
			 ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
			 ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
			 ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
			 ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
			 ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
			 ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
			 ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			 ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
			 ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
			 ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
			 ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c

LIBFT_OBJS = $(LIBFT_SRCS:%.c=%.o)

BoldBlue = \033[1;34m
ED = \033[0m

all : $(NAME)

$(NAME) :
	@$(CC) -c $(CFLAGS) $(LIBFT_SRCS) $(HEADERS)
	@echo "$(BoldBlue)Build Static Library$(ED)"
	@ar rc $(NAME) $(LIBFT_OBJS)

clean :
	@rm -rf $(LIBFT_OBJS)

fclean : clean 
	@rm -f $(NAME)

re : fclean all

help :
	 @echo "LIBFT_SRCS : $(LIBFT_SRCS)\n"
	 @echo "LIBFT_OBJS : $(LIBFT_OBJS)"