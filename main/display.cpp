#include "main.h"

/*Display Processing*/
void Display(){
	if(uiState.displayRedraw==true){
		lcd.clear();
		uiState.displayRedraw=false;
		lcd.setCursor(0, 0);
		lcd.print("SET ");
		lcd.print(uiState.SET_TEMP);
		lcd.print(' ');
		lcd.print("NOW ");
		lcd.print(uiState.TEMP);

		switch(uiState.flag){
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