#include <Arduino.h>
#include <EEPROM.h>
#include <GyverEncoder.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <microDS18B20.h>

#define CLK 6
#define DT 5
#define SW 4
#define VENT 8
#define PIEZO 9
#define VALVE 10

Encoder enc (CLK, DT, SW, TYPE2);
MicroDS18B20<2> sensor;
LiquidCrystal_I2C lcd (0x27, 16, 2);

extern Encoder enc;
extern MicroDS18B20 sensor;
extern LiquidCrystal_I2C lcd;

void ReadSensors ();
void Display ();
void Work ();
void Enc ();