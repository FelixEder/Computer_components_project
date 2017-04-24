// The scrren file, handles screen outputs.

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameinfo.h"  /* Declatations for these labs */
#include "data.h"

int y = 16;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

static int change = 0;
static int speed = 2;





/* This function is called repetitively from the main program */
void screenWork(struct Player *player, struct Rectangle *rect)
{

        change += speed;



        display_image(0, ground);
        display_image(32, ground);
        display_image(64, ground);
        display_image(96, ground);



        display_image(0, player->image);


         uint8_t merge[128];

         int j = 0;
         for(j; j<128; j++){

               merge[j] = box[j];
         }


         if (rect->x >= 0){
         int n = 0 + 32 - (rect->x);


        int i = 0;
        for (i; i<n; i++){


              merge[i] |= player->image[32-n+i];
              merge[32+i] |= player->image[64-n+i];
              merge[64+i] |= player->image[96-n+i];
              merge[96+i] |= player->image[128-n+i];

        }
         }


        if (rect->x<0){


              if (change == y)
                  updateX(rect, 112);
                  //rect->x = 112;
              int n = 16;
                      int i = 0;
              for (i; i<n; i++){


                    merge[32-n+i] |= player->image[i];
                    merge[64-n+i] |= player->image[32+i];
                    merge[96-n+i] |= player->image[64+i];
                    merge[128-n+i] |= player->image[96+i];

              }



        }


       display_image(rect->x, merge);
       boxlimits(player, rect);


     if (change == y){

       if(y != 0) {
         change = 0;
         updateX(rect, rect->x-y);
         //rect->x-=y;
       } else {
        display_string(0, "ULTRA SPEEDUP REACHED");
        }
     }
  }

void changeSpeed(int n) {
  if (n <= 16)
      speed = n;


}


void boxlimits(struct Player *player, struct Rectangle *rect){

      static int jumpCollision = 0;
      static int sideCollision = 0;

   
      
      if ((player->x + 12) >= rect->colX && (player->x + 12) <= rect->width && player->y+16 > rect->colY){
            if (sideCollision == 0)
                  changeHealth(player, -1);
            
            sideCollision = 1;

      }
      else
            sideCollision = 0;


      if ((player->x + 12) <= rect->width && (player->x + 12) >= rect->colX && (player->y+15) < rect->colY){

            jumpCollision = 1;
            player->jumpState = 4;

      }
      else if (jumpCollision){
            
            //player->jumpState = 3;
            jumpCollision = 0;
            increaseScore(player, 1);

      }
            
            
      
   

      


}



