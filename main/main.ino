#include "main.h"

MicroDS18B20<2> sensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);
EncButton eb(CLK, DT, SW);

UIState uiState;

void setup(){
	lcd.init();
	lcd.backlight();
	lcd.home();
	lcd.print("FIRE CONTROL");

	pinMode(VENT, OUTPUT);
	pinMode(2, INPUT);
	pinMode(PIEZO, OUTPUT);
	pinMode(VALVE, OUTPUT);

	uiState.SET_TEMP=(float)EEPROM.read(0)/10.0;
	delay(500);
	lcd.clear();
	}

void loop(){
	ReadSensors();
	Display();
	Work();
	Enc();
	}
