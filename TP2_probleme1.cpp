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
* │  │ PA0 ●─│→ledR   │PB0 ○  │        │PC0 ○ │       │PD0 ○ │        │
* │  │ PA1 ●─│→ledG   │PB1 ○  │        │PC1 ○ │       │PD1 ○ │        │
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
| INIT            | 0   | INT             | 0   | 0   |
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
#include<avr/io.h>
#include <util/delay.h>
const double delay = 200;
void _delay_ms(double ms);
bool bouton_presse();
enum Etat (INIT,PREMIER_APPUI,PREMIER_RELACHE,SECOND_APPUI,SECOND_RELACHE,DERNIER_APPUI,DERNIER_RELACHE);
Etat etat = INIT;
int main(){
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD &= ~(1 << PD2);
    while(true){
        switch (etat)
        {
        case INIT:
            
            break;
        
        default:
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