#include "main.h"
void ReadSensors (){
	FLAME = digitalRead (A1);
	static uint32_t tmr;
	if (millis () - tmr >= 800){
		tmr = millis ();
		if (sensor.readTemp ()){
			OLD_TEMP = TEMP;
			TEMP = round (sensor.getTemp ());
			if (OLD_TEMP != TEMP){
				displayRedraw = true;
				}
			}
		sensor.requestTemp ();
		}
	}