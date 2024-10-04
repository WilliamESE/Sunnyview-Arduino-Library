#include "SunnyButton.h"

SunnyButton::SunnyButton(uint8_t port, bool pullup, bool btnreverse) : m_port(port), m_reversed(btnreverse), m_led(-1){
	if(pullup)
		pinMode(m_port, INPUT_PULLUP);
	else
		pinMode(m_port, INPUT);
}

void SunnyButton::withLED(uint8_t ledPort, bool ledreverse = false){
	m_led.setPort(ledPort, ledreverse);
}

bool SunnyButton::isPressed(){
	return ((m_reversed) ? digitalRead(m_port) : !digitalRead(m_port));
}

void SunnyButton::setLEDOn(){
	m_led.setOn();
}
void SunnyButton::setLEDOff(){
	m_led.setOff();
}