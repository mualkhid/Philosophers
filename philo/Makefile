# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 15:44:00 by mualkhid          #+#    #+#              #
#    Updated: 2024/07/05 15:44:01 by mualkhid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo.a
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

RM = rm -f
SRC = utils.c initiate.c philo.c parsing.c time.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ) philo.h
	@ar rc $(NAME) $(OBJ)
	@${CC} ${CFLAGS} philo.c ${NAME} -o philo ${LDFLAGS}

clean :
	@${RM} ${OBJ} ${NAME}

fclean : clean
	@${RM} philo

re : fclean all
