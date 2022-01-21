/* INCLUDE LIBRARY */
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Header.h"
#include "stdbool.h"
#include "stdio.h"
#include "String.h"
/* INITIALIZE FUNCTION */
void parsingDataF1(void);
/* VARIABLE */
char tx[100];
//uint8_t rx_buff;
//uint16_t i;
//char Rx[50], tmp2[50];
bool flagRx = false;
char dateTime[100];
char dataF1[100];
char tampungData[100];
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
			}else if(j == 2 && flag2 == false){
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
}