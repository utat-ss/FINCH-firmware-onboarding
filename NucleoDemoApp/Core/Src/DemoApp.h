/*
DemoApp.h
Date Created: Oct 11th, 2022
Last Date Modified: Oct 13th, 2022

Author(s): Aspen Erlandsson
 */
#include "main.h"

#ifndef SRC_DEMOAPP_H_
#define SRC_DEMOAPP_H_
extern volatile uint8_t g_selected_led_index;
extern volatile uint8_t g_high_level_counter;

/*
Toggles the LED specified by index for on-board LEDs [LD1, LD2, LD3]
Acceptable values uint8_t index are 0, 1, or 2, otherwise the function does nothing
 */
void toggle_led_index(uint8_t index);


/*
 Expected to be called on the rising edge of the on-board blue button.
 Rotates the value of selected_led_index from 1->2->3->1->2 etc.
 Sets high_level_counter in such a way that the demo_app_clock_interrupt_handler_8hz
 will definitely turn on the correct LED immidiately the next time it is called
 Turns off LD1, LD2, and LD3.
 */
void demo_app_button_press_handler();


/*
Expects to be called at a rate of 8hz by a hardware timer interrupt.
Toggles the currently selected LED at the correct rate, by calling the toggle
function every (2^(index + 1))th interval, i.e. every 2nd interval, every 4th, every 8th
for LD1, LD2, LD3 respectively
 */
void demo_app_clock_interrupt_handler_8hz();



#endif /* SRC_DEMOAPP_H_ */
