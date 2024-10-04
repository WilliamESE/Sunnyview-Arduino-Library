/**************************************************************************************************
 * Project: Sunnyview Library
 * Program: Header file for an LED used in Sunnyview projects
 * Company: Crescent School
 * Author: William Veldhuis
 * Date: Oct 4 2024
 * Version: 1
**************************************************************************************************/

#ifndef	SUNNYLED
#define SUNNYLED

#include "Arduino.h"
#include <Stdint.h>

class SunnyLED{

	uint8_t m_port;
	bool m_high;
	bool m_low;

	public:
		/**
         *   \brief SunnyLED - Initializes the object
         *   \param port - The port the LED is wired into
		 *   \param reverse - Does the LED outputs need to be reversed? if setOn turns it off then YES you need to reverse it!
        **/
		SunnyLED(uint8_t port, bool reverse = false);

		/**
         *   \brief setOn - Turns the LED on
        **/
		void setOn();

		/**
         *   \brief setOff - Turns the LED off
        **/
		void setOff();

		/**
         *   \brief setPort - Modifies the LED port information
		 *   \param port - The port the LED is wired into
		 *   \param reverse - Does the LED outputs need to be reversed? if setOn turns it off then YES you need to reverse it!
        **/
		void setPort(uint8_t port, bool reverse = false);
};

#endif //SUNNYLED