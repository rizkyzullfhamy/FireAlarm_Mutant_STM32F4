/* INCLUDE LIBRARY */
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Header.h"
#include "stdbool.h"
#include "stdio.h"
#include "LCD_Lib.h"
#include "DWT_Delay.h"
/* INITIALIZE FUNCTION */
float lowPassFilter(float dataInput, int i);
void getSensor(void);
int scanSensor(void); 
void modeSingleWire(void);
void modeCrossWire(void);
void checkSortAndOpenCircuit(void);
void checkOverCurrentSensor(void);
/* VARIABLE */
char bufferrr[100];
float data_vAdc;
float adc_lowpass;
float y[16];
float resistor = 3.3;
float vRef = 3.3;
float currentSegment[16];
float openShortCircuit[16];
float thresholdSegment[16];
int currentOverSensor = 300;
uint8_t dataSeg[16];

// =========================================== //
	 /*		NILAI 0 => AMAN
				NILAI 1 => PRE-ALARM
				NILAI 2 => ALARM/FIRE
	 */
// ========================================== //
/* ========================================== */
/* ========================================== */
/* ============== TODO HERE ================= */
/* ========================================== */
/* ========================================== */
float lowPassFilter(float dataInput, int i){
	float val1 = 0.172;
	float val2 = 0.828;

	y[i] = (val2 * y[i] ) + (val1 * dataInput);
	
	return y[i];
}
void getSensor(void){
	for(int i = 0 ; i < 16; i++){
		adc_lowpass =  lowPassFilter(adcBuffer[i], i);
		data_vAdc = (vRef * adc_lowpass) / 4095;
		currentSegment[i] = (data_vAdc / resistor) * 1000;  
	}
}

int scanSensor(void){
	int count = 0;
	bool flagScan = false;
	if(valueSetInterval <= 0) {valueSetInterval = 50;}		// DEFAULT APABILA TIDAK DIISI
	for (int i = 0; i < 16; i++){
		thresholdSegment[i] = (currentSegment[i] + valueSetInterval) * 0.9;
		openShortCircuit[i] = currentSegment[i] * 0.2; // TOLERANCE 20%
	//	if(openShortCircuit[i] < 0) openShortCircuit[i] = 0;
	}
	
	// CHECKSUM SCAN SENSOR
	for(int i=0; i  < 15; i++){
		if(openShortCircuit[i] == 0 && thresholdSegment[i] < 150) count++;
		
	}
		if(count > 15){
			LCD_Clear();
			LCD_Putsxy(0,0,"SCAN FAILED, TRY AGAIN");
			sprintf(bufferrr, "%d || %d || %d || %d || %.2f || %.2f", count ,adcBuffer[0], adcBuffer[1], adcBuffer[10], currentSegment[0], currentSegment[1]);
			LCD_Putsxy(0,1, bufferrr);
			HAL_Delay(2000);
			flagScan = false;
		}else{
			LCD_Clear();
			LCD_Putsxy(0,0,"SCAN SUCCESS"); 
			sprintf(bufferrr,"%d || op :  %.2f || %.2f || %.2f ", valueSetInterval, openShortCircuit[0], openShortCircuit[1], thresholdSegment[0]);
			LCD_Putsxy(0,1,bufferrr);
			HAL_Delay(2000);
			flagScan = true;
		}
	return flagScan;
}

// FITUR
void modeSingleWire(void){
	if(currentSegment[0] > thresholdSegment[0]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(0);
		// Data TO SCADA
		dataSeg[0] = 2;
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 1 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[0] = 0;		
	}
	if(currentSegment[1] > thresholdSegment[1]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(1);
		// Data TO SCADA
		dataSeg[1] = 2;
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 2 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[1] = 0;
	}
	if(currentSegment[2] > thresholdSegment[2]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(2);
		// Data TO SCADA
		dataSeg[2] = 2;
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 3 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[2] = 0;		
	}
	if(currentSegment[3] > thresholdSegment[3]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(3);
		// Data TO SCADA
		dataSeg[3] = 2;
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 4 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[3] = 0;		
	}
	if(currentSegment[4] > thresholdSegment[4]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(4);
		// Data TO SCADA
		dataSeg[4] = 2;	
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 5 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[4] = 0;
	}
	if(currentSegment[5] > thresholdSegment[5]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(5);
		// Data TO SCADA
		dataSeg[5] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 6 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[5] = 0;
	}
	if(currentSegment[6] > thresholdSegment[6]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(6);
		// Data TO SCADA
		dataSeg[6] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 7 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[6] = 0;		
	}
	if(currentSegment[7] > thresholdSegment[7]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(7);
		// Data TO SCADA
		dataSeg[7] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 8 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[7] = 0;	
	}
	if(currentSegment[8] > thresholdSegment[8]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(8);
		// USART TO SCADA
		dataSeg[8] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 9 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[8] = 0;	
	}
	if(currentSegment[9] > thresholdSegment[9]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(9);
		// Data TO SCADA
		dataSeg[9] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 10 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[9] = 0;		
	}
	if(currentSegment[10] > thresholdSegment[10]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(10);
		// Data TO SCADA
		dataSeg[9] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 11 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[10] = 0;			
	}
	if(currentSegment[11] > thresholdSegment[11]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(11);
		// Data TO SCADA
		dataSeg[11] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 12 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[11] = 0;			
	}
	if(currentSegment[12] > thresholdSegment[12]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(12);
		// Data TO SCADA
		dataSeg[12] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 13 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[12] = 0;			
	}
	if(currentSegment[13] > thresholdSegment[13]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(13);
		// Data TO SCADA
		dataSeg[13] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 14 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[13] = 0;	
	}
	if(currentSegment[14] > thresholdSegment[14]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(14);
		// Data TO SCADA
		dataSeg[14] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 15 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[14] = 0;	
	}
	if(currentSegment[15] > thresholdSegment[15]){
		/* FIRE ALARM ACTIVE */
		// AKTIFKAN RELAY
		relayOn(15);
		// Data TO SCADA
		dataSeg[15] = 2;		
		// PESAN KE LCD
		LCD_Clear();
		LCD_Putsxy(0,1, "Segment 16 AKTIF");
		HAL_Delay(2000);
	}else{
		/* MODE AMAN */
		dataSeg[15] = 0;	
	}
}
void modeCrossWire(void){
	/* ==================SEGMENT 1 DAN 2==================*/
	if(currentSegment[0] > thresholdSegment[0]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 1 ACTIVE");
			// DATA TO SCADA
			dataSeg[0] = 1;
			// BUZZERR BLINK
			buzzerBlink(1000);
			LCD_Clear();
		if((currentSegment[0] > thresholdSegment[0]) && (currentSegment[1] > thresholdSegment[1])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(0);
				relayOn(1);
			// DATA TO SCADA
				 dataSeg[0] = 2;
				 dataSeg[1] = 2;
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 1 & 2 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(0);
				relayOff(1);
				LCD_Clear();
		}		
	}else if(currentSegment[1] > thresholdSegment[1]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 2 ACTIVE");
			// DATA TO SCADA
			dataSeg[1] = 1;
			// BUZZERR BLINK
			buzzerBlink(1000);
			LCD_Clear();
		if((currentSegment[0] > thresholdSegment[0]) && (currentSegment[1] > thresholdSegment[1])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(0);
				relayOn(1);
			// DATA TO SCADA
				 dataSeg[0] = 2;
				 dataSeg[1] = 2;
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 1 & 2 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(0);
				relayOff(1);
				LCD_Clear();
		}
	}else if(currentSegment[0] > openShortCircuit[0] && currentSegment[0] < thresholdSegment[0]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[0] = 0;
				if(currentSegment[1] > openShortCircuit[1] && currentSegment[1] < thresholdSegment[1]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[1] = 0;
				}
	}else if(currentSegment[1] > openShortCircuit[1] && currentSegment[1] < thresholdSegment[1]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[1] = 0;		
				if(currentSegment[0] > openShortCircuit[0] && currentSegment[0] < thresholdSegment[0]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[0] = 0;
				}	
	}
	
		/* ===============SEGMENT 3 DAN 4===================== */
		if(currentSegment[2] > thresholdSegment[2]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 3 ACTIVE");
			// DATA TO SCADA
			dataSeg[2] = 1;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[2] > thresholdSegment[2]) && (currentSegment[3] > thresholdSegment[3])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(2);
				relayOn(3);
			// DATA TO SCADA
				 dataSeg[2] = 2;
				 dataSeg[3] = 2;
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 3 & 4 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(2);
				relayOff(3);
				LCD_Clear();
		}		
	}else if(currentSegment[3] > thresholdSegment[3]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();		
			LCD_Putsxy(0,1,"SEGMENT 4 ACTIVE");
			// DATA TO SCADA
			dataSeg[3] = 1;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[2] > thresholdSegment[2]) && (currentSegment[3] > thresholdSegment[3])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(2);
				relayOn(3);
			// DATA TO SCADA
				 dataSeg[2] = 2;
				 dataSeg[3] = 2;		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 3 & 4 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(2);
				relayOff(3);
				LCD_Clear();
		}
	}else if(currentSegment[2] > openShortCircuit[2] && currentSegment[2] < thresholdSegment[2]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[2] = 0;
				if(currentSegment[3] > openShortCircuit[3] && currentSegment[3] < thresholdSegment[3]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[3] = 0;
				}
	}else if(currentSegment[3] > openShortCircuit[3] && currentSegment[3] < thresholdSegment[3]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[3] = 0;		
				if(currentSegment[2] > openShortCircuit[2] && currentSegment[2] < thresholdSegment[2]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[2] = 0;
				}	
	}
	/* ===============SEGMENT 5 DAN 6===================== */
		if(currentSegment[4] > thresholdSegment[4]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();	
			LCD_Putsxy(0,1,"SEGMENT 5 ACTIVE");
			// DATA TO SCADA
			dataSeg[4] = 1;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[4] > thresholdSegment[4]) && (currentSegment[5] > thresholdSegment[5])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(4);
				relayOn(5);
			// DATA TO SCADA
				 dataSeg[4] = 2;
				 dataSeg[5] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 5 & 6 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(4);
				relayOff(5);
				LCD_Clear();
		}		
	}else if(currentSegment[5] > thresholdSegment[5]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 6 ACTIVE");
			// DATA TO SCADA
			dataSeg[5] = 1;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[4] > thresholdSegment[4]) && (currentSegment[5] > thresholdSegment[5])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(4);
				relayOn(5);
			// DATA TO SCADA
				 dataSeg[4] = 2;
				 dataSeg[5] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 5 & 6 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(4);
				relayOff(5);
				LCD_Clear();				
		}
	}else if(currentSegment[4] > openShortCircuit[4] && currentSegment[4] < thresholdSegment[4]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[4] = 0;
				if(currentSegment[5] > openShortCircuit[5] && currentSegment[5] < thresholdSegment[5]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[5] = 0;
				}
	}else if(currentSegment[5] > openShortCircuit[5] && currentSegment[5] < thresholdSegment[5]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[5] = 0;		
				if(currentSegment[4] > openShortCircuit[4] && currentSegment[4] < thresholdSegment[4]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[4] = 0;
				}	
	}
	
	/* ===============SEGMENT 7 DAN 8===================== */
		if(currentSegment[6] > thresholdSegment[6]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 7 ACTIVE");
			// DATA TO SCADA
			dataSeg[6] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[6] > thresholdSegment[6]) && (currentSegment[7] > thresholdSegment[7])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(6);
				relayOn(7);
			// DATA TO SCADA
				 dataSeg[6] = 2;
				 dataSeg[7] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 7 & 8 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(6);
				relayOff(7);
				LCD_Clear();
		}		
	}else if(currentSegment[7] > thresholdSegment[7]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();		
			LCD_Putsxy(0,1,"SEGMENT 8 ACTIVE");
			// DATA TO SCADA
			dataSeg[7] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[6] > thresholdSegment[6]) && (currentSegment[7] > thresholdSegment[7])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(6);
				relayOn(7);
			// DATA TO SCADA
				 dataSeg[6] = 2;
				 dataSeg[7] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 7 & 8 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(6);
				relayOff(7);
			  LCD_Clear();
		}
	}else if(currentSegment[6] > openShortCircuit[6] && currentSegment[6] < thresholdSegment[6]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[6] = 0;
				if(currentSegment[7] > openShortCircuit[7] && currentSegment[7] < thresholdSegment[7]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[7] = 0;
				}
	}else if(currentSegment[7] > openShortCircuit[7] && currentSegment[7] < thresholdSegment[7]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[7] = 0;		
				if(currentSegment[6] > openShortCircuit[6] && currentSegment[6] < thresholdSegment[6]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[6] = 0;
				}	
	}
	
	/* ===============SEGMENT 9 DAN 10===================== */
		if(currentSegment[8] > thresholdSegment[8]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();		
			LCD_Putsxy(0,1,"SEGMENT 9 ACTIVE");
			// DATA TO SCADA
			dataSeg[8] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();		
		if((currentSegment[8] > thresholdSegment[8]) && (currentSegment[9] > thresholdSegment[9])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(8);
				relayOn(9);
			// DATA TO SCADA
				 dataSeg[8] = 2;
				 dataSeg[9] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 9 & 10 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(8);
				relayOff(9);
			  LCD_Clear();		
		}		
	}else if(currentSegment[9] > thresholdSegment[9]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();		
			LCD_Putsxy(0,1,"SEGMENT 10 ACTIVE");
			// DATA TO SCADA
			dataSeg[9] = 2;		
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();		
		if((currentSegment[8] > thresholdSegment[8]) && (currentSegment[9] > thresholdSegment[9])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(8);
				relayOn(9);
			// DATA TO SCADA
				 dataSeg[8] = 2;
				 dataSeg[9] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 9 & 10 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(8);
				relayOff(9);
			  LCD_Clear();		
		}
	}else if(currentSegment[8] > openShortCircuit[8] && currentSegment[8] < thresholdSegment[8]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[8] = 0;
				if(currentSegment[9] > openShortCircuit[9] && currentSegment[9] < thresholdSegment[9]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[9] = 0;
				}
	}else if(currentSegment[9] > openShortCircuit[9] && currentSegment[9] < thresholdSegment[9]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[9] = 0;		
				if(currentSegment[8] > openShortCircuit[8] && currentSegment[8] < thresholdSegment[8]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[8] = 0;
				}	
	}
	
	/* ===============SEGMENT 11 DAN 12===================== */
		if(currentSegment[10] > thresholdSegment[10]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 11 ACTIVE");
			// DATA TO SCADA
				 dataSeg[10] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[10] > thresholdSegment[10]) && (currentSegment[11] > thresholdSegment[11])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(10);
				relayOn(11);
			// DATA TO SCADA
				 dataSeg[10] = 2;
				 dataSeg[11] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 11 & 12 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(10);
				relayOff(11);
			  LCD_Clear();
		}		
	}else if(currentSegment[11] > thresholdSegment[11]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 12 ACTIVE");
			// DATA TO SCADA
				 dataSeg[11] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[10] > thresholdSegment[10]) && (currentSegment[11] > thresholdSegment[11])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(10);
				relayOn(11);
			// DATA TO SCADA
				 dataSeg[10] = 2;
				 dataSeg[11] = 2;			
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 11 & 12 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(10);
				relayOff(11);
			  LCD_Clear();
		}
	}else if(currentSegment[10] > openShortCircuit[10] && currentSegment[10] < thresholdSegment[10]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[10] = 0;
				if(currentSegment[11] > openShortCircuit[11] && currentSegment[11] < thresholdSegment[11]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[11] = 0;
				}
	}else if(currentSegment[11] > openShortCircuit[11] && currentSegment[11] < thresholdSegment[11]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[11] = 0;		
				if(currentSegment[10] > openShortCircuit[10] && currentSegment[10] < thresholdSegment[10]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[10] = 0;
				}	
	}
	
	/* ===============SEGMENT 13 DAN 14===================== */
		if(currentSegment[12] > thresholdSegment[13]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 13 ACTIVE");
			// DATA TO SCADA
				 dataSeg[12] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[12] > thresholdSegment[12]) && (currentSegment[13] > thresholdSegment[13])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(12);
				relayOn(13);
			// DATA TO SCADA
				 dataSeg[12] = 2;
				 dataSeg[13] = 2;		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 13 & 14 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(12);
				relayOff(13);
			  LCD_Clear();
		}		
	}else if(currentSegment[13] > thresholdSegment[13]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 14 ACTIVE");
			// DATA TO SCADA
				 dataSeg[13] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[12] > thresholdSegment[12]) && (currentSegment[13] > thresholdSegment[13])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(12);
				relayOn(13);
			// DATA TO SCADA
				 dataSeg[12] = 2;
				 dataSeg[13] = 2;		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 11 & 12 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(12);
				relayOff(13);
			  LCD_Clear();
		}
	}else if(currentSegment[12] > openShortCircuit[12] && currentSegment[12] < thresholdSegment[12]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[12] = 0;
				if(currentSegment[13] > openShortCircuit[13] && currentSegment[13] < thresholdSegment[13]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[13] = 0;
				}
	}else if(currentSegment[13] > openShortCircuit[13] && currentSegment[13] < thresholdSegment[13]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[13] = 0;		
				if(currentSegment[12] > openShortCircuit[12] && currentSegment[12] < thresholdSegment[12]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[12] = 0;
				}	
	}
	
	/* ===============SEGMENT 15 DAN 16===================== */
		if(currentSegment[14] > thresholdSegment[14]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 15 ACTIVE");
			// DATA TO SCADA
				 dataSeg[14] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[14] > thresholdSegment[14]) && (currentSegment[15] > thresholdSegment[15])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(14);
				relayOn(15);
			// DATA TO SCADA
				 dataSeg[14] = 2;
				 dataSeg[15] = 2;		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 15 & 16 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(14);
				relayOff(15);
			  LCD_Clear();
		}		
	}else if(currentSegment[15] > thresholdSegment[15]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0,1,"SEGMENT 16 ACTIVE");
			// DATA TO SCADA
				 dataSeg[15] = 2;
			// BUZZERR BLINK
			buzzerBlink(2000);
			LCD_Clear();
		if((currentSegment[14] > thresholdSegment[14]) && (currentSegment[15] > thresholdSegment[15])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(14);
				relayOn(15);
			// DATA TO SCADA
				 dataSeg[14] = 2;
				 dataSeg[15] = 2;	
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 15 & 16 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(14);
				relayOff(15);
			  LCD_Clear();
		}
	}else if(currentSegment[14] > openShortCircuit[14] && currentSegment[14] < thresholdSegment[14]){
				/* KONDISI AMAN SEGMENT 1*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[14] = 0;
				if(currentSegment[15] > openShortCircuit[15] && currentSegment[15] < thresholdSegment[15]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[15] = 0;
				}
	}else if(currentSegment[15] > openShortCircuit[15] && currentSegment[15] < thresholdSegment[15]){
				/* KONDISI AMAN SEGMENT 2*/
				LCD_Clear();
				// DATA TO SCADA
				 dataSeg[15] = 0;		
				if(currentSegment[14] > openShortCircuit[14] && currentSegment[14] < thresholdSegment[14]){
					/* KONDISI AMAN SEGMENT 1*/
					LCD_Clear();
				  // DATA TO SCADA
				  dataSeg[14] = 0;
				}	
	}
	
}
void checkSortAndOpenCircuit(void){
	/* CHECK SHORT CIRCUIT */
	if((currentSegment[0] <= 0) && (currentSegment[1] <= 0) && (currentSegment[2] <= 0) 
		&& (currentSegment[3] <= 0) && (currentSegment[4] <= 0) && (currentSegment[5] <= 0)
		&& (currentSegment[6] <= 0) && (currentSegment[7] <= 0) && (currentSegment[8] <= 0)
		&& (currentSegment[9] <= 0) && (currentSegment[10] <= 0) && (currentSegment[11] <= 0)
	  && (currentSegment[12] <= 0) && (currentSegment[13] <= 0) && (currentSegment[14] <= 0)
	  && (currentSegment[15] <= 0)){
		// PESASN KE LCD
		LCD_Putsxy(0,1, "SENSOR =>SHORT CIRCUIT");
		// BUZZER NOTIF
		buzzerBlink(1000);
		LCD_Clear();
	}
	/* CHECK OPEN CIRCUIT */
	else if(currentSegment[0] < openShortCircuit[0]){
			/* OPEN CIRCUIT SEGMENT 1 */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 1");	
			// BUZZER NOTIF
			buzzerBlink(1000);
			LCD_Clear();
	}else if(currentSegment[1] < openShortCircuit[1]){
			/* OPEN CIRCUIT SEGMENT 2 */
			// PESAN KE LCD
			LCD_Clear();
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 2");	
			// BUZZER NOTIF
			buzzerBlink(1000);
			LCD_Clear();
	}
}
void backupopen(void){
	if(currentSegment[2] < openShortCircuit[2]){
			/* OPEN CIRCUIT SEGMENT 3 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 3");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[3] < openShortCircuit[3]){
			/* OPEN CIRCUIT SEGMENT 4 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 4");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[4] < openShortCircuit[4]){
			/* OPEN CIRCUIT SEGMENT 5 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 5");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[5] < openShortCircuit[5]){
			/* OPEN CIRCUIT SEGMENT 6 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 6");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[6] < openShortCircuit[6]){
			/* OPEN CIRCUIT SEGMENT 7 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 7");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[7] < openShortCircuit[7]){
			/* OPEN CIRCUIT SEGMENT 8 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 8");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[8] < openShortCircuit[8]){
			/* OPEN CIRCUIT SEGMENT 9 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 9");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[9] < openShortCircuit[9]){
			/* OPEN CIRCUIT SEGMENT 10 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 10");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[10] < openShortCircuit[10]){
			/* OPEN CIRCUIT SEGMENT 11 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 11");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[11] < openShortCircuit[11]){
			/* OPEN CIRCUIT SEGMENT 12 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 12");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[12] < openShortCircuit[12]){
			/* OPEN CIRCUIT SEGMENT 13 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 13");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[13] < openShortCircuit[13]){
			/* OPEN CIRCUIT SEGMENT 14 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 14");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[14] < openShortCircuit[14]){
			/* OPEN CIRCUIT SEGMENT 15 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 15");	
			// BUZZER NOTIF
			buzzerBlink(2000);		
	}else if(currentSegment[15] < openShortCircuit[15]){
			/* OPEN CIRCUIT SEGMENT 16 */
			// PESAN KE LCD
			LCD_Putsxy(0, 1, "OPEN CIRCUIT SEG 16");	
			// BUZZER NOTIF
			buzzerBlink(2000);				
	}
	
	
	/* BACKUP MODE CROSS WIRE */
		/* ===============SEGMENT 3 DAN 4===================== */
		if(currentSegment[2] > thresholdSegment[2]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 3 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[2] > thresholdSegment[2]) && (currentSegment[3] > thresholdSegment[3])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(2);
				relayOn(3);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 3 & 4 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(2);
				relayOff(3);
		}		
	}else if(currentSegment[3] > thresholdSegment[3]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 4 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[2] > thresholdSegment[2]) && (currentSegment[3] > thresholdSegment[3])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(2);
				relayOn(3);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 3 & 4 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(2);
				relayOff(3);
		}
	}
	/* ===============SEGMENT 5 DAN 6===================== */
		if(currentSegment[4] > thresholdSegment[4]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 5 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[4] > thresholdSegment[4]) && (currentSegment[5] > thresholdSegment[5])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(4);
				relayOn(5);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 5 & 6 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(4);
				relayOff(5);
		}		
	}else if(currentSegment[5] > thresholdSegment[5]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 6 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[4] > thresholdSegment[4]) && (currentSegment[5] > thresholdSegment[5])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(4);
				relayOn(5);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 5 & 6 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(4);
				relayOff(5);
		}
	}
	/* ===============SEGMENT 7 DAN 8===================== */
		if(currentSegment[6] > thresholdSegment[6]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 7 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[6] > thresholdSegment[6]) && (currentSegment[7] > thresholdSegment[7])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(6);
				relayOn(7);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 7 & 8 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(6);
				relayOff(7);
		}		
	}else if(currentSegment[7] > thresholdSegment[7]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 8 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[6] > thresholdSegment[6]) && (currentSegment[7] > thresholdSegment[7])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(6);
				relayOn(7);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 7 & 8 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(6);
				relayOff(7);
		}
	}
	/* ===============SEGMENT 9 DAN 10===================== */
		if(currentSegment[8] > thresholdSegment[8]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 9 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[8] > thresholdSegment[8]) && (currentSegment[9] > thresholdSegment[9])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(8);
				relayOn(9);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 9 & 10 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(8);
				relayOff(9);
		}		
	}else if(currentSegment[9] > thresholdSegment[9]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 10 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[8] > thresholdSegment[8]) && (currentSegment[9] > thresholdSegment[9])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(8);
				relayOn(9);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 9 & 10 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(8);
				relayOff(9);
		}
	}
	
	
	
	
	
	
	
	
	/* ===============SEGMENT 11 DAN 12===================== */
		if(currentSegment[10] > thresholdSegment[10]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 11 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[10] > thresholdSegment[10]) && (currentSegment[11] > thresholdSegment[11])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(10);
				relayOn(11);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 11 & 12 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(10);
				relayOff(11);
		}		
	}else if(currentSegment[11] > thresholdSegment[11]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 12 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[10] > thresholdSegment[10]) && (currentSegment[11] > thresholdSegment[11])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(10);
				relayOn(11);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 11 & 12 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(10);
				relayOff(11);
		}
	}





	/* ===============SEGMENT 13 DAN 14===================== */
		if(currentSegment[12] > thresholdSegment[13]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 13 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[12] > thresholdSegment[12]) && (currentSegment[13] > thresholdSegment[13])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(12);
				relayOn(13);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 13 & 14 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(12);
				relayOff(13);
		}		
	}else if(currentSegment[13] > thresholdSegment[13]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 14 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[12] > thresholdSegment[12]) && (currentSegment[13] > thresholdSegment[13])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(12);
				relayOn(13);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 11 & 12 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(12);
				relayOff(13);
		}
	}
	/* ===============SEGMENT 15 DAN 16===================== */
		if(currentSegment[14] > thresholdSegment[14]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 15 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[14] > thresholdSegment[14]) && (currentSegment[15] > thresholdSegment[15])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(14);
				relayOn(15);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 15 & 16 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(14);
				relayOff(15);
		}		
	}else if(currentSegment[15] > thresholdSegment[15]){
			/* PRE ALARM */
			// PESAN KE LCD
			LCD_Putsxy(0,1,"SEGMENT 16 ACTIVE");
			// BUZZERR BLINK
			buzzerBlink(2000);
		if((currentSegment[14] > thresholdSegment[14]) && (currentSegment[15] > thresholdSegment[15])){
			/* FIRE ALARM ACTIVE */
			// AKTIFKAN RELAY 0
				relayOn(14);
				relayOn(15);
			// USART TO SCADA
		
			// PESAN KE LCD
				LCD_Putsxy(0,1, "SEGMENT 15 & 16 ACTIVE");
				HAL_Delay(2000);
			}else{
				// NONAKTIF RELAY
				relayOff(14);
				relayOff(15);
		}
	}
}
void checkOverCurrentSensor(void){
	if(currentSegment[0] > currentOverSensor){limitOn(0);}
	if(currentSegment[1] > currentOverSensor){limitOn(1);}
	if(currentSegment[2] > currentOverSensor){limitOn(2);}
	if(currentSegment[3] > currentOverSensor){limitOn(3);}
	if(currentSegment[4] > currentOverSensor){limitOn(4);}
	if(currentSegment[5] > currentOverSensor){limitOn(5);}
	if(currentSegment[6] > currentOverSensor){limitOn(6);}
	if(currentSegment[7] > currentOverSensor){limitOn(7);}
	if(currentSegment[8] > currentOverSensor){limitOn(8);}
	if(currentSegment[9] > currentOverSensor){limitOn(9);}
	if(currentSegment[10] > currentOverSensor){limitOn(10);}
	if(currentSegment[11] > currentOverSensor){limitOn(11);}
	if(currentSegment[12] > currentOverSensor){limitOn(12);}
	if(currentSegment[13] > currentOverSensor){limitOn(13);}
	if(currentSegment[14] > currentOverSensor){limitOn(14);}
	if(currentSegment[15] > currentOverSensor){limitOn(15);}
}



















