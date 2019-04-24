#include <16F886.h>
#device ADC=10 *=16
#device PASS_STRINGS=IN_RAM

#FUSES NOWDT //No Watch Dog Timer
#FUSES PUT //Power Up Timer
#FUSES NOMCLR //Master Clear pin not enabled
#FUSES NOPROTECT //Code not protected from reading
#FUSES NOCPD //No EE protection
#FUSES BROWNOUT //Brownout reset
#FUSES IESO //Internal External Switch Over mode enabled
#FUSES FCMEN //Fail-safe clock monitor enabled
#FUSES NOLVP //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG //No Debug mode for ICD
#FUSES NOWRT //Program memory not write protected
#FUSES BORV40 //Brodddddwnout reset at 4.0V
#FUSES RESERVED //Used to set the reserved FUSE bits
#FUSES INTRC_IO 

#use delay(clock=8M)

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#include <string.h>

void main() {
    setup_adc_ports(sAN0); // setup PIN A0 as analog input 
    setup_adc( ADC_CLOCK_INTERNAL ); 
    set_adc_channel( 0 ); // set the ADC chaneel to read 
    delay_us(100); // wait for the sensor reading to finish
   char store[20] = "";
   char temp_store[60] = "";
   char text[20] = "";
   int idx = 0;
   int filter, count, temp_count;
   while(1){
      if(read_adc() > 3){
         delay_ms(1500);
         for(temp_count = 0;temp_count < 18;temp_count++){
            if(read_adc() > 3){
               temp_store[temp_count] = '1';
            }else{
               temp_store[temp_count] = '0';
            }
            output_high(PIN_A1);
            delay_ms(100);
            output_low(PIN_A1);
            delay_ms(400);
         }
         while(temp_store[--temp_count] == '0');
         temp_count = temp_count - 2;
         temp_store[temp_count] = '\0';
         printf("%s final\n",temp_store);
         int ii = 0;
         count = 0;
         while(ii < temp_count){
            filter = 0;
            for(int i=0;i<3;i++){
               if(temp_store[ii] == '1'){
                  filter++;
               }
               ii++;
            }
            if(filter < 2){
               store[count] = '0';
            }else{
               store[count] = '1';
            }
            count++;
         }
         store[count] = '\0';
         printf("Input: %s\n",temp_store);
         printf("Store: %s\n",store);
         if (strcmp(store, "01") == 0) {
            printf("A\n");
            text[idx] = 'A';
         }else if (strcmp(store, "1000") == 0) {
            printf("B\n");
            text[idx] = 'B';
         }else if (strcmp(store, "1010") == 0) {
            printf("C\n");
            text[idx] = 'C';
         }else if (strcmp(store, "100") == 0) {
            printf("D\n");
            text[idx] = 'D';
         }else if (strcmp(store, "0") == 0) {
            printf("E\n");
            text[idx] = 'E';
         }else if (strcmp(store, "0010") == 0) {
            printf("F\n");
            text[idx] = 'F';
         }else if (strcmp(store, "110") == 0) {
            printf("G\n");
            text[idx] = 'G';
         }else if (strcmp(store, "0000") == 0) {
            printf("H\n");
            text[idx] = 'H';
         }else if (strcmp(store, "00") == 0) {
            printf("I\n");
            text[idx] = 'I';
         }else if (strcmp(store, "0111") == 0) {
            printf("J\n");
            text[idx] = 'J';
         }else if (strcmp(store, "101") == 0) {
            printf("K\n");
            text[idx] = 'K';
         }else if (strcmp(store, "0100") == 0) {
            printf("L\n");
            text[idx] = 'L';
         }else if (strcmp(store, "11") == 0) {
            printf("M\n");
            text[idx] = 'M';
         }else if (strcmp(store, "10") == 0) {
            printf("N\n");
            text[idx] = 'N';
         }else if (strcmp(store, "111") == 0) {
            printf("O\n");
            text[idx] = 'O';
         }else if (strcmp(store, "0110") == 0) {
            printf("P\n");
            text[idx] = 'P';
         }else if (strcmp(store, "1101") == 0) {
            printf("Q\n");
            text[idx] = 'Q';
         }else if (strcmp(store, "010") == 0) {
            printf("R\n");
            text[idx] = 'R';
         }else if (strcmp(store, "000") == 0) {
            printf("S\n");
            text[idx] = 'S';
         }else if (strcmp(store, "1") == 0) {
            printf("T\n");
            text[idx] = 'T';
         }else if (strcmp(store, "001") == 0) {
            printf("U\n");
            text[idx] = 'U';
         }else if (strcmp(store, "0001") == 0) {
            printf("V\n");
            text[idx] = 'V';
         }else if (strcmp(store, "011") == 0) {
            printf("W\n");
            text[idx] = 'W';
         }else if (strcmp(store, "1001") == 0) {
            printf("X\n");
            text[idx] = 'X';
         }else if (strcmp(store, "1011") == 0) {
            printf("Y\n");
            text[idx] = 'Y';
         }else if (strcmp(store, "1100") == 0) {
            printf("Z\n");
            text[idx] = 'Z';
         }else if (strcmp(store, "11111") == 0) {
            printf("0\n");
            text[idx] = '0';
         }else if (strcmp(store, "01111") == 0) {
            printf("1\n");
            text[idx] = '1';
         }else if (strcmp(store, "00111") == 0) {
            printf("2\n");
            text[idx] = '2';
         }else if (strcmp(store, "00011") == 0) {
            printf("3\n");
            text[idx] = '3';
         }else if (strcmp(store, "00001") == 0) {
            printf("4\n");
            text[idx] = '4';
         }else if (strcmp(store, "00000") == 0) {
            printf("5\n");
            text[idx] = '5';
         }else if (strcmp(store, "10000") == 0) {
            printf("6\n");
            text[idx] = '6';
         }else if (strcmp(store, "11000") == 0) {
            printf("7\n");
            text[idx] = '7';
         }else if (strcmp(store, "11100") == 0) {
            printf("8\n");
            text[idx] = '8';
         }else if (strcmp(store, "11110") == 0) {
            printf("9\n");
            text[idx] = '9';
         }else if (strcmp(store, "10001") == 0) {
            //enter
            text[idx] = '\0';
            printf("Message: %s\n",text);
            idx = 0;
            text[0] = '\0';
            continue;
         }else if (strcmp(store, "10011") == 0) {
            //clear
            idx = 0;
            text[0] = '\0';
            printf("Message: %s\n",text);
            continue;
         }else if (strcmp(store, "10111") == 0) {
            //backspace
            idx == 0 ? 0:idx--;
            text[idx] = '\0';
            printf("Message: %s\n",text);
            continue;
         }else{
            //output_high(PIN_A1);
            printf("404 NOT FOUND!\n");
            continue;
         }
         idx++;
      }
   }
}
