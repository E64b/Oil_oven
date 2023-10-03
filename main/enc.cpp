#include "main.h"

/*Encoder Processing*/
void Enc (){
	eb.tick ();
	if (eb.right ()){
		uiState.SET_TEMP++;
		uiState.displayRedraw = true;
		}
	if (eb.left ()){
		uiState.SET_TEMP--;
		uiState.displayRedraw = true;
		}
	if (eb.rightH ()){
		uiState.SET_TEMP += 10;
		uiState.displayRedraw = true;
		}
	if (eb.leftH ()){
		uiState.SET_TEMP -= 10;
		uiState.displayRedraw = true;
		}
	if (eb.press ()){
		uiState.TRY = 0;
		uiState.START = true;
		uiState.ERR = false;
		uiState.FirstStart = true;
		uiState.displayRedraw = true;
		}
	if (eb.hold()){
		lcd.clear ();
		EEPROM.write (0, (float)uiState.SET_TEMP * 10.0);
		lcd.home ();
		lcd.print ("+SET TEMP SAVE+");
		delay (1000);
		uiState.displayRedraw = true;
		}
	}