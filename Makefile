# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 00:49:18 by jihoolee          #+#    #+#              #
#    Updated: 2025/07/13 01:26:48 by jihoolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

AR			=	ar
ARFLAGS		=	rcs

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fPIC

RM			=	rm -rf

NAME		=	libft_malloc_$(HOSTTYPE).so
LIB_NAME	=	ft_malloc_$(HOSTTYPE)

INCLUDE_DIR	=	include

SRC_DIR		=	src
SRC			=	malloc.c \
				__allocate.c \
				__find_next_available.c \
				__get_mem_type.c \
				__get_total_allocated_bytes.c \
				__show_alloc_mem_pool.c

OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT_DIR	=	libft
LIBFT		=	libft.a

TEST_SRC	=	test/test_main.c
TEST_OBJ	=	$(TEST_SRC:.c=.o)


.PHONY: all clean fclean re test

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR) $(TEST_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test: $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o test.out $(TEST_OBJ) -L. -l$(LIB_NAME) -Wl,-rpath,. -I $(INCLUDE_DIR) -I $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFT)
	$(CC) -shared -o $@ $(OBJS) -L$(LIBFT_DIR) -lft -L$(LIBFT_DIR) -I $(INCLUDE_DIR) -I $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(LIBFT_DIR)/$(LIBFT):
	make -C $(LIBFT_DIR)


