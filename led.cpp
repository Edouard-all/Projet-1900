#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
double ms = 16000000;
void _delay_ms(double ms);
void ambre();
int main() {
	__builtin_avr_delay_cycles(ms);
	DDRA |= (1 << PA0) | (1 << PA1);
	DDRD &= ~(1 << PD2);
	while (true) {
		PORTA |= (1 << PA0);
		PORTA &= ~(1 << PA1); //rouge
		_delay_ms(ms);
		PORTA |= (1 << PA1);
		PORTA &= ~(1 << PA0); //vert
		_delay_ms(ms);
		ambre();
		_delay_ms(ms);
	}

}
void ambre() {
	while (true) {
		PORTA |= (1 << PA0);
		PORTA &= ~(1 << PA1);
		_delay_ms(1);
		PORTA &= ~(1 << PA0);
		PORTA |= (1 << PA1);
		_delay_ms(1);
	}
}