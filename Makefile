NAME = kernel_rabougue

CC = gcc
ASMC = nasm
FLAG = -fno-builtin -fno-exception -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs

SRC_C = main.c
SRC_S = entry.s
SRC_LD = link.ld
OBJS = main.o\
	   entry.o

all:$(NAME)

$(NAME): $(OBJS)
	$(ASMC) -f elf32 $(SRC_S) -o entry.o
	$(CC) -m32 -c $(SRC_C) -o main.o
	ld -m elf_i386 -T $(SRC_LD) -o $(NAME) $(OBJS)

clean:
	rm -fr $(OBJS)

fclean: clean
	rm -fr $(NAME)

re: fclean all
