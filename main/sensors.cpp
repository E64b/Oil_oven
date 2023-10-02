#include "main.h"

void ReadSensors (){
	uiState.FLAME = digitalRead (A1);
	static uint32_t tmr;
	if (millis () - tmr >= 800){
		tmr = millis ();
		if (sensor.readTemp ()){
			uiState.OLD_TEMP = uiState.TEMP;
			uiState.TEMP = round (sensor.getTemp ());
			if (uiState.OLD_TEMP != uiState.TEMP){
				uiState.displayRedraw = true;
				}
			}
		sensor.requestTemp ();
		}
	}