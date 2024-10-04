#include "H_Bridge.h"

Hbridge::Hbridge(uint8_t in1, uint8_t in2, boolean reverse) : m_pinA(in1), m_pinB(in2){
    pinMode(m_pinA, OUTPUT);
    pinMode(m_pinB, OUTPUT);
    //When reversed simply which the pins around
    if(reverse){
        m_pinA += m_pinB;           //Example A = 5, B = 6; A = A+B = 11
        m_pinB -= m_pinA;           //B = A-B = 11-6 = 5
        m_pinA = m_pinA - m_pinB;   //A = A-B = 11-5 = 6; A = 6, B = 5 (Flipped directions)
    }
}

void Hbridge::begin(){
    pinMode(m_pinA, OUTPUT);
    pinMode(m_pinB, OUTPUT);
}

void Hbridge::forwards(uint8_t speed){
    //Set one pin to low and the other output the pwm signal
    digitalWrite(m_pinB, LOW);
    setPin(m_pinA, speed);
}
void Hbridge::backwards(uint8_t speed){
    //Set one pin to low and the other output the pwm signal
    digitalWrite(m_pinA, LOW);
    setPin(m_pinB, speed);
}
void Hbridge::stop(){
    //Set both to low to stop
    digitalWrite(m_pinB, LOW);
    digitalWrite(m_pinA, LOW);
}

//Private functions
void Hbridge::setPin(uint8_t pin, uint8_t speed){
    analogWrite(pin, speed);
}