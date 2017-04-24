//The logic class for the gameinfo
//Also takes care of the input and output classes
#include "gameinfo.h"

int logicProcess(struct Player *player) {
  int input = getinput();
  
  if(player->isJumping == 0) {
      if(input == 2) {
            /*
                  display_string(0, "dafuq");
      display_update();
      delay(5000);*/

          //Ska spelaren kunna hoppa när denne står på en låda
          //och hur ska det se ut?
          player->jumpState = 1;
          jump(player);
      }
  } else {
      jump(player);
  }

  updateOutput(player->health);

  //Kolla om spelaren kolliderar med något och isåfall ändra health.
  //Fast kanske kan fixas på något annat håll.
  if(player->health <= 0) {
    return 0;
  }
  return 1;
}
