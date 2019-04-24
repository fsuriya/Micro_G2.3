#include <16F886.h>
#device ADC=10 *=16
#device PASS_STRINGS=IN_RAM

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO 

#use delay(clock=8M)

////////////////////////////////////////////////////////////
//define LCD Display 
////////////////////////////////////////////////////////////
#define SLAVE_ADDRESS  0xB0
#define DISPLAY_ADDRESS 0xB4
#define REGISTER_SIZE  8   
#define DISPLAY_CMD_SEND_VALUE 2
#define DISPLAY_CMD_SEND_LONG_TEXT 5
#define DISPLAY_CMD_CLS 6
#define DISPLAY_CMD_SETPOS 8
#define DEVICE_DEF     1
#define starttime 65511
////////////////////////////////////////////////////////////
//define LCD Display 
////////////////////////////////////////////////////////////

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

// setup the I2C port
#use i2c(MASTER, I2C1, FORCE_HW)

#define RUN_BUTTON   PIN_B7

void displayLongText(char* text);
void displayValue(int16 value[]);
void clearDisplay();
void setDisplayPos(int pos);

void main(void) {
   // ------- Collect Input into store -------
   int i;
   printf("00 lllll\n");
   while(1){
      boolean push = false, enter = false, clear = false;
      char store[50] ="1";
      i=1;
      //set LCD;
      printf("01 lllll\n");
//!      setDisplayPos(1);/////
//!      displayLongText("zz");/////
      printf("02 lllll\n");
      while(!enter){
//!      setDisplayPos(1);///////
//!      displayLongText("oo");///////
         if(push == false){
            if(input(PIN_B3)){
               store[i++]='1';
               store[i]='\0';
               enter = true;
               output_high(PIN_A2);
               delay_ms(150);
               output_low(PIN_A2);
            }else if(input(PIN_B2)){
               store[i++]='1';
               store[i]='\0';
               push =true;
               output_high(PIN_A2);
               delay_ms(200);
               output_low(PIN_A2);
            }else if(input(PIN_B1)){
               store[i++]='0';
               store[i]='\0';
               push =true;
               output_high(PIN_A2);
               delay_ms(100);
               output_low(PIN_A2);
            }else if(input(PIN_B0)){
               push =true;
               clear = true;
               output_high(PIN_A2);
               delay_ms(150);
               output_low(PIN_A2);
            }
         }else{
            if(!(input(PIN_B0) || input(PIN_B1) || input(PIN_B2) || input(PIN_B3))){
               if(i > 6){
                  printf("404 NOT FOUND!\n");
                  output_high(PIN_A2);
                  delay_ms(300);
                  output_low(PIN_A2);
                  clear = true;
               }
               if(clear) break;
               push =false;
//!               setDisplayPos(1);///////
//!               displayLongText("gg");////
               printf("%s\n",store);
            }
         }
         //clearDisplay();//////
      }
      if(clear){
         printf("CLEAR!\n");
         continue;
      }
      printf("%s Output\n",store);
      int q = 0;
      while(store[q]){
         printf("sending : %c \n",store[q]);
         if(store[q] == '0'){
            output_low(PIN_A0);
         }else{
            output_high(PIN_A0);
         }
         q++;
         delay_ms(1500);
      }
      output_low(PIN_A0);
   }
   //clearDisplay();///////
}

// ----------- Function ------------------
void displayLongText(char* text) {
   int i ;
   i2c_start();
   i2c_write(DISPLAY_ADDRESS);
   i2c_write(DISPLAY_CMD_SEND_LONG_TEXT);
   i=0;
   while(text[i]){
      i2c_write(text[i]);
      i++;
   }
   i2c_write('\0');
   i2c_stop();
}

void displayValue(int16 value[]) {
   i2c_start();
   i2c_write(DISPLAY_ADDRESS);
   i2c_write(DISPLAY_CMD_SEND_VALUE);
   i2c_write((int)(value>>8)); // high byte
   i2c_write((int)(value & 0xFF)); // low byte
   i2c_write('\0');
   i2c_stop();
   
}

void clearDisplay(){
   i2c_start();
   i2c_write(DISPLAY_ADDRESS);
   i2c_write(DISPLAY_CMD_CLS);
   i2c_stop();
}

void setDisplayPos(int pos){
   i2c_start();
   i2c_write(DISPLAY_ADDRESS);
   i2c_write(DISPLAY_CMD_SETPOS);
   i2c_write(pos);
   i2c_write('\0');
   i2c_stop();
}
