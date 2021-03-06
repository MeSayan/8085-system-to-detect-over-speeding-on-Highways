#include<reg52.h> 
sbit LED = P1^0;
sfr LCD=0xA0; 
sbit RS=P0^5; 
sbit EN=P0^7; 

unsigned int a=0, i=0, v; 
void tm(); 
void delay(unsigned char time) 
{ unsigned int a,b; 
  for(a=0;a<time;a++) 
  for(b=0;b<1275;b++); 
} 
void lcdcmd(unsigned char value) 
{ LCD=value; 
  RS=0; 
  EN=1; 
  delay(10); 
  EN=0; 
} 
void lcddata(unsigned char value) 
{ LCD=value; 
  RS=1; 
  EN=1; 
  delay(10); 
  EN=0; 
} 
void lcd_init() 
{ lcdcmd(0x38); 
  delay(20);  
  lcdcmd(0x0c); 
  delay(20); 
  lcdcmd(0x01); 
  delay(20); 
  lcdcmd(0x06); 
  delay(20); 
} 
void ISR_ex0(void) interrupt 0 {
   while(1) {
      tm(); 
      a++; 
   } 
}

void ISR_ex1(void) interrupt 2
{ unsigned char m,n,temp,o; 
  if ( a != 0) {
     v=80/a; 
     m=v/100; 
     temp=v%100; 
     n=temp/10; 
     o=temp%10; 
     lcdcmd(0xc6); 
     lcddata(m+48); 
     lcddata(n+48); 
     lcddata(o+48); 
     a=0; 
     lcddata('m'); 
     lcddata('m'); 
     lcddata('/'); 
     lcddata('s'); 
     lcddata('e'); 
     lcddata('c'); 
     lcddata(' '); 
     lcddata(' '); 
  }
  else {
     lcdcmd(0xc6);
     lcddata('W');
     lcddata('A');
     lcddata('I');
     lcddata('T');
     lcddata('I');
     lcddata('N');
     lcddata('G');
     lcddata('.');
     lcddata('.');
  }
} 
void main() 
{ unsigned char w[]="WELCOMESPEED=WAITING..."; 
  IT0 = 1;   // Configure interrupt 0 for falling edge on /INT0 (P3.2) 
  EX0 = 1;   // Enable EX0 Interrupt  
  IT1 = 1;   // Configure interrupt 1 for falling edge on /INT0 (P3.2) 
  EX1 = 1;   // Enable EX1 Interrupt 
  EA = 1;    // Enable Global Interrupt Flag 
  IP=0x04;  // Priority of ex1 high 
  lcd_init(); 
  lcdcmd(0x84); 
  for(i=0;i<7;i++)  
  lcddata(w[i]); 
  lcdcmd(0xc0); 
  for(i=7;i<13;i++) 
  lcddata(w[i]); 
  for(i=13;i<24;i++) 
  lcddata(w[i]); 
  while(1) {
    delay(500);
    LED = ~LED;
    delay(500);
  } 
} 
void tm() 
{ int y=0; 
  for(y=0;y<15;y++) 
  { TMOD=0x01; 
    TL0=0xFD; 
    TH0=0x4B; 
    TR0=1; 
    while(TF0==0); 
    TR0=0; 
    TF0=0; 
  } 
} 

