/*Include libs*/
#include <Arduino.h>
#include <GyverEncoder.h>
#include <microDS18B20.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define CLK 6
#define DT 5 
#define SW 4 
#define VENT 8
#define PIEZO 9 
#define VALVE 10
#define digitalRead(A1) FLAME

Encoder enc1(CLK, DT, SW);
MicroDS18B20<2> sensor1;   //Init sensor
LiquidCrystal_I2C lcd(0x27, 16, 2); //Init LCD

/*Init vals*/
uint8_t SET_TEMP = 0;
uint8_t TRY = 0;
bool displayRedraw = true, WORK = false, START = false; //Флаги для мониторинга состояния 
int gis = 3;
float TEMP = 0;
bool IGNITION = LOW, FUEL = LOW, BOOST = LOW;
uint32_t timer = 0;
float OLD_TEMP = 0;

void setup(){
	lcd.begin();
	lcd.backlight();
	lcd.home();
	lcd.print("Fucking fire");

	pinMode(VENT, OUTPUT); 
	pinMode(A1, INPUT);
	pinMode(PIEZO, OUTPUT);
	pinMode(VALVE, OUTPUT);
	enc1.setType(TYPE2);
	
	delay(500);
	lcd.clear();
}

void Enc(){
	if (enc1.isRight()){
		SET_TEMP++;
		displayRedraw = true;
	}
	if (enc1.isLeft()){
		SET_TEMP--;
		displayRedraw = true;
	}
	if (enc1.isRightH()){
		SET_TEMP += 10;
		displayRedraw = true;
	}
	if (enc1.isLeftH()){
		SET_TEMP -= 10;
		displayRedraw = true;
	}
	if (enc1.isClick()){
		TRY = 0;
		START = true;
		displayRedraw = true;
	}
}

void ReadSensors(){	
	static uint32_t tmr;
	if (millis() - tmr >= 800)
	{
		tmr = millis();
		if (sensor.readTemp())
		{
			OLD_TEMP = TEMP;
			TEMP = round(sensor.getTemp());
			if (OLD_TEMP != TEMP)
			{
				displayRedraw = true;
			}
		}			
		sensor.requestTemp();
	}
}

void Display(){
	if (displayRedraw)
	{
		lcd.clear();
		displayRedraw = false;
		lcd.setCursor(0, 0);
		lcd.print("SET ");
		lcd.print(SET_TEMP);
		lcd.print(' ');
		lcd.print("NOW ");
		lcd.print(TEMP);		

		switch (flag) 
		{
			case 0:
			lcd.setCursor(0, 1);
			lcd.println("    ^^FLAME^^   ");
			break;

			case 1:
			lcd.setCursor(0, 1);
			lcd.println("   **COOLING**  ");
			break;

			case 2:
			lcd.setCursor(0, 1);
			lcd.println("   !!ERROR!!    ");
			break;

			case 3:
			lcd.setCursor(0, 1);
			lcd.println("   ++START++   ");
			break;
		}
	}
}

void Work()
{
	/*Режим розжига*/
	if ((FLAME == HIGH) and (TRY < 5) and (TEMP < SET_TEMP) and (START == true))
	{	
		flag = 3;
		TRY++;
		BOOST = HIGH;
		delay(1000);
		FUEl = HIGH;
		delay(500);
		IGNITION = HIGH;
		delay(500); //Пол секунды на устаканивание


		if (TRY >= 5)
		{
			displayRedraw = true;
			START = false;
			flag = 2;
		}

		if (FLAME == LOW)
		{
			displayRedraw = true;
			TRY = 0;
			WORK = true;
			START = false;
			IGNITION = LOW;
		}
	}

	/*Режим работы*/
	if ((WORK == true) and (TEMP <= SET_TEMP))
	{	
		flag = 0;
		FUEL = HIGH;
		BOOST = HIGH;
	
		if (FLAME == HIGH)
		{
			displayRedraw = true;
			flag = 2;
			WORK = false;
		}
	}

	/* Режим ожидания */
	if (TEMP >= SET_TEMP + gis)
	{
			flag = 1;
			IGNITION = LOW;
			FUEL = LOW;
			BOOST = LOW;
			WORK = false;
	}
}

void loop(){
	delay(100);
	/*Send command exe*/
	digitalWrite(PIEZO, IGNITION);
	digitalWrite(VALVE, FUEL);
	digitalWrite(VENT, BOOST);

	Enc();
	ReadSensors();
	Display();
	Work();		
}
