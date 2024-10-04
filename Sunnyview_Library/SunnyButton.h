
/**************************************************************************************************
 * Project: Sunnyview Library
 * Program: Header file for a button used in Sunnyview projects
 * Company: Crescent School
 * Author: William Veldhuis
 * Date: Oct 4 2024
 * Version: 1
**************************************************************************************************/

#ifndef	SUNNYBUTTON
#define SUNNYBUTTON

#include "Arduino.h"
#include "SunnyLED.h"
#include <Stdint.h>

class SunnyButton{

	uint8_t m_port;
	SunnyLED m_led;
	bool m_reversed;

	public:
		/**
         *   \brief SunnyButton - Initializes the object
         *   \param port - The port the button is wired into
		 *   \param pullup - Does the button require a pullup resistor (if you didn't wire a resistor in then YES it does!)
		 *   \param btnreverse - Does the button inputs need to be reversed? if isPressed returns true when the button isn't pressed then YES is must be reversed
		 *   \param ledPort - If you wish to have the LED controls, pass the port number it is wired into here
		 *   \param ledreverse - If you wish to reverse the on/off states for the LED to make sure when you call setLEDOn it actually turns on
        **/
		SunnyButton(uint8_t port, bool pullup = true, bool btnreverse = false);
		void withLED(uint8_t ledPort = -1, bool ledreverse = false);

		/**
         *   \brief isPressed - returns true if the button is pressed, false if not pressed (make sure you set reverse in the constructor if what it returns isn't correct)
        **/
		bool isPressed();

		/**
         *   \brief setLEDOn - Turns the LED on if you have initialized the port
        **/
		void setLEDOn();

		/**
         *   \brief setLEDOff - Turns the LED off if you have initialized the port
        **/
		void setLEDOff();
};

#endif //SunnyButton