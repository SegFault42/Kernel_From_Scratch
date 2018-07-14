NAME = kernel_SegFault42

CC = clang
ASMC = nasm
FLAG = -m32 -Weverything -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

SRCS = ./srcs/main.c\
 	   ./srcs/write.c\
 	   ./srcs/workspace.c\
 	   ./srcs/keyboard.c

SRC_LD = link.ld
OBJS = $(SRCS:.c=.o)
INCLUDE = -I ./include/

all:$(NAME)

$(NAME): $(OBJS) ./include/kernel.h ./include/keyboard.h
	make -s -C ./libft/
	$(ASMC) -f elf32 entry.s -o entry.o
	ld -m elf_i386 -T $(SRC_LD) -o $(NAME) $(OBJS) entry.o ./libft/libft.a
	@mkdir -p kernel/boot/grub
	@/bin/cp $(NAME) kernel/boot
	@/bin/cp grub.cfg kernel/boot/grub
	@grub-mkrescue -o kernel_SegFault42.iso kernel

%.o : %.c
	$(CC) -o $@ -c $(FLAG) $<

clean:
	make -s clean -C libft
	rm -fr $(OBJS) entry.o
	rm -fr kernel

fclean: clean
	make -s fclean -C libft
	rm -fr $(NAME)
	rm -fr kernel_SegFault42.iso

re: fclean all qemu
	make -s re -C libft

qemu:
	qemu-system-i386 -kernel kernel_SegFault42
