#include "main.h"


void setup (){
	lcd.begin ();
	lcd.backlight ();
	lcd.home ();
	lcd.print ("FIRE CONTROL");

	pinMode (VENT, OUTPUT);
	pinMode (A1, INPUT);
	pinMode (PIEZO, OUTPUT);
	pinMode (VALVE, OUTPUT);

	uiState.FLAME = digitalRead (A1);
	uiState.SET_TEMP = (float)EEPROM.read (0) / 10.0;
	delay (500);
	lcd.clear ();
	}

void loop (){
	ReadSensors ();
	Display ();
	Work ();
	Enc ();
	}
