NAME = kernel_SegFault42

CC = gcc
ASMC = nasm
FLAG = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

SRCS = ./srcs/main.c ./srcs/write.c
SRC_LD = link.ld
OBJS = $(SRCS:.c=.o)
INCLUDE = -I ./include/

all:$(NAME)

$(NAME): $(OBJS) ./include/kernel.h
	make -s -C ./libft/
	$(ASMC) -f elf32 entry.s -o entry.o
	$(CC) -o $@ $^ $(FLAG)

	#$(CC) $(FLAG) -o $(NAME) $(SRCS) ./libft/libft.a

	#$(CC) $(FLAG) -c $(SRC_C) -o main.o
	ld -m elf_i386 -T $(SRC_LD) -o $(NAME) $(OBJS) entry.o ./libft/libft.a

%.o : %.c
	echo "lol"
	$(CC) -o $@ -c $(FLAG) $<
	#$(CC) -c $(FLAG) $< -o $@ $(INCLUDE)

clean:
	make -s clean -C libft
	rm -fr $(OBJS)

fclean: clean
	make -s fclean -C libft
	rm -fr $(NAME)

re: fclean all
	make -s re -C libft
