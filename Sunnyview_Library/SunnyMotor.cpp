#include "SunnyMotor.h"

SunnyMotor::SunnyMotor(uint8_t port, bool reverse) : m_port(port), m_high(((reverse) ? LOW : HIGH)), m_low(((reverse) ? HIGH : LOW)){
	pinMode(m_port, OUTPUT);
}

void SunnyMotor::run(){
	digitalWrite(m_port, m_high);
}
void SunnyMotor::stop(){
	digitalWrite(m_port, m_low);
}