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
RM = rm -f
SRC = initiate.c main.c parcing.c start_simulation.c time.c utils.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ) main.h
	@ar rc $(NAME) $(OBJ)
	@$(CC) $(CFLAGS) main.c $(NAME) -o philo_bonus
clean :
	@${RM} ${OBJ} ${NAME}
fclean : clean
	@${RM} philo_bonus
re : fclean all
