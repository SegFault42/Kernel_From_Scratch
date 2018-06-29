NAME = kernel_SegFault42

CC = clang
ASMC = nasm
FLAG = -m32 -Weverything -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

SRCS = ./srcs/main.c ./srcs/write.c
SRC_LD = link.ld
OBJS = $(SRCS:.c=.o)
INCLUDE = -I ./include/

all:$(NAME)

$(NAME): $(OBJS) ./include/kernel.h
	make -s -C ./libft/
	$(ASMC) -f elf32 entry.s -o entry.o
	ld -m elf_i386 -T $(SRC_LD) -o $(NAME) $(OBJS) entry.o ./libft/libft.a

%.o : %.c
	$(CC) -o $@ -c $(FLAG) $<

clean:
	make -s clean -C libft
	rm -fr $(OBJS) entry.o

fclean: clean
	make -s fclean -C libft
	rm -fr $(NAME)

re: fclean all qemu
	make -s re -C libft

qemu:
	qemu-system-i386 -kernel kernel_SegFault42
