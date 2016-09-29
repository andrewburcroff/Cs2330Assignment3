#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

int main(void)
{
    WDTCTL  = WDTPW | WDTHOLD;//watch dog disabled or a name distant name
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1DIR |= 0b00001001;//direction output for P1.0 and P1.6
    P1OUT |= 0b00001001;//set P1.0 and P1.6 ON

    serial_init(9600);

    for(;;)
    {
      int j = 0;
      char arraycounter;
      char cmd_line[90];
      cio_print((char *) "$");
      char c = cio_getc();
      while(c != '\r')
      {
        if(c== 0x08)
        {
          if (j!= 0)
          {
            cmd_line[--j]= 0;
            cio_print(0x08);
            cio_printc(' ');
            cio_printc(0x08);
          }
        }
        else
        {
          cmd_line[j++] = c;
          cio_printc(c);
        }
        c= cio_getc();
      }
      cio_print((char *) '\n');
    }
    cio_print((char *) "I'm waiting for your character!\n\r");
    char c = cio_getc();
    cio_printc(c);
    cio_print((char *) "\n\r");
    for(;;)
    {
      P1OUT ^= BIT6;
      for(int i= 0; i < 0x6000;i ++)
      {
        int n;

           printf("Enter an integer\n");
           scanf("%d", &n);

           if (n%2 == 0)
              printf("Even\n");
           else
              printf("Odd\n");
      }
      for(int i = 0; i < 4; i++) {
        P1OUT ^= 0b01000001; // toggle both LEDs
        // P1OUT = P1OUT ^ 0b01000001;
        __delay_cycles(1000000);
}
    }
}
