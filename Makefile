# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 00:49:18 by jihoolee          #+#    #+#              #
#    Updated: 2025/02/23 10:14:56 by jihoolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

AR			= ar
ARFLAGS		= rcs

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror


NAME		= libft_malloc_$(HOSTTYPE).so
LIB_NAME	= libft_malloc.so


$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.PHONY: all clean fclean re

all: $(NAME)
	echo $(HOSTTYPE)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) -o test test/test_main.c -L . -lft_malloc
