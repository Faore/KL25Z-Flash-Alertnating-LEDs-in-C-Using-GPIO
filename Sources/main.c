/*
*	main.c by Daniel Mills
*	Created on 10/25/15
*	EELE 371 Lab #8 Part 1 Code
*/

#include "derivative.h" /* include peripheral declarations */

/* Constants are saved in ROM. 'const' is the keyword to save in ROM. */

/*Activate Port B via System Clock Gating Control Register 5 */
const uint32_t	Port_Clock_Gate_Control =  0b10000000000;	//Bit 10 is port B
  		
/*MUX Manipulation */
const uint32_t	MUX_GPIO_Mask_SET = 0b00000000000000000000000100000000;	//Set GPIO option in MUX by
const uint32_t	MUX_GPIO_Mask_CLR = 0b11111111111111111111100111111111;	//Masking 001 to the MUX bits
		
/*LED bit masks */
const uint32_t	red = 0b1000000000000000000;	//Red is bit 18
const uint32_t  green = 0b10000000000000000000;
const uint32_t  blue = 0b10;


/* Variables are saved in RAM */
uint32_t data;				//For storing register data
volatile uint32_t *addr;	//For storing register addresses
/* NOTE: saved system addresses (such as SIM_SCGC5 are declared volatile
 * when defined in the system. It is therefore necessary to declare any 
 * variable that will use these values volatile.
 */

/* Functions for convenience */
void waitMillis(uint32_t);
void ledOn(uint32_t);
void ledOff(uint32_t);
void ledToggle(uint32_t);
void setStates(uint8_t);

int main(void) {
	/* Activate port B by masking the Port Clock Gate Control bits */
	
	data = SIM_SCGC5;				//Store the data from the specified register
	data |= Port_Clock_Gate_Control;//Update the data to what it should be
	addr = &SIM_SCGC5;				//Get the address of the specified register
	*addr = data;					//"Upload" the data to the specified register
	
	/* Set the LED pin as GPIO in the MUX settings via bit-masking */
	
	/* Red */
	data = PORTB_PCR18;			//Store the data from the specified register
	data |= MUX_GPIO_Mask_SET;	//Update the data to what it should be
	data &= MUX_GPIO_Mask_CLR;	//Update the data to what it should be
	addr = &PORTB_PCR18;		//Get the address of the specified register
	*addr = data;				//"Upload" the data to the specified register
	
	/* Green */
		data = PORTB_PCR19;			//Store the data from the specified register
		data |= MUX_GPIO_Mask_SET;	//Update the data to what it should be
		data &= MUX_GPIO_Mask_CLR;	//Update the data to what it should be
		addr = &PORTB_PCR19;		//Get the address of the specified register
		*addr = data;				//"Upload" the data to the specified register
		
	/* Blue */
		data = PORTD_PCR01;			//Store the data from the specified register
		data |= MUX_GPIO_Mask_SET;	//Update the data to what it should be
		data &= MUX_GPIO_Mask_CLR;	//Update the data to what it should be
		addr = &PORTD_PCR01;		//Get the address of the specified register
		*addr = data;				//"Upload" the data to the specified register
		
	/* Set the LED pin as an output */
	
	/* Red */
	data = GPIOB_PDDR;		//Store the data from the specified register
	data |= red;			//Update the data to what it should be
	addr = &GPIOB_PDDR;		//Get the address of the specified register
	*addr = data;			//"Upload" the data to the specified register
	
	/* Green */
	data = GPIOB_PDDR;		//Store the data from the specified register
	data |= green;			//Update the data to what it should be
	addr = &GPIOB_PDDR;		//Get the address of the specified register
	*addr = data;			//"Upload" the data to the specified register
	
	/* Blue */
	data = GPIOD_PDDR;		//Store the data from the specified register
	data |= blue;			//Update the data to what it should be
	addr = &GPIOD_PDDR;		//Get the address of the specified register
	*addr = data;			//"Upload" the data to the specified register


	/* Turn off the LED */
	ledOffRG(red);
	ledOffRG(green);
	
	/* Loop forever */
	for(;;) {
		waitMillis(500);	//Wait between loops
		ledToggleRG(red);		//Toggle the red LED
	}
	
	return 0;
}

/* Power on a specified LED */
void ledOnRG(uint32_t led) {
	addr = &GPIOB_PCOR;	//Clear (turn on)
	*addr = led;		//the led
}

/* Power off a specified LED */
void ledOffRG(uint32_t led) {
	addr = &GPIOB_PSOR;	//Set (turn off)
	*addr = led;		//the led
}

/* Toggle a specified LED */
void ledToggleRG(uint32_t led) {
	addr = &GPIOB_PTOR;
	*addr = led;
}
/* Blue is on a different port/
/* Power on a specified LED */
void ledOnB(uint32_t led) {
	addr = &GPIOD_PCOR;	//Clear (turn on)
	*addr = led;		//the led
}

/* Power off a specified LED */
void ledOffB(uint32_t led) {
	addr = &GPIOD_PSOR;	//Set (turn off)
	*addr = led;		//the led
}

/* Toggle a specified LED */
void ledToggleB(uint32_t led) {
	addr = &GPIOD_PTOR;
	*addr = led;
}

/* Wait for a specified number of milliseconds */
void waitMillis(uint32_t millis) {
	millis *= 2400;
	while(millis > 0) millis--;
}
