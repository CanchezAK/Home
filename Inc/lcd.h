#ifndef LCD_H_

#define LCD_H_

 

#include "main.h"

 

#endif /* LCD_H_ */

#define d4_set() HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET)

#define d5_set() HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET)

#define d6_set() HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET)

#define d7_set() HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET)

#define d4_reset() HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET)

#define d5_reset() HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET)

#define d6_reset() HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET)

#define d7_reset() HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET)

 

#define e1 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET) // установка линии E в 1

#define e0 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET) // установка линии E в 0

#define rs1 HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET) // установка линии RS в 1 (данные)

#define rs0 HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET) // установка линии RS в 0 (команда)