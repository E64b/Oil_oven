#include "main.h"

/*Init vals*/
uint8_t SET_TEMP = 0;
uint8_t TRY = 0;
bool displayRedraw = true, WORK = false, START = false, ERR = false, bool FLAME;
int gis = 3;
float TEMP = 0, OLD_TEMP = 0;
int flag = 0;

void setup (){
	lcd.begin ();
	lcd.backlight ();
	lcd.home ();
	lcd.print ("FIRE CONTROL");

	pinMode (VENT, OUTPUT);
	pinMode (A1, INPUT);
	pinMode (PIEZO, OUTPUT);
	pinMode (VALVE, OUTPUT);

	FLAME = digitalRead (A1);
	SET_TEMP = (float)EEPROM.read (0) / 10.0;
	delay (500);
	lcd.clear ();
	}

void loop (){
	ReadSensors ();
	Display ();
	Work ();
	Enc ();
	}
