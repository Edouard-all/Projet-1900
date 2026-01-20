#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
const double delay = 200;
void _delay_ms(double ms);
bool bouton_presse();
int main() {
	DDRA |= (1 << PA0) | (1 << PA1);
	DDRD &= ~(1 << PD2);
	uint8_t etat = 0;
	while (true) {
        switch (etat)
        {
        case 0: //rouge    
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);
            if (bouton_presse()){
                etat++;
            }
            break;
        case 1: //vert
            PORTA |= (1 << PA1);
            PORTA &= ~(1 << PA0);
            if (bouton_presse()){
                etat++;
            }
            break;
        default: //ambre
            PORTA &= ~(1 << PA0);
            PORTA |= (1 << PA1);
            _delay_ms(5);
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);
            _delay_ms(1);
            if (bouton_presse()){
                etat = 0;
            }
            break;
        }
    }
}
bool bouton_presse(){
	if (PIND & (1 << PD2)){
		_delay_ms(delay);
        if (PIND & (1 << PD2)){
            return true;
        }
	}
	else {
		return false;
	}
}
void allumerLedRouge(){

}