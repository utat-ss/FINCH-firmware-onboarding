/*
DemoApp.h
Date Created: Oct 11th, 2022
Last Date Modified: Oct 13th, 2022

Author(s): Aspen Erlandsson


Defines the functions called by the hardware timer and button interrupts.

When the button press interrupt is called, the LED that flashes is switched.

The LEDs are flashed at the appropriate rate by running a function at specific
time intervals that keeps track of which LED should be on or off ay any given time

 */


#include "DemoApp.h"


//Which of the 3: [LD1,LD2,LD3] LEDs are currently selected to be flashed
volatile uint8_t g_selected_led_index = 0;

//A high level counter used by demo_app_clock_interrupt_handler_8hz() for correct flash timing
volatile uint8_t g_high_level_counter = 0;



/*
Toggles the LED specified by index for on-board LEDs [LD1, LD2, LD3]
Acceptable values uint8_t index are 0, 1, or 2, otherwise the function does nothing
 */
void toggle_led_index(uint8_t index) {
	if (index == 0) {
		//0b1 masks the rightmost (zeroeth) register(?) bit, and it is then toggled using bitwise XOR
	    GPIOB->ODR ^= 0b1;
		return;
	}

	if (index == 1) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
		return;
	}

	if (index == 2) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		return;
	}

}

/*
 Expected to be called on the rising edge of the on-board blue button.
 Rotates the value of selected_led_index from 1->2->3->1->2 etc.
 Sets high_level_counter in such a way that the demo_app_clock_interrupt_handler_8hz
 will definitely turn on the correct LED immidiately the next time it is called
 Turns off LD1, LD2, and LD3.
 */
void demo_app_button_press_handler() {
	g_selected_led_index = (g_selected_led_index + 1) % 3;
	g_high_level_counter = 4 >> g_selected_led_index;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	}


/*
Expects to be called at a rate of 8hz by a hardware timer interrupt.
Toggles the currently selected LED at the correct rate, by calling the toggle
function every (2^(index + 1))th interval, i.e. every 2nd interval, every 4th, every 8th
for LD1, LD2, LD3 respectively
 */
void demo_app_clock_interrupt_handler_8hz() {
	//Magic
	if ((g_high_level_counter % 8) % (4 >> g_selected_led_index) == 0) {
		toggle_led_index(g_selected_led_index);
	}

	g_high_level_counter++;
}

