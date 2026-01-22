#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
const double delayDebounce = 200;
const double delayRouge = 1;
const double delayVert = 5;
void _delay_ms(double ms);
void allumerLedRouge();
void allumerLedVert();
bool bouton_presse();
int main() {
	DDRA |= (1 << PA0) | (1 << PA1);
	DDRD &= ~(1 << PD2);
	uint8_t etat = 0;
	while (true) {
        switch (etat)
        {
        case 0: //rouge    
            allumerLedRouge();
            if (bouton_presse()){
                etat++;
            }
            break;
        case 1: //vert
            allumerLedVert();
            if (bouton_presse()){
                etat++;
            }
            break;
        default: //ambre
            allumerLedRouge();
            _delay_ms(delayRouge);
            allumerLedVert();
            _delay_ms(delayVert);
            if (bouton_presse()){
                etat = 0;
            }
            break;
        }
    }
}
bool bouton_presse(){
	if (PIND & (1 << PD2)){
		_delay_ms(delayDebounce);
        if (PIND & (1 << PD2)){
            return true;
        }
	}
	else {
		return false;
	}
}
void allumerLedRouge(){
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}
void allumerLedVert(){
    PORTA |= (1 << PA1);
    PORTA &= ~(1 << PA0);
}