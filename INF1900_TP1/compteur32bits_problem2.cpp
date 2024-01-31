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
    DDRD = 0x00;
    // int compteur = 0;

  for (;;)
  {
    if (PIND & 0x04)
    {
      PORTA = 0x02;
    }
    else
    {
      PORTA = 0x00;
    }
  }
    return 0; 
  }

