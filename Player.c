#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "data.h"
#include <stdlib.h>

struct Player {
  //Maybe a field for name?
  int health;
  int score;
  int x;
  int y;
//  int width;
//  int height;
  int jumpState;
  int isJumping;
  uint8_t * image;
};

struct Player newPlayer(){
  struct Player player;
  player.health = 8;
  //player.ammo = 5;
  player.score = 0;
  player.jumpState = 0;
  player.isJumping = 0;

  //Set these two to correct starting position
  player.x = 10;
  player.y = 16;
//  player.width = player.x + 12;
 // player.height = player.y + 16;
  player.image = &player_ground;


  return player;
}

void changeHealth(struct Player *player, int change) {
   player->health += change;
}

void changeAmmo(struct Player *player, int change) {
  /*if(player->ammo <= 8)
    player->ammo += change;*/
}

void increaseScore(struct Player *player, int points) {
  player->score += points;
}

void jump(struct Player *player) {

    switch (player->jumpState) {

    case  0 :
      player->image = player_ground;
      player->y = 16;
      player->isJumping = 0;
      break;


    case  1 :

      player->image = player_jump1;
      player->jumpState = 2;
      player->y = 8;
      player->isJumping = 1;
      break;

    case  2 :
      player->image = player_jump2;
      player->jumpState = 4;
      player->y = 0;
      break;

    case  3 :
      player->image = player_jump1;
      player->y = 8;
      player->jumpState = 0;
      break;
     
     case 4 :
      player->image = player_jump2;
      player->jumpState = 3;
      break;


  }


}
