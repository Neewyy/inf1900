  /*
  * Nom: compteur 32 bits
  * Copyright (C) 2005 Matthew Khouzam
  * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
  * Description: Ceci est un exemple simple de programme 
  * Version: 1.1
  */

  #define F_CPU 8000000
  #include <util/delay.h>


  #include <avr/io.h> 

  int main()
  {
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;
    int compteur = 0;

  for (;;)
  {
    PORTA = 0x01; // vert, att 2s
    _delay_ms(2000);
    PORTA = 0x02; // rouge, att 2s
    _delay_ms(2000);

    for (;;)
    {
      compteur += 10; // ambre, att 2s
      if (compteur >= 2000)
      {
        break;
      }
      else
      {
        PORTA = 0x01;
        _delay_ms(5);
        PORTA = 0x02;
        _delay_ms(5);
      }
    }

  }
    return 0; 
  }

