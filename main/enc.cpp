#include "main.h"
/*Encoder Processing*/
void Enc (){
	enc.tick ();
	if (enc.isRight ()){
		SET_TEMP++;
		displayRedraw = true;
		}
	if (enc.isLeft ()){
		SET_TEMP--;
		displayRedraw = true;
		}
	if (enc.isRightH ()){
		SET_TEMP += 10;
		displayRedraw = true;
		}
	if (enc.isLeftH ()){
		SET_TEMP -= 10;
		displayRedraw = true;
		}
	if (enc.isClick ()){
		TRY = 0;
		START = true;
		ERR = false;
		displayRedraw = true;
		}
	if (enc.isHolded ()){
		lcd.clear ();
		EPROM.write (0, (float)SET_TEMP * 10.0);
		lcd.home;
		lcd.print ("+SET TEMP SAVE+");
		delay (1000);
		displayRedraw = true;
		}
	}