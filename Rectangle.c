#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "data.h"



struct Rectangle {
	int x;
      int colX;
      int colY;
      int width;
      int height;
      uint8_t * box_image; 
};


// http://stackoverflow.com/questions/30098054/initialize-array-in-gcc-undefined-reference-to-memcpy	
struct Rectangle newRectangle(int x) {
      struct Rectangle rect;
      rect.x = x;
      rect.colX = rect.x + 7;
      rect.colY = 18;
      rect.width = rect.colX + 16;
      rect.height = rect.colY + 14;
      rect.box_image = &box;
      
      return rect;
	

}

void updateX(struct Rectangle *rect, int n){
      
      rect->x = n;
      rect->colX = rect->x + 7;
      
}