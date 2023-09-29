/*Include libs*/
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

Encoder enc(CLK, DT, SW, TYPE2);
MicroDS18B20<2> sensor;             // Init sensor
LiquidCrystal_I2C lcd(0x27, 16, 2); // Init LCD

/*Init vals*/
uint8_t SET_TEMP = 0;
uint8_t TRY = 0;
bool displayRedraw = true, WORK = false, START = false, ERROR = false;
int gis = 3;
float TEMP = 0, OLD_TEMP = 0;
int flag = 0;
bool FLAME;

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.home();
  lcd.print("FIRE CONTROL");

  pinMode(VENT, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(VALVE, OUTPUT);

  delay(500);
  lcd.clear();
}

void ReadSensors() {
  FLAME = digitalRead(A1);
  static uint32_t tmr;
  if (millis() - tmr >= 800) {
    tmr = millis();
    if (sensor.readTemp()) {
      OLD_TEMP = TEMP;
      TEMP = round(sensor.getTemp());
      if (OLD_TEMP != TEMP) {
        displayRedraw = true;
      }
    }
    sensor.requestTemp();
  }
}

void Display() {
  if (displayRedraw == true) {
    lcd.clear();
    displayRedraw = false;
    lcd.setCursor(0, 0);
    lcd.print("SET ");
    lcd.print(SET_TEMP);
    lcd.print(' ');
    lcd.print("NOW ");
    lcd.print(TEMP);

    switch (flag) {
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

void Work() {
  /*Режим розжига*/
  if ((FLAME == HIGH) and (TRY < 5) and (TEMP < SET_TEMP) and  (START == true) and (ERROR = false)) {
    flag = 3;
    digitalWrite(VENT, HIGH);
    delay(1000);
    digitalWrite(VALVE, HIGH);
    delay(500);
    digitalWrite(PIEZO, HIGH);
    delay(2500); // Время на стабилизацию горения

    if (digitalRead(A1) == HIGH) // Если нет запуска, считаем попытки
    {
      TRY++;
      digitalWrite(PIEZO, LOW);
      digitalWrite(VALVE, LOW);
      digitalWrite(VENT, LOW);
    }

    if (digitalRead(A1) == LOW) // Если запуск удачный, переходим в режим работы
    {
      digitalWrite(PIEZO, LOW); // Выключаем поджиг
      displayRedraw = true;
      TRY = 0;
      WORK = true;
      START = false;
    }

    if (TRY >=
        5) // После 5 попыток, выключаем все исполнители и попадаем в ошибку
    {
      displayRedraw = true;
      START = false;
      flag = 2;
      digitalWrite(PIEZO, LOW);
      digitalWrite(VALVE, LOW);
      digitalWrite(VENT, LOW);
      ERROR = true;
    }
  }

  /*Режим работы*/
  if ((WORK == true) and (TEMP <= SET_TEMP)) {
    flag = 0;

    if (FLAME == HIGH) // Если огонь потух, выключаем все и впадаем в ошибку
    {
      displayRedraw = true;
      flag = 2;
      WORK = false;
      ERROR = true;
      digitalWrite(PIEZO, LOW);
      digitalWrite(VALVE, LOW);
      digitalWrite(VENT, LOW);
    }
  }

  /* Режим ожидания */
  if (TEMP >= SET_TEMP + gis) // Если догрели до нужной температуры, выключаем
                              // все и переходим в режим готовности к запуску
  {
    START = true;
    flag = 1;
    WORK = false;
    digitalWrite(PIEZO, LOW);
    digitalWrite(VALVE, LOW);
    digitalWrite(VENT, LOW);
  }

  /* Режим ошибки */
  if (ERROR) // Если есть ошибка, больше не пытаемся запускать
  {
    START = false;
    WORK = false;
    digitalWrite(PIEZO, LOW);
    digitalWrite(VALVE, LOW);
    digitalWrite(VENT, LOW);
  }
}

void Enc() {
  enc.tick();
  if (enc.isRight()) {
    SET_TEMP++;
    displayRedraw = true;
  }
  if (enc.isLeft()) {
    SET_TEMP--;
    displayRedraw = true;
  }
  if (enc.isRightH()) {
    SET_TEMP += 10;
    displayRedraw = true;
  }
  if (enc.isLeftH()) {
    SET_TEMP -= 10;
    displayRedraw = true;
  }
  if (enc.isClick()) {
    TRY = 0;
    START = true;
    ERROR = false;
    displayRedraw = true;
  }
}
void loop() {
  ReadSensors();
  Display();
  Work();
  Enc();
}
