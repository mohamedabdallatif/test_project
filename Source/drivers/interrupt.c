#include "../headers/Run.h"
#include "../headers/check_winner.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/Timer2.h"
#include "../headers/Nokia5110.h"
#include "../headers/gpio_driver.h"
#include "../headers/UART.h"
#include "../headers/Leds.h"

extern char matrix[10];
extern char turn;
extern int cursor;
int moves;
char win ;
int flag =0;

void GPIOPortF_Handler(void){
	if(GPIO_PORTF_RIS_R &(1<<4) && flag ==3){
		
	}
	if(GPIO_PORTF_RIS_R & (1<<0) && flag ==3){
	  
	}
	if(GPIO_PORTF_RIS_R &(1<<4) && flag==0){
			 PortE_Init();
			 PortB_Init();
			 drawGrid();
			 flag =1;
	}
	else if(GPIO_PORTF_RIS_R &(1<<0) && flag==0){
			PortE_Init();
			drawGrid();
			flag=2;
			UART();
	} 
	else if (GPIO_PORTF_RIS_R &(1<<4) && flag==1)  {
			Timer2_Init(20);
			GPIO_PORTF_ICR_R|= (1<<4);
			cursor--;
			if(cursor<1) cursor=9;
			drawGrid();
	}
		
	else if(GPIO_PORTF_RIS_R &(1<<0) && flag==1){	
			Timer2_Init(20);
			GPIO_PORTF_ICR_R |= (1<<0);
			cursor++;
			if(cursor>9) cursor=1;
			}	
			drawGrid();		
	}

void GPIOPortB_Handler(void){
		if (GPIO_PORTB_RIS_R &(1<<0) && flag==1)  
		{
			Timer2_Init(20);
			GPIO_PORTB_ICR_R|= (1<<0);
			if(cursor < 4 && cursor > 0)	cursor += 6;   //code up
			else	cursor -= 3;
			drawGrid();	
			}
		
		else if(GPIO_PORTB_RIS_R &(1<<1) && flag ==1){	
			Timer2_Init(20);
			GPIO_PORTB_ICR_R |= (1<<1);
			if(cursor < 10 && cursor > 6)	cursor -= 6;   //code down
			else	cursor += 3;
			drawGrid();		
		}
	
	else if(GPIO_PORTB_RIS_R&(1<<1) && flag ==1){	
		Timer2_Init(20);
		GPIO_PORTB_ICR_R |= (1<<1);
		if(cursor < 10 && cursor > 6)	cursor -= 6;   //code down
		else	cursor += 3;
		drawGrid();		
	}
}

void GPIOPortE_Handler(void){
if (GPIO_PORTE_RIS_R &(1<<1) && flag==1)  
	{
		Timer2_Init(20);
		GPIO_PORTE_ICR_R|= (1<<1);
		Timer2_Init(10);
			if(matrix[cursor]==' '){
					if (turn =='X'){
						matrix[cursor]='X';
						win = check_winner (matrix, turn);
						if (win == 1){
							Flash(0);//red led on
							Timer2_Init(100);
							Clear_Led(0);//red led off
							Nokia5110_ClearBuffer();
							Nokia5110_DisplayBuffer();
							Nokia5110_SetCursor(3, 2);
							Nokia5110_OutChar(turn);
							Nokia5110_OutString("-Player");
							Nokia5110_SetCursor(4, 3);
							Nokia5110_OutString("wins");
							Timer2_Init(100);
							Nokia5110_DisplayBuffer();
							Timer2_Init(100);
							return;
						}
						Clear_Led(0);
						turn='O';
					}
			else{ 
				Set_Led(2);
				matrix[cursor]='O';
				win = check_winner (matrix, turn);
				if (win == 1){
					Flash(2);//red led on
					Timer2_Init(100);
					Clear_Led(2);//red led off
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Nokia5110_SetCursor(3, 2);
					Nokia5110_OutChar(turn);
					Nokia5110_OutString("-Player");
					Nokia5110_SetCursor(4, 3);
					Nokia5110_OutString("wins");
					Timer2_Init(100);
					Nokia5110_DisplayBuffer();
					Timer2_Init(100);
					return;
				}						
				Clear_Led(2);
				turn='X';
			}
			drawGrid();
			moves++;
			if (!win&&moves==9){
					Flash(3);//red led on
					Timer2_Init(50);
					Clear_Led(3);//red led off
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Nokia5110_SetCursor(2, 2);
					Nokia5110_OutString("NO");
					Nokia5110_DisplayBuffer();
					Timer2_Init(6);
					Nokia5110_SetCursor(3, 3);
					Nokia5110_OutString("ONE");
					Nokia5110_DisplayBuffer();
					Timer2_Init(6);
					Nokia5110_SetCursor(4, 4);
					Nokia5110_OutString("WIN!!");
					Nokia5110_DisplayBuffer();
					Timer2_Init(6);
					return;
			}
		}
	}			
}

