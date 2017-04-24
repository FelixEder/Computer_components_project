// Player
#include <stdint.h>
#include <string.h>

//The struct of the player
struct Player {

  int health;
  
  //int ammo;
  int score;
  int x;
  int y;
  //int height;
  //int width;
  int jumpState; 
  int isJumping;
  uint8_t * image;

};

//Screen specific functions
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

//Function from gameInit.c
void quicksleep(int cyc);
void IO_init();

//Player specific functions
struct Player newPlayer();
void changeHealth(struct Player *player, int change);
void changeAmmo(struct Player player, int change);
void increaseScore(struct Player *player, int points);
void jump(struct Player* player);

void rungame();

// playah
/*
extern const uint8_t const player_ground[128];
extern const uint8_t const player_jump1[128];
extern const uint8_t const player_jump2[128];
*/

// ground
extern const uint8_t const ground[128];

// box
//extern const uint8_t const box[128];

extern const uint8_t const test[128];

extern char textbuffer[4][16];

extern const uint8_t const font[128*8];



/* Declare text buffer for display output */
extern char textbuffer[4][16];

//Functions relating to the logic of the game.
void delay(int);
int getinput();
void updateOutput(int value);

//Functions relating to the screen information.
void changeY(int why);

void gameover();



struct Rectangle {
	int x;
      int colX;
      int colY;
      int width;
      int height;

      uint8_t * box_image;
};

struct Rectangle newRectangle(int x);
