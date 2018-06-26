#define VIDEO_MEM_BEGIN	0xb8000
#define VIDEO_MEM_END	0xb8FA0
#define MAX_LINES		25
#define MAX_COLUMNS		80

#define BLACK			0x00
#define BLUE			0x01
#define GREEN			0x02
#define CYAN			0x03
#define RED				0x04
#define MAGENTA			0x05
#define BROWN			0x06
#define LIGHT_GREY		0x07
#define DARK_GREY		0x08
#define LIGHT_BLUE		0x09
#define LIGHT_GREEN		0x0a
#define LIGHT_CYAN		0x0b
#define LIGHT_RED		0x0c
#define LIGHT_MAGENTA	0x0d
#define LIGHT_BROWN		0x0e
#define WHITE			0x0f

typedef char	uint8_t;
typedef short	uint16_t;
typedef int		uint32_t;
typedef long	uint64_t;
typedef long	size_t;

static void	ft_kputstr(const char *str);
static void	clear_screen(void);
static void	write_to_pos(uint8_t x, uint8_t y, const char *str);
static void	*ft_kmemmove(void *dest, const void *src, size_t n);
static void	*ft_kmemset(void *b, int c, size_t len);

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

static void	*ft_kmemset(void *b, int c, size_t len)
{
	size_t	i = 0;
	char *tmp_b = b;

	while (i < len) {
		*tmp_b++ = c;
		i++;
	}
	return (b);
}

static void	*ft_kmemmove(void *dest, const void *src, size_t n)
{
	size_t		i = 0;
	char		*tmp_dest = dest;
	const char	*tmp_src = src;

	while (i < n) {
		tmp_dest[i] = tmp_src[i];
		i++;
	}
	return (dest);
}

//this function write a character to x and y coordinate
static void	write_to_pos(uint8_t x, uint8_t y, const char *str)
{
	uint16_t pos = 0;
	char	*tmp = (char *)VIDEO_MEM_BEGIN;

	pos = ((y * MAX_COLUMNS) * 2) + (x * 2);
	while (*str) {
		tmp[pos] = *str;
		tmp[pos+1] = LIGHT_GREY;

		pos += 2;
		++str;
	}
}

static void	clear_screen(void)
{
	// this loop set the screen
	// * 2 for 2 bytes per block
	for (int j = 0; j < MAX_COLUMNS * MAX_LINES * 2; j+=2) {

		// first byte set to ' '
		vidptr[j] = '@';

		// second byte set to light grey on black screen.
		vidptr[j+1] = WHITE;
	}
}

static void	ft_kputstr(const char *str)
{
	while (*str) {
		if (vidptr == (char *)VIDEO_MEM_END) {
			// scrolling
			ft_kmemmove((char *)VIDEO_MEM_BEGIN,
 						(char *)VIDEO_MEM_BEGIN + (MAX_COLUMNS * 2),
						(MAX_COLUMNS * 2) * (MAX_LINES - 1));
			// replace cursor
			vidptr = (char *)(VIDEO_MEM_END) - (MAX_COLUMNS * 2);
			// memset to 0 last line
			ft_kmemset(vidptr, 0, MAX_COLUMNS * 2);
		}
		*vidptr++ = *str;
		*vidptr++ = GREEN;

		++str;
		for (int i = 0; i < 100000; i++) {}
	}
}

void	kmain(void)
{
	const char		*str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec elit nibh, congue nec nibh eget, ultrices pharetra velit. Suspendisse non lacus ac ante viverra dictum ut nec nisi. Suspendisse maximus ultrices nisl ac maximus. Cras mattis metus magna, sed auctor purus sodales ac. Mauris semper sollicitudin metus, id porttitor lacus accumsan vitae. Nam lobortis varius lacinia. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam pulvinar nisi arcu. Cras faucibus purus a libero volutpat rhoncus. Maecenas posuere turpis sit amet ipsum molestie laoreet. In id risus vehicula, auctor neque nec, varius felis. Vestibulum tincidunt et lectus in tempor. Pellentesque tempor commodo posuere. Integer aliquet luctus velit id ornare. Ut orci sem, vehicula pulvinar metus et, aliquet tempus mi. Nulla pharetra elit ac sapien fringilla, sed sagittis nisl pulvinar.Sed libero quam, viverra sed pretium eu, faucibus in arcu. Phasellus ornare dapibus velit vitae sodales. Donec euismod erat vel posuere vestibulum. Pellentesque interdum risus a varius placerat. Aenean posuere elit eget urna viverra luctus. In mattis mattis odio nec hendrerit. Etiam quis euismod purus. Proin in laoreet erat. Phasellus sollicitudin consectetur ligula, ut tristique massa finibus ut.Morbi cursus arcu vitae iaculis venenatis. Maecenas consequat odio ac mollis maximus. Sed magna erat, dictum eu justo vitae, luctus viverra leo. Ut lacus lectus, tincidunt ac sollicitudin eget, venenatis at libero. Vivamus ligula enim, tincidunt at quam ac, ultrices auctor augue. Praesent dignissim malesuada lorem, eget lacinia ex pretium vitae. Aliquam gravida cursus nisi, nec scelerisque enim tempus a. Donec finibus, lectus quis rhoncus consectetur, elit sapien tincidunt nulla, ac imperdiet nisi est sit amet velit. Donec sit amet sapien quam. Fusce sed porttitor quam. Cras mi libero, congue eu tincidunt at, euismod vel neque. Vivamus ultricies tellus ac malesuada ultricies. Vestibulum et commodo massa. Mauris fermentum tortor metus.";

	clear_screen();
	ft_kputstr(str);
	ft_kputstr(str);
	/*write_to_pos(2, 10, "Ramzi");*/
	/*ft_kputstr(" Je suis un con");*/
	/*ft_kmemmove((char *)VIDEO_MEM_BEGIN + (80 * 2), (char *)VIDEO_MEM_BEGIN, 11 * 2);*/

	return ;
}
