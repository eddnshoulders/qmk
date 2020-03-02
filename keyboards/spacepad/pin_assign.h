#pragma once

#include "custom_board.h"

#undef B0
#undef B1
#undef B2
#undef B3
#undef B4
#undef B5
#undef B6
#undef C6
#undef D0
#undef D1
#undef D2
#undef D3
#undef D4
#undef D7
#undef E6
#undef F4
#undef F5
#undef F6
#undef F7
                 //pin
#define D3 PIN1  //006
#define D2 PIN2  //008
#define D1 PIN5  //015
#define D0 PIN6  //017
#define D4 PIN7  //020
#define C6 PIN8  //013
#define D7 PIN9  //024
#define E6 PIN10 //009
#define B4 PIN11 //010
#define B5 PIN12 //106
#define B6 PIN13 //111
#define B2 PIN14 //028
#define B3 PIN15 //003
#define B1 PIN16 //113
#define F7 PIN17 //002
#define F6 PIN18 //029
#define F5 PIN19 //031
#define F4 PIN20 //030

#define THIS_DEVICE_ROWS 3
#define THIS_DEVICE_COLS 4

#define MATRIX_ROW_PINS { B4, B5, D3 }
#define MATRIX_COL_PINS { B3, B2, B6, D2 }
