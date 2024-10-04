/**************************************************************************************************
 * Project: Sunnyview Library
 * Program: Header file for a motor used in Sunnyview projects. These motors can only move in one direction
 * Company: Crescent School
 * Author: William Veldhuis
 * Date: Oct 4 2024
 * Version: 1
**************************************************************************************************/

#ifndef	SUNNYMOTOR
#define SUNNYMOTOR

#include "Arduino.h"
#include <Stdint.h>

class SunnyMotor{

	uint8_t m_port;
	bool m_high;
	bool m_low;

	public:
		/**
         *   \brief SunnyMotor - Initializes the object
         *   \param port - The port the motor is wired into
		 *   \param reverse - Does the motor outputs need to be reversed? if run() stops it then YES you need to reverse it!
        **/
		SunnyMotor(uint8_t port, bool reverse = false);

		/**
         *   \brief run - Runs the motor
        **/
		void run();

		/**
         *   \brief stop - Stops the motor
        **/
		void stop();
};

#endif //SUNNYMOTOR