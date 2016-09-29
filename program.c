#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1DIR |= 0b01000001; // direction output for P1.0 and P1.6
    P1OUT |= 0b01000001; // set P1.0 and P1.6 ON

    serial_init(9600);

while(1) {
    int num = 0;
    int power10 = 1;
    int arraycounter[4];
    cio_print("Please enter an integer: \n\r");
    char c;
    int i;
    int j;
    int g;
    for(i =0; i < 4; i++)
    {
        c = cio_getc();
        cio_printc(c);
        arraycounter[i] = c -'0';
    }
    for(j =0; j < i-1; j++)
    {
      power10 *=10;
    }
    for(g =0;g < 4; g++){
        num += arraycounter[g]*power10;
        power10/= 10;
    }
    cio_printf("number is %i", num);
    if(num%2==0){
      cio_printf("%s\n","The entered number is even\n\r");
      P1OUT ^= 0b01000001; // toggle both LEDs
      P1OUT = P1OUT ^ 0b01000001;
      __delay_cycles(1000000);
    }
    else{
      cio_printf("%s\n", "The entered  integer is odd\n\r");
      P1OUT ^= 0b01000001; // toggle both LEDs
      P1OUT = P1OUT ^ 0b01000001;
      __delay_cycles(1000000);
    }
  }
    return 0;
}
