// Game Init file, sets up a bunch of things

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameinfo.h"  /* Declatations for these labs */
#include <stdio.h>

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

// https://reference.digilentinc.com/_media/chipkit_shield_basic_io_shield:chipkit_basic_io_shield_rm.pdf
// page 11
void display_init(void) {

     /* We're going to be sending commands, so clear the Data/Cmd bit*/
      DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
      /* Start by turning VDD on and wait a while for the power to come up.*/
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

      /* Display off command*/
	spi_send_recv(0xAE);

      /* Bring Reset low and then high*/
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

      /* Send the Set Charge Pump and Set Pre-Charge Period commands*/
	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

      /* Turn on VCC and wait 100ms*/
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

      /* Send the commands to invert the display. This puts the display origin
      ** in the upper left corner.*/
	spi_send_recv(0xA1);    //remap columns
	spi_send_recv(0xC8);    //remap the rows


	/* Send the commands to select sequential COM configuration. This makes the
      ** display memory non-interleaved.*/
	spi_send_recv(0xDA);    //set COM configuration command
	spi_send_recv(0x20);    //sequential COM, left/right remap enabled

	/* Send Display On command*/
      spi_send_recv(0xAF);
}


//Sets up the IO of the game
void IO_init() {
	TRISD = TRISD | 0xA0;
	TRISE = TRISE & ~0xFF;
	PORTE = PORTE & ~0xFF;
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;

	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void display_image(int x, const uint8_t *data) {
	int i, j;

      // this outer for loop corresponds to the 4 rows in the icon
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

            /* Set the page address */
		spi_send_recv(0x22); // Set page command
		spi_send_recv(i); // page number

            // 0000 0001 & 1111 1111
		spi_send_recv(x & 0xF);
            // 0001 0000


            // x = 64, 0100 0000 ---- 64 >> 4 = 0000 0100
            // x = 63, 0011 1111 ----- 63 >> 4 = 0000 0011
            // x = 62, 0011 1110 ----- 62 >> 4 = 0000 0011


            // from 0x10 to 0x1F
		spi_send_recv(0x10 | ((x >> 4) & 0xF));

		DISPLAY_CHANGE_TO_DATA_MODE;

		// this inner for loop seems to corespond to the columns, behaves weird tho
            // A limit of 1 seems to be enough to display 1 line, but everything starts to move around the screen
            // 0, nothing
            // 1-3, moves around
            // 4 seems okay
            // 5-7, moves around
            // 8 seems okay
            // 12 seems okay
            // 15 moves around
            // 16 seems okay
            // 32 is the original
            for(j = 0; j < 32; j++){
			spi_send_recv(data[i*32 + j]);
            }
	}
}

void display_update(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}


