# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 09:54:55 by dferreir          #+#    #+#              #
#    Updated: 2023/04/27 10:22:24 by dferreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREEN		= \033[0;32m
RED 		= \033[0;31m
BOLD		= \033[1m
NORMAL		= \033[0m
UP 			= \033[A
CUT 		= \033[K

#OUTPUT
NAME		= philo

#FILES
HEADS_LIST	= philo.h
HEADS_DIR	= ./incs/
HEADS		= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIR	= ./srcs/
SRCS_FILES	= main.c utils.c check.c init.c errors.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_FILES}}

OBJS_DIR	= ./objs/
OBJS_FILES	:= ${SRCS_FILES:.c=.o}
OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS_FILES}}

#COMMANDS
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
MKDIR		= mkdir -p
RM			= rm -rf
INCS		= -I$(HEADS_DIR)

all: ${NAME}

#Compile normal executable
${NAME}: ${OBJS_DIR} ${OBJS}
	@${CC} -g ${CFLAGS} ${INCS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) created and compiled object files"
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) is ready"

#Create objects directory
${OBJS_DIR}:
	@${MKDIR} ${OBJS_DIR}

#Compile normals objects
${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@echo "$(RED)[$(BOLD)Compiling$(NORMAL)$(RED)]$(NORMAL) $<$(UP)$(CUT)"
	@${CC} -g ${CFLAGS} ${INCS} -o $@ -c $<

#Clean obj files
clean:
	@${RM} ${OBJS_DIR}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) object files deleted"

#Clean objs files and name
fclean:	clean
	@${RM} ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) deleted"

#valgrind: all
#	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all

.PHONY: all clean fclean re #valgrind
