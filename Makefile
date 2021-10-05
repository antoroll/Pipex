# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arolland <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/08 15:13:08 by arolland          #+#    #+#              #
#    Updated: 2021/09/16 16:22:40 by arolland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./utils.c \
	   ./utils2.c \
	   ./utils3.c \
	   ./paths.c \
	   ./parent_process.c \
	   ./free.c \
	   ./errors.c \

SRCS_MANDATORY = ./main.c \
				 ./processes.c \

SRCS_BONUS = bonus/main_bonus.c \
			 bonus/processes_bonus.c \
			 bonus/processes2_bonus.c \
			 bonus/here_doc_bonus.c \
			 bonus/init_bonus.c

OBJS 		= ${SRCS:.c=.o}
OBJS_B		= ${SRCS_BONUS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

CC 			= clang
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -f
NAME		= pipex
all: 		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS) ${OBJS_M}
			${CC} $(CFLAGS) -o $(NAME) $(OBJS) ${OBJS_M}

bonus:		${OBJS} ${OBJS_B}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_B}

clean:
			${RM} ${OBJS} ${OBJS_M} ${OBJS_B}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re
