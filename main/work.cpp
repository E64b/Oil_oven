#include "main.h"

void Work (){
	/*Ignition mode*/
	if ((uiState.START == true) and (uiState.ERR == false) and (uiState.TEMP <= uiState.SET_TEMP)){
		/*If you are ready to launch, then we make 5 attempts*/
		for (uiState.TRY; uiState.TRY < 5; uiState.TRY++){
			Display ();
			uiState.displayRedraw = true;
			uiState.flag = 3;
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
			if (digitalRead(A1) == LOW){
				digitalWrite (PIEZO, LOW);
				uiState.displayRedraw = true;
				uiState.TRY = 0;
				uiState.WORK = true;
				uiState.START = false;
				Display ();
				break;
				}

			/*After 5 attempts, we turn off all performers and get into an error*/
			if (uiState.TRY >= 5){
				uiState.displayRedraw = true;
				uiState.START = false;
				uiState.flag = 2;
				digitalWrite (PIEZO, LOW);
				digitalWrite (VALVE, LOW);
				digitalWrite (VENT, LOW);
				uiState.ERR = true;
				Display ();
				break;
				}
			break;
			}
		}

	/*Operating mode*/
	if ((uiState.WORK == true) and (uiState.TEMP <= uiState.SET_TEMP)){
		uiState.flag = 0;

		/*If the fire goes out, turn off everything and fall into error*/
		if (uiState.FLAME == HIGH){
			uiState.displayRedraw = true;
			uiState.flag = 2;
			uiState.WORK = false;
			uiState.ERR = true;
			digitalWrite (PIEZO, LOW);
			digitalWrite (VALVE, LOW);
			digitalWrite (VENT, LOW);
			Display ();
			}
		}

	/* Standby mode */
/*If they are heated to the desired temperature, turn off everything and switch to the ready-to-start mode*/
	if (uiState.TEMP >= uiState.SET_TEMP + uiState.gis){
		uiState.START = true;
		uiState.flag = 1;
		uiState.WORK = false;
		digitalWrite (PIEZO, LOW);
		digitalWrite (VALVE, LOW);
		digitalWrite (VENT, LOW);
		}

	/* Error mode */
	// If there is an error, we don't try to run it anymore
	if (uiState.ERR){
		uiState.flag = 2;
		uiState.START = false;
		uiState.WORK = false;
		digitalWrite (PIEZO, LOW);
		digitalWrite (VALVE, LOW);
		digitalWrite (VENT, LOW);
		}
	}