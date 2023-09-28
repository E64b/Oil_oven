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
uint8_t value = 0;
uint8_t TRY = 0;
bool displayRedraw = true,  WORK = false;
int gis;
float TEMP = 0;
bool IGNITION = LOW, FUEL = LOW, BOOST = LOW;
uint32_t timer = 0;

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
		value++;
		displayRedraw = true;
	}
	if (enc1.isLeft()){
		value--;
		displayRedraw = true;
	}
	if (enc1.isRightH()){
		value += 10;
		displayRedraw = true;
	}
	if (enc1.isLeftH()){
		value -= 10;
		displayRedraw = true;
	}
	if (enc1.isClick()){
		WORK = true;
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
			TEMP = round(sensor.getTemp());
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
		lcd.print("YCTAH ");
		lcd.print(value);
		lcd.print(' ');
		lcd.print("TEMP");
		lcd.print(TEMP);		

		Switch(flag) 
		{
			Case 0:
			lcd.setCursor(0, 1);
			lcd.println("    ^^FLAME^^   ");
			break;

			Case 1:
			lcd.setCursor(0, 1);
			lcd.println("   **COOLING**  ");
			break;

			Case 2:
			lcd.setCursor(0, 1);
			lcd.println("   !!ERROR!!    ");
			break;
		}
	}
}

void Work(){
	/*Режим розжига*/
	if ((FLAME == LOW) and (TRY < 5) and (TEMP < value))
	{
		
	}

	/*Режим работы*/
	if (WORK)
	{

	}
	else 
	{
		IGNITION = LOW;
		FUEL = LOW;
		BOOST = LOW;
		WORK = false;
	}

if ((FLAME == LOW) and (TRY < 5) and (TEMP < value) and (WORK == true))
{
		if (FLAME == LOW && flag3 == 0)
		{
			digitalWrite(PIEZO, LOW);
			digitalWrite(VALVE, HIGH);
			digitalWrite(VENT, HIGH);
			
			flag2 = 0;
			flag1 = 0;
		}
		if (sensor1.getTemp() > (value + gis))
		{
			digitalWrite(VENT, LOW);
			digitalWrite(VALVE, LOW);
			
			flag3 = 1;
		}

		if (FLAME == HIGH && flag2 == 5)
		{
			digitalWrite(PIEZO, LOW);
			digitalWrite(VENT, LOW);
			digitalWrite(VALVE, LOW);			
		}
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
