# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 19:59:56 by jmiranda          #+#    #+#              #
#    Updated: 2023/07/12 13:46:43 by jmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = minitalk

CLIENT   = client

SERVER   = server

CC       = gcc

CFLAGS   = -Wall -Wextra -Werror

all      : ${NAME}

${NAME}  : ${CLIENT} ${SERVER}

${CLIENT}: client.c
				$(CC) $(CFLAGS) client.c -o client

${SERVER}: server.c
				$(CC) $(CFLAGS) server.c -o server

clean    :
				@rm -f ${CLIENT} ${SERVER}

fclean   : clean

re       : fclean all

.PHONY   : all bonus clean fclean re
