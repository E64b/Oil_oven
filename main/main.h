#pragma once

#include <stdio.h>
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

typedef struct {
uint8_t SET_TEMP = 0;
uint8_t TRY = 0;
uint8_t flag = 0;
uint8_t gis = 3;
bool displayRedraw = true;
bool WORK = false;
bool START = false;
bool ERR = false;
bool FLAME;
float TEMP = 0;
float OLD_TEMP = 0;
} UIState;

extern UIState uiState;

extern Encoder enc;
extern MicroDS18B20<2> sensor;
extern LiquidCrystal_I2C lcd;

void ReadSensors();
void Display();
void Work();
void Enc();