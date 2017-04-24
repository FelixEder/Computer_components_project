//The input file
// Ska hantera input från button 2 och 4

#include <pic32mx.h>

/* Function checks button input and returns integer 0 if neither or
 both buttons are pressed, 1 if button 2 (other button) is pressed
 and 2 if button 4 (jump/select button) is pressed. */
int getinput() {
	int button;
	int btns = (PORTD >> 5);
	switch (btns) {
		case 1:
		case 3:
			button = 1; //Other button
			break;

		case 4:
		case 6:
			button = 2; //Jump button
			break;

		default:
			button = 0; //Neither or both
	}

	return button;
}
