# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 11:37:51 by edfirmin          #+#    #+#              #
#    Updated: 2025/10/15 10:40:42 by edfirmin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC = src/main.c src/utils.c src/md5.c src/sha256.c

#FLG = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

.c.o :
	gcc $(FLG) -c $< -o ${<:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) -o $(NAME) -lm

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all