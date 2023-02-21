# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 13:06:31 by arnaud            #+#    #+#              #
#    Updated: 2023/02/21 13:09:13 by arnaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

FLAGS = -Wall -Wextra -Werror

SRC = main.c 

OBJS = $(SRC:.c=.o)

CC = gcc

RM = rm -rf

INC =  include

.c.o:
	$(CC) $(FLAGS) -I$(INC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -I$(INC) -o $(NAME) $(OBJS) 

clean:
	make clean -C libft
	$(RM) $(OBJS) $(NAME) 


fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re