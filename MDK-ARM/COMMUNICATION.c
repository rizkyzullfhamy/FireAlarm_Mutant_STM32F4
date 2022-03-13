/* INCLUDE LIBRARY */
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Header.h"
#include "stdbool.h"
#include "stdio.h"
#include "String.h"
/* INITIALIZE FUNCTION */
void parsingDataF1(void);
void sendDateTime(void);
void sendDataSegment(void);
/* VARIABLE */
char tx[128];
//uint8_t rx_buff;
//uint16_t i;
//char Rx[50], tmp2[50];
bool flagRx = false;
char dateTime[128];
char dataF1[128];
char tampungData[128];
bool flag1, flag2;

void parsingDataF1(void){
	int j = 0;
	flag1 = false;
	flag2 = false;
	for(int i = 0; i < sizeof(tx); i++){
		if(tx[i] == '|'){
			j++;
		}else{
			if(j == 1 && flag1 == false){
				memset(dateTime, 0, sizeof(dateTime));
				for(int ct = 0; ct < sizeof(tampungData); ct++){
					dateTime[ct] =  tampungData[ct];
				}
				//HAL_UART_Transmit(&huart6,(uint8_t *) RxSip1, strlen(RxSip1), 100);
				flag1 = true;
			}else if(j == 2 && flag2 == false){			// BUAT TAMBAHAN APABILA ADA DATA DI F1 MAU DIKIRIMKAN KE F4 
				memset(dataF1, 0, sizeof(dataF1));
				uint8_t tmpIndex = i;
				tmpIndex -= 4;			// prev index 
				for(int ct = 0; ct < sizeof(tampungData); ct++){
					dataF1[ct] =  tampungData[tmpIndex++];
				}
				//HAL_UART_Transmit(&huart6,(uint8_t *) RxSip2, strlen(RxSip2), 100);
				flag2 = true;
			}
			tampungData[i] = tx[i];
		}
	}
	memset(tampungData, 0, sizeof(tampungData));
	flagRx = false;
	char bufff [128];
	
//	sprintf(bufff, "TIME : %s | F1: %s \r\n",dateTime, dataF1);
//	HAL_UART_Transmit(&huart6,(uint8_t *) bufff, strlen(bufff), 100);
}

void sendDateTime(void){
	char bufferDateTime [100];
//	int hour = 12;
//	int minute = 11;
//	int second = 30;
//	int day = 23;
//	int month = 2;
//	int year = 2022;
	for(int i = 0; i < 3; i++){
			sprintf(bufferDateTime, "%d,%d,%d,%d,%d,%d,\r\n",hour,minute,second,day,month,year);
			HAL_UART_Transmit(&huart1,(uint8_t *) bufferDateTime, strlen(bufferDateTime), 100);
			HAL_Delay(200);
	}
}

void sendDataSegment(void){
	char bufferData [100];

	sprintf(bufferData, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", 
	dataSeg[0], dataSeg[1], dataSeg[2], dataSeg[3],dataSeg[4],dataSeg[5], dataSeg[6], dataSeg[7], 
	dataSeg[8],dataSeg[9],dataSeg[10], dataSeg[11], dataSeg[12], dataSeg[13],dataSeg[14],dataSeg[15]);
	
	HAL_UART_Transmit(&huart1,(uint8_t *) bufferData, strlen(bufferData), 100);
}