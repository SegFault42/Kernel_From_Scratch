#define VIDEO_MEM		0xb8000
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

char	*vidptr = (char *)VIDEO_MEM;

static void	clear_screen(void)
{
	// this loop set the screen
	// * 2 for 2 bytes per block
	for (int j = 0; j < MAX_COLUMNS * MAX_LINES * 2; j+=2) {

		// first byte set to ' '
		vidptr[j] = ' ';

		// second byte set to light grey on black screen.
		vidptr[j + 1] = BLACK;
	}
}

static void	write_to_screen(const char *str)
{
	/*this loop copy str to video ptr*/
	int i, j = 0;
	while (str[j]) {

		/*copy char to video ptr*/
		vidptr[i] = str[j];

		/*set the color to char*/
		vidptr[i+1] = GREEN;

		++j;
		i += 2;
	}
}

void	kmain(void)
{
	const char		*str = "Hello world";
	unsigned int	i, j = 0;

	clear_screen();
	/*splash_screen();*/
	write_to_screen(str);

	return ;
}
