# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 09:55:51 by guilmira          #+#    #+#              #
#    Updated: 2021/10/15 14:40:19 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARGUMENTS	= 3 3000 100 100
#número_de_filósofos	tiempo_para_morir
#tiempo_para_comer	tiempo _para_dormir
#[número_de_veces_que_cada_filósofo_debe_comer]
#--------------------------------------------------------------------------------------------------------------COMPILER
NAME		= philo
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
#--------------------------------------------------------------------------------------------------------------LIBS
INCLUDES	= -I ./0includes
INCLUDES_TH	= -pthread
#--------------------------------------------------------------------------------------------------------------SOURCES
SRCS		= philo1.c 0parser.c 8philo_tools.c
OBJS		= $(SRCS:.c=.o)
#--------------------------------------------------------------------------------------------------------------RULES
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_TH) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(INCLUDES_TH) -o $(NAME)
	@echo $(GREEN) "$(NAME) compiled" $(NONE)

exe: $(NAME)
	./$(NAME) $(ARGUMENTS)

noflags: $(OBJS)
	$(CC) $(OBJS) $(INCLUDES) $(INCLUDES_TH) -o $(NAME)
	@echo $(GREEN) "$(NAME) compiled" $(NONE)
exepure: $(noflags)
	./$(NAME) $(ARGUMENTS)

norm:
	norminette $(SRCS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
#--------------------------------------------------------------------------------------------------------------FORMAT
NONE='\033[0m'
GREEN='\033[1;32m'