/*
================================================
================ INPUT OUTPUT ==================
================================================
*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "Header.h"
#include "dwt_delay.h"

void buzzerOn(int delay){
	HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_SET);
	DWT_Delayms(delay);
}
void buzzerOff(int delay){
	HAL_GPIO_WritePin(GPIOA, BUZZER_Pin, GPIO_PIN_RESET);
	DWT_Delayms(delay);
}
void buzzerBlink(int delay){
	HAL_GPIO_TogglePin(GPIOA, BUZZER_Pin);
	DWT_Delayms(delay);
}
void relayOn(int number){
		if(number == 0){
			HAL_GPIO_WritePin(RL_0_GPIO_Port, RL_0_Pin, HIGH);	
		}
		else if(number == 1){
			HAL_GPIO_WritePin(RL_1_GPIO_Port, RL_1_Pin, HIGH);	
		}
		else if(number == 2){
			HAL_GPIO_WritePin(GPIOC, RL_2_Pin, HIGH);	
		}
		else if(number == 3){
			HAL_GPIO_WritePin(GPIOC, RL_3_Pin, HIGH);	
		}
		else if(number == 4){
			HAL_GPIO_WritePin(RL_4_GPIO_Port, RL_4_Pin, HIGH);	
		}
		else if(number == 5){
			HAL_GPIO_WritePin(GPIOC, RL_5_Pin, HIGH);	
		}
		else if(number == 6){
			HAL_GPIO_WritePin(GPIOE, RL_6_Pin, HIGH);	
		}
		else if(number == 7){
			HAL_GPIO_WritePin(GPIOE, RL_7_Pin, HIGH);	
		}
		else if(number == 8){
			HAL_GPIO_WritePin(GPIOE, RL_8_Pin, HIGH);	
		}
		else if(number == 9){
			HAL_GPIO_WritePin(GPIOE, RL_9_Pin, HIGH);	
		}
		else if(number == 10){
			HAL_GPIO_WritePin(GPIOE, RL_10_Pin, HIGH);	
		}
		else if(number == 11){
			HAL_GPIO_WritePin(GPIOE, RL_11_Pin, HIGH);	
		}
		else if(number == 12){
			HAL_GPIO_WritePin(GPIOB, RL_12_Pin, HIGH);	
		}
		else if(number == 13){
			HAL_GPIO_WritePin(GPIOB, RL_13_Pin, HIGH);	
		}
		else if(number == 14){
			HAL_GPIO_WritePin(GPIOB, RL_14_Pin, HIGH);	
		}
		else if(number == 15){
			HAL_GPIO_WritePin(GPIOB, RL_15_Pin, HIGH);	
		}
		else if(number == 16){
			HAL_GPIO_WritePin(GPIOB, RL_16_Pin, HIGH);
		}
		else{
			HAL_GPIO_WritePin(GPIOH, RL_0_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOH, RL_1_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOC, RL_2_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOC, RL_3_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_4_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOC, RL_5_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_6_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_7_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_8_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_9_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_10_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, RL_11_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, RL_12_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, RL_13_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, RL_14_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, RL_15_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, RL_16_Pin, HIGH);
		}
}

void relayOff(int number){
		if(number == 0){
			HAL_GPIO_WritePin(GPIOH, RL_0_Pin, LOW);	
		}
		else if(number == 1){
			HAL_GPIO_WritePin(GPIOH, RL_1_Pin, LOW);	
		}
		else if(number == 2){
			HAL_GPIO_WritePin(GPIOC, RL_2_Pin, LOW);	
		}
		else if(number == 3){
			HAL_GPIO_WritePin(GPIOC, RL_3_Pin, LOW);	
		}
		else if(number == 4){
			HAL_GPIO_WritePin(GPIOE, RL_4_Pin, LOW);	
		}
		else if(number == 5){
			HAL_GPIO_WritePin(GPIOC, RL_5_Pin, LOW);	
		}
		else if(number == 6){
			HAL_GPIO_WritePin(GPIOE, RL_6_Pin, LOW);	
		}
		else if(number == 7){
			HAL_GPIO_WritePin(GPIOE, RL_7_Pin, LOW);	
		}
		else if(number == 8){
			HAL_GPIO_WritePin(GPIOE, RL_8_Pin, LOW);	
		}
		else if(number == 9){
			HAL_GPIO_WritePin(GPIOE, RL_9_Pin, LOW);	
		}
		else if(number == 10){
			HAL_GPIO_WritePin(GPIOE, RL_10_Pin, LOW);	
		}
		else if(number == 11){
			HAL_GPIO_WritePin(GPIOE, RL_11_Pin, LOW);	
		}
		else if(number == 12){
			HAL_GPIO_WritePin(GPIOB, RL_12_Pin, LOW);	
		}
		else if(number == 13){
			HAL_GPIO_WritePin(GPIOB, RL_13_Pin, LOW);	
		}
		else if(number == 14){
			HAL_GPIO_WritePin(GPIOB, RL_14_Pin, LOW);	
		}
		else if(number == 15){
			HAL_GPIO_WritePin(GPIOB, RL_15_Pin, LOW);	
		}
		else if(number == 16){
			HAL_GPIO_WritePin(GPIOB, RL_16_Pin, LOW);
		}
		else{
			HAL_GPIO_WritePin(GPIOH, RL_0_Pin, LOW);
			HAL_GPIO_WritePin(GPIOH, RL_1_Pin, LOW);
			HAL_GPIO_WritePin(GPIOC, RL_2_Pin, LOW);
			HAL_GPIO_WritePin(GPIOC, RL_3_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_4_Pin, LOW);
			HAL_GPIO_WritePin(GPIOC, RL_5_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_6_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_7_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_8_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_9_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_10_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, RL_11_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, RL_12_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, RL_13_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, RL_14_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, RL_15_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, RL_16_Pin, LOW);
		}
}

void limitOn(int number){
	if(number == 0){
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, HIGH);
	}else if(number == 1){
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, HIGH);
	}else if(number == 2){
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, HIGH);
	}else if(number == 3){
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, HIGH);
	}else if(number == 4){
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, HIGH);
	}else if(number == 5){
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, HIGH);
	}else if(number == 6){
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, HIGH);
	}else if(number == 7){
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, HIGH);
	}else if(number == 8){
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, HIGH);
	}else if(number == 9){
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, HIGH);
	}else if(number == 10){
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, HIGH);
	}else if(number == 11){
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, HIGH);
	}else if(number == 12){
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, HIGH);
	}else if(number == 13){
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, HIGH);
	}else if(number == 14){
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, HIGH);
	}else if(number == 15){
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, HIGH);
	}else{
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, HIGH);
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, HIGH);
	}
}






void limitOff(int number){
		if(number == 0){
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, LOW);
	}else if(number == 1){
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, LOW);
	}else if(number == 2){
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, LOW);
	}else if(number == 3){
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, LOW);
	}else if(number == 4){
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, LOW);
	}else if(number == 5){
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, LOW);
	}else if(number == 6){
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, LOW);
	}else if(number == 7){
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, LOW);
	}else if(number == 8){
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, LOW);
	}else if(number == 9){
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, LOW);
	}else if(number == 10){
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, LOW);
	}else if(number == 11){
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, LOW);
	}else if(number == 12){
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, LOW);
	}else if(number == 13){
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, LOW);
	}else if(number == 14){
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, LOW);
	}else if(number == 15){
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, LOW);
	}else{
			HAL_GPIO_WritePin(GPIOB, LIM0_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM1_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM2_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM3_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM4_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM5_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM6_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM7_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM8_Pin, LOW);
			HAL_GPIO_WritePin(GPIOE, LIM9_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM10_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM11_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM12_Pin, LOW);
			HAL_GPIO_WritePin(GPIOB, LIM13_Pin, LOW);
			HAL_GPIO_WritePin(GPIOD, LIM14_Pin, LOW);
			HAL_GPIO_WritePin(GPIOD, LIM15_Pin, LOW);
	}
}













