#include "gameinfo.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>

int running = 1;

//void *sprintf = (void *) 0;
//void *stdout = (void *) 0;
FILE * const stdout = (void *)0;


void rungame(){
  int newGame = 1;
  while(newGame) {
    running = 1;
    struct Player player = newPlayer();
    struct Rectangle rect = newRectangle(96);
    int difficulty = 0;
    int speed = 4;
    changeSpeed(speed);

    display_string(0, "This is our game");
    display_string(1, "Help Stefan home");
    display_string(2, "for Christmas!");
    display_string(3, "BTN4 to jump.");
    display_update();
    delay(5000);
    
    while(running){
      //increaseScore(&player, 1);
      if(difficulty == 200) {
        speed *= 2;
        changeSpeed(speed);
        display_string(0, "    SPEEDUP");
        difficulty = 0;
      }

      
      running = logicProcess(&player);

      screenWork(&player, &rect);



      difficulty++;
      delay(100);

    }


    char score[16];
    sprintf(score, "%d", player.score);
    char highscore[32] = {};
    strcat(highscore, "Score:");
    strcat(highscore, score);
    display_string(0, "Stefan wil spend");
    display_string(1, "Christmas alone.");
    display_string(2, highscore);
    display_string(3, "BTN4:NewBTN2:End");
    display_update();
    
    while(getinput() == 0);
    int decision = getinput();
    if(decision == 1)
      newGame = 0;
  }

  display_string(0, "Thanks for playn");
  display_string(1, "You had fun and");
  display_string(2, "Stefan too!  By:");
  display_string(3, "Henrik and Felix");
  display_update();
  delay(5000);
}



void gameover(){

      running = 0;

}
