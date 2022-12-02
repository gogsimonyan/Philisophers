UNAME = $(shell uname -s)

NAME = phillo

CC	=	gcc

SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

FLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
