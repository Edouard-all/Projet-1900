#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
const double ms = 1600;
void _delay_ms(double ms);
void ambre(int compteur);
int main() {
	__builtin_avr_delay_cycles(ms);
	DDRA |= (1 << PA0) | (1 << PA1);
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	int etat = 0;
	while (true) {
		if (!(PIND & 1 << PD2)){
			_delay_ms(50);
			if (!(PIND & 1 << PD2)){
				switch (etat)
				{
				case 0: //rouge
					PORTA |= (1 << PA0);
					PORTA &= ~(1 << PA1);
					etat++;
					break;
				case 1: //vert
					PORTA |= (1 << PA1);
					PORTA &= ~(1 << PA0);
					etat++;
					break;
				default: //ambre
					_delay_ms(50);
					while (PIND & 1 << PD2) {
					PORTA |= (1 << PA0);
					PORTA &= ~(1 << PA1);
					_delay_ms(1);
					PORTA &= ~(1 << PA0);
					PORTA |= (1 << PA1);
					_delay_ms(1);
					}
					etat = 0;
					break;
				}
			}

		}
	}

}