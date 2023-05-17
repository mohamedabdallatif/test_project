#include "../headers/tm4c123gh6pm.h"
#include "../headers/Nokia5110.h"
#include "../headers/TExaS.h"
#include "../headers/gpio_driver.h"
#include "../headers/UART.h"
#include "../headers/Timer2.h"
#include "../headers/Leds.h"


int i = 0, j = 0, position = 1, current_cursor = 1, moves=0, start;
char matrix[10]={'a',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char turn = 'X', x = 'X', o = 'O';
int scoreX = 0, scoreO = 0, cursor = 1;

void drawGrid(void){
	if(start==0){
		Start_Game();
		Clear_ALL();
		start++;
	}
	Clear_Led_PF1();
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	current_cursor=1,position=1;
	
	// Horizontal borders
	for(i = 0 ;i < 8 ;i++){
		Nokia5110_SetCursor(i, 1);
		Nokia5110_OutString("-");
		Nokia5110_SetCursor(i, 3);
		Nokia5110_OutString("-");
	}

	// Vertical borders
	for(j = 0 ;j < 5 ;j+=2){
		Nokia5110_SetCursor(2, j);
		Nokia5110_OutString("|");
		Nokia5110_SetCursor(5, j);
		Nokia5110_OutString("|");	
	}

// arrayay values
 for(i = 0 ;i < 5;i+=2) {
	for(j = 0 ;j < 8 ;j+=3){
			Nokia5110_SetCursor(j, i);
			Nokia5110_OutChar(matrix[position++]);
	}
}
 
// Displaying cursor
 for(i = 0 ;i < 5;i+=2) {
	for(j = 1 ;j < 8 ;j+=3){
		if(current_cursor == cursor){
			Nokia5110_SetCursor(j, i);
			Nokia5110_OutChar('.');
		}
		current_cursor++;
		}
}

// 	Display Trun
			Nokia5110_SetCursor(8,0);
			Nokia5110_OutString("Turn");
			Nokia5110_SetCursor(9,1);
			Nokia5110_OutChar(turn);

}
void result(){
		Nokia5110_ClearBuffer();
		Nokia5110_DisplayBuffer();
		Nokia5110_SetCursor(2, 2);
		Nokia5110_OutString("X-");
		Nokia5110_SetCursor(2, 3);
		Nokia5110_OutString("Y-");
		Nokia5110_SetCursor(6, 2);
		Nokia5110_OutUDec(scoreX);
		Nokia5110_SetCursor(6, 3);
		Nokia5110_OutUDec(scoreO);
		Timer2_Init(100);
		Nokia5110_DisplayBuffer();
		Timer2_Init(100);
}
/*void choose(void){
   if(GPIO_PORTF_DATA_R & 1){
	   PortE_Init();
		 PortB_Init();
	 }
	 else if (GPIO_PORTF_DATA_R & (1<<4)){
	    UART();

	 }
}

void Xo_Init(void){
	Nokia5110_SetCursor(4,1);
	Nokia5110_OutString("1.Kit");
	Nokia5110_SetCursor(4,2);
	Nokia5110_OutString("2.UART");
}
*/
