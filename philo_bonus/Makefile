# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 15:45:32 by mualkhid          #+#    #+#              #
#    Updated: 2024/07/05 15:45:33 by mualkhid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus.a
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread
RM = rm -f
SRC = initiate.c philo.c parsing.c time.c utils.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ) philo_bonus.h
	@ar rc $(NAME) $(OBJ)
	@$(CC) $(CFLAGS) philo.c $(NAME) -o philo_bonus $(LDFLAGS)

clean :
	@${RM} ${OBJ} ${NAME}

fclean : clean
	@${RM} philo_bonus

re : fclean all
