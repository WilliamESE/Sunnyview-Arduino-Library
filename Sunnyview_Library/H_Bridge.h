/**************************************************************************************************
 * Project: H-Bridge Library
 * Program: Header file for H-Bridge library
 * Company: Crescent School
 * Author: William Veldhuis
 * Date: Dec 4 2023
 * Version: 1
**************************************************************************************************/

#ifndef HBRIDGE
#define HBRIDGE

//Libraries
#include "Arduino.h"
#include <Stdint.h>

class Hbridge{
    //Private variables
    uint8_t m_pinA;
    uint8_t m_pinB;

    public:
        //Public functions
        /**
         *   \brief Hbridge - Initializes the object
         *   \param in1 - First PWM port to the H-bridge
         *   \param in2 - Second PWM port to the H-bridge
         *   \param reverse - Reverse the outputs; true = reversed, false = not reversed
        **/
        Hbridge(uint8_t in1, uint8_t in2, boolean reverse = false);
        void begin();

        /**
         *   \brief forwards - spins the motor in the forwards direction
         *   \param speed - speed of rotation from 0-255
        **/
        void forwards(uint8_t speed);

        /**
         *   \brief backwards - spins the motor in the backwards direction
         *   \param speed - speed of rotation from 0-255
        **/
        void backwards(uint8_t speed);

        /**
         *   \brief stop - stops the motor
        **/
        void stop();

    private:
        //Private functions
        void setPin(uint8_t pin, uint8_t speed);
};

#endif //HBRIDGE