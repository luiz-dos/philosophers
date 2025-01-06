NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -I.
RM		= rm -f
SRCS	= clear_sim.c error.c forks.c handle_data.c init_data.c main.c \
			monitoring.c routine.c utils.c  
			
OBJS	= ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 