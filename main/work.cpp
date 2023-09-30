#include "main.h"
void Work (){
	/*Ignition mode*/
	if ((START == true) and (ERR == false) and (TEMP <= SET_TEMP)){
		/*If you are ready to launch, then we make 5 attempts*/
		for (TRY; TRY < 5; TRY++){
			Display ();
			displayRedraw = true;
			flag = 3;
			digitalWrite (VENT, HIGH);
			delay (1000);
			digitalWrite (VALVE, HIGH);
			delay (500);
			digitalWrite (PIEZO, HIGH);
			delay (2500);

			/*If there is no startup, turn off everything*/
			if (digitalRead (A1) == HIGH){
				digitalWrite (PIEZO, LOW);
				digitalWrite (VALVE, LOW);
				digitalWrite (VENT, LOW);
				Display ();
				}

			/*If the launch is successful, we switch to operation mode*/
			if (digitalRead (A1) == LOW){
				digitalWrite (PIEZO, LOW);
				displayRedraw = true;
				TRY = 0;
				WORK = true;
				START = false;
				Display ();
				break;
				}

			/*After 5 attempts, we turn off all performers and get into an error*/
			if (TRY >= 5){
				displayRedraw = true;
				START = false;
				flag = 2;
				digitalWrite (PIEZO, LOW);
				digitalWrite (VALVE, LOW);
				digitalWrite (VENT, LOW);
				ERR = true;
				Display ();
				break;
				}
			break;
			}
		}

	/*Operating mode*/
	if ((WORK == true) and (TEMP <= SET_TEMP)){
		flag = 0;

		/*If the fire goes out, turn off everything and fall into error*/
		if (FLAME == HIGH){
			displayRedraw = true;
			flag = 2;
			WORK = false;
			ERR = true;
			digitalWrite (PIEZO, LOW);
			digitalWrite (VALVE, LOW);
			digitalWrite (VENT, LOW);
			Display ();
			}
		}

	/* Standby mode */
/*If they are heated to the desired temperature, turn off everything and switch to the ready-to-start mode*/
	if (TEMP >= SET_TEMP + gis){
		START = true;
		flag = 1;
		WORK = false;
		digitalWrite (PIEZO, LOW);
		digitalWrite (VALVE, LOW);
		digitalWrite (VENT, LOW);
		}

	/* Error mode */
	// If there is an error, we don't try to run it anymore
	if (ERR){
		flag = 2;
		START = false;
		WORK = false;
		digitalWrite (PIEZO, LOW);
		digitalWrite (VALVE, LOW);
		digitalWrite (VENT, LOW);
		}
	}