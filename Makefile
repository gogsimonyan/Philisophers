UNAME = $(shell uname -s)

NAME = phillo

CC = cc

SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

RM = rm -f

ifeq ($(UNAME), Linux)
	CC = gcc
	LINK = -pthread
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LINK) $(CFLAGS) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
