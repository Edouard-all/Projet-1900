/*Edouard Allaire
*Abdeldjallil Moncef MESSAI
*machines a etat pour allumer la led en pesant trois fois le bouton
*
* ========== I/O IDENTIFICATION (CONNEXIONS SUR LE ROBOT) =============
* 
*
* ┌───────────────────────────────────────────────────────────────────┐
* │                    ATmega324PA - Pinout                           │
* ├───────────────────────────────────────────────────────────────────┤
* │                                                                   │
* │   PORTA            PORTB           PORTC          PORTD           │
* │  ┌───────┐        ┌───────┐        ┌──────┐       ┌──────┐        │   
* │  │ PA0 ●─│→ledRout│PB0 ○  │        │PC0 ○ │       │PD0 ○ │        │
* │  │ PA1 ●─│→ledGout│PB1 ○  │        │PC1 ○ │       │PD1 ○ │        │
* │  │ PA2 ○ │        │PB2 ○  │        │PC2 ○ │       │PD2 ●─│→B-INT0 │
* │  │ PA3 ○ │        │PB3 ○  │        │PC3 ○ │       │PD3 ○ │        │
* │  │ PA4 ○ │        │PB4 ○  │        │PC4 ○ │       │PD4 ○ │        │
* │  │ PA5 ○ │        │PB5 ○  │        │PC5 ○ │       │PD5 ○ │        │
* │  │ PA6 ○ │        │PB6 ○  │        │PC6 ○ │       │PD6 ○ │        │
* │  │ PA7 ○ │        │PB7 ○  │        │PC7 ○ │       │PD7 ○ │        │
* │  └───────┘        └───────┘        └──────┘       └──────┘        │
* │                                                                   │
* │  ● = Utilisé          ○ = Non utilisé                             │
* └───────────────────────────────────────────────────────────────────┘
*
*bouton: input: PD2
*led: output: PA0 et PA1
+-----------------+-----+-----------------+-----+-----+
| etas            | PD2 | prochain etat   | PA0 | PA1 |
+-----------------+-----+-----------------+-----+-----+
| INIT            | 0   | INIT            | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| INIT            | 1   | PREMIER_APPUI   | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| PREMIER_APPUI   | 0   | PREMIER_RELACHE | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| PREMIER_APPUI   | 1   | PREMIER_APPUI   | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| PREMIER_RELACHE | 0   | PREMIER_RELACHE | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| PREMIER_RELACHE | 1   | SECOND_APPUI    | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| SECOND_APPUI    | 0   | SECOND_RELACHE  | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| SECOND_APPUI    | 1   | SECOND_APPUI    | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| SECOND_RELACHE  | 0   | SECOND_RELACHE  | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| SECOND_RELACHE  | 1   | DERNIER_APPUI   | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| DERNIER_APPUI   | 0   | DERNIER_RELACHE | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| DERNIER_APPUI   | 1   | DERNIER_APPUI   | 0   | 0   |
+-----------------+-----+-----------------+-----+-----+
| DERNIER_RELACHE | 0   | INIT            | 0   | 1   |
+-----------------+-----+-----------------+-----+-----+
| DERNIER_RELACHE | 1   | INIT            | 0   | 1   |
+-----------------+-----+-----------------+-----+-----+
*/
//boutton: entre DPD2
//led: sortie PD1 et PD2
#define F_CPU 8000000
#include<avr/io.h>
#include <util/delay.h>
const double delay = 20;
const double two_sec = 2000;
void _delay_ms(double ms);
bool bouton_presse();
void led_off();
void led_vert_two_sec();
enum Etat {INIT,PREMIER_APPUI,PREMIER_RELACHE,SECOND_APPUI,SECOND_RELACHE,DERNIER_APPUI,DERNIER_RELACHE};
Etat etat = INIT;
int main(){
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << PD2);
    while(true){
        switch (etat)
        {
        case INIT:
            led_off();
            if(bouton_presse()){
                etat = PREMIER_APPUI;
            }
            break;
        case PREMIER_APPUI:
            led_off();
            if(!(bouton_presse())){
                etat = PREMIER_RELACHE;
            }
            break;
        case PREMIER_RELACHE:
            led_off();
            if(bouton_presse()){
                etat = SECOND_APPUI;
            }
            break;
        case SECOND_APPUI:
            led_off();
            if(!(bouton_presse())){
                etat = SECOND_RELACHE;
            }
            break;
        case SECOND_RELACHE:
            led_off();
            if(bouton_presse()){
                etat = DERNIER_APPUI;
            }
            break;
        case DERNIER_APPUI:
            led_off();
            if(!(bouton_presse())){
                etat = DERNIER_RELACHE;
            }
            break;
        case DERNIER_RELACHE:
            led_vert_two_sec();
            etat = INIT;
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
        else {
            return false;
        }
	}
	else {
		return false;
	}
}
void led_off(){
    PORTA &= ~(1 << PA0) & ~(1 << PA1);
}
void led_vert_two_sec(){
    PORTA |= (1 << PA1);
    PORTA &= ~(1 << PA0);
    _delay_ms(two_sec);
    led_off();
}