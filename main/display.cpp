#include "main.h"
/*Display Processing*/
void Display (){
	if (displayRedraw == true){
		lcd.clear ();
		displayRedraw = false;
		lcd.setCursor (0, 0);
		lcd.print ("SET ");
		lcd.print (SET_TEMP);
		lcd.print (' ');
		lcd.print ("NOW ");
		lcd.print (TEMP);

		switch (flag){
				case 0:
					lcd.setCursor (0, 1);
					lcd.println ("    ^^FLAME^^   ");
					break;

				case 1:
					lcd.setCursor (0, 1);
					lcd.println ("   **COOLING**  ");
					break;

				case 2:
					lcd.setCursor (0, 1);
					lcd.println ("   !!ERROR!!    ");
					break;

				case 3:
					lcd.setCursor (0, 1);
					lcd.println ("   ++START++   ");
					break;
			}
		}
	}