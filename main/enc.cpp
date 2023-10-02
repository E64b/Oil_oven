#include "main.h"
/*Encoder Processing*/
void Enc (){
	enc.tick ();
	if (enc.isRight ()){
		uiState.SET_TEMP++;
		uiState.displayRedraw = true;
		}
	if (enc.isLeft ()){
		uiState.SET_TEMP--;
		uiState.displayRedraw = true;
		}
	if (enc.isRightH ()){
		uiState.SET_TEMP += 10;
		uiState.displayRedraw = true;
		}
	if (enc.isLeftH ()){
		uiState.SET_TEMP -= 10;
		uiState.displayRedraw = true;
		}
	if (enc.isClick ()){
		uiState.TRY = 0;
		uiState.START = true;
		uiState.ERR = false;
		uiState.displayRedraw = true;
		}
	if (enc.isHolded ()){
		lcd.clear ();
		EEPROM.write (0, (float)uiState.SET_TEMP * 10.0);
		lcd.home();
		lcd.print ("+SET TEMP SAVE+");
		delay (1000);
		uiState.displayRedraw = true;
		}
	}