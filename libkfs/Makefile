NAME = libkfs.a

SRC = ./memory.c ./string.c ./scroll.c ./ctype.c

OBJS = $(SRC:.c=.o)

CC = gcc

FLAG = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

HEAD = ./include

all: $(NAME)

$(NAME): $(OBJS) ./include/libkfs.h
	$(CC) $(FLAG) -c $(SRC) -I $(HEAD)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o : %.c $(HEAD)
	$(CC) $(FLAG) -c $< -o $@ -I $(HEAD)

mc: fclean all clean

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
