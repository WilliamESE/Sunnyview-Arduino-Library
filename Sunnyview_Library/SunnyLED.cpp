#include "SunnyLED.h"

SunnyLED::SunnyLED(uint8_t port, bool reverse) : m_port(port), m_high(((reverse) ? LOW : HIGH)), m_low(((reverse) ? HIGH : LOW)){
	if(m_port != -1)
		pinMode(m_port, OUTPUT);
}

void SunnyLED::setOn(){
	if(m_port == -1)
		return;
	digitalWrite(m_port, m_high);
}
void SunnyLED::setOff(){
	if(m_port == -1)
		return;
	digitalWrite(m_port, m_low);
}


void SunnyLED::setPort(uint8_t port, bool reverse = false){
	m_port = port;
	m_high = (((reverse) ? LOW : HIGH));
	m_low = (((reverse) ? HIGH : LOW));
	if(m_port != -1)
		pinMode(m_port, OUTPUT);
}