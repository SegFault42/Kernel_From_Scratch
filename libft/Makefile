NAME = libft.a

SRC = ./memory.c ./string.c ./scroll.c

OBJS = $(SRC:.c=.o)

CC = clang

FLAG = -m32 -Weverything -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

HEAD = ./include

all: $(NAME)

$(NAME): $(OBJS) ./include/libft.h
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
