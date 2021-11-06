# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 09:55:51 by guilmira          #+#    #+#              #
#    Updated: 2021/11/06 13:30:47 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARGUMENTS	= 4 150 60 60
#60 150 60 60 se cuela en el menaje de muerte
#200 130 60 60 NO TIRA
#20 410 200 200
#3 300 100 100
#5 179 60 60
#5 180 60 60
#4 120 60 60 pares deberian vivir. ME FUNCIONA
#5 190 60 60
#5 130 60 60
#200 130 60 60 //creo que no deberiia morir ninguno
#número_de_filósofos	tiempo_para_morir
#tiempo_para_comer	tiempo _para_dormir
#[número_de_veces_que_cada_filósofo_debe_comer]
#--------------------------------------------------------------------------------------------------------------COMPILER
NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g -O3 -fsanitize=address
#--------------------------------------------------------------------------------------------------------------LIBS
INCLUDES	=	-I ./0includes
INCLUDES_TH	=	-pthread
#--------------------------------------------------------------------------------------------------------------SOURCES
SRCS		=	philo.c 0parser.c 1reader.c 2philo_management.c \
				3philo_routine.c 4philo_links.c 5managment.c \
				6actions.c 6actions2.c 7death_check.c 8philo_tools.c
OBJS		=	$(SRCS:.c=.o)
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
#añadir normi de header

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
#--------------------------------------------------------------------------------------------------------------FORMAT
NONE='\033[0m'
GREEN='\033[1;32m'
