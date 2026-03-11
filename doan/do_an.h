#include <16F887.h>
#fuses NOWDT, HS, PUT, BROWNOUT, NOLVP
#device ADC=10
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits=8, parity=N, stop=1)
#use i2c(master,slow,sda=pin_c4,scl=pin_c3)   
#include <LibraryLCD.h>
#include <LibraryRealtime.h>
#include <LibraryKeypad.h>
//#include <TestMode.h>
void Init(){
   set_tris_a(0);
   set_tris_c(0x80); //binary=10000000, C7 is input, C0>C6 is output.
   set_tris_b(0xf0); port_b_pullups(0xf0);
   set_tris_e(0);   
   set_tris_d(0b10000000);
   output_c(0x00); 
   output_low(pin_D6);
   output_high(LED_WAIT);
   lcd_setup();
   lcd_command(0x40);
   for(int m=0;m<64;m++){lcd_data(lcd_ma_8doan[m]);}
   //lcd_command(0x80); lcd_data("DarTC");
   //lcd_command(0xC0); lcd_data("2,4,0,1,0,4");
   
   //testsetup();
}
