# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 22:31:19 by jihoolee          #+#    #+#              #
#    Updated: 2025/07/13 00:51:44 by jihoolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR		=	ar
ARFLAGS	=	rcs

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -fPIC

RM		=	rm -rf

NAME	=	libft.a

SRCS	=	ft_putnbr_fd.c \
			ft_putptr_fd.c \
			ft_putstr_fd.c \
			ft_strlen.c

OBJS	=	$(SRCS:.c=.o)


.PHONY: all clean fclean re

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

