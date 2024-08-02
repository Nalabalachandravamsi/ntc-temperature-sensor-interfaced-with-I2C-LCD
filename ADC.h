//  ntc temparture intilization
void port_intialization();
void temp_sensor_intialization();
void result();
void delay1(char);
void reverse_number(volatile long);
void convert_to_string(volatile long);


volatile long answer = 0;
volatile char *str_ptr;
volatile  unsigned char *ADCH1=0x79;
volatile  unsigned char *ADCL1=0x78;
volatile unsigned long adcResult;


void port_intialization() {
    volatile char *dirf = (volatile char *)0x30;
    volatile char *dirk = (volatile char *)0x107;
    *dirf = 0x00;
    *dirk = 0xFF;
}
void temp_sensor_intialization() {
    volatile char *ADMUX1 = (volatile char *)0x7C;
    volatile char *ADCSRB1 = (volatile char *)0x7B;
    volatile char *ADCSRA1 = (volatile char *)0x7A;
    *ADMUX1 = 0x00;     // enable ADC0
    *ADCSRB1 = 0x00;    // making ADC in free running mode
    *ADCSRA1 = 0xC7;    // enable ADC, start bit, and prescaler=128
}
void result() {
    volatile char *ADCSRA1 = (volatile char *)0x7A;
    volatile char *outk = (volatile char *)0x108;   
    while ((*ADCSRA1 & 0x40)) {  // waiting for start bit to become zero
        *outk = 0x01;
        delay1(2);
    }
    *outk = 0x02;
    adcResult = *ADCL1;
    adcResult = (*ADCH1 << 8) | *ADCL1;  
}
void reverse_number(volatile long num) {
    volatile long rev = 0;
    while (num) {
        rev = rev * 10 + (num % 10);
        num = num / 10;
    }
    answer = rev;   
}
void convert_to_string(volatile long num) {
    volatile char s[10];
    volatile char *ptr = s;
    volatile long data = num;
    // Convert each digit to character and store it in the buffer
    while (data) {
      *ptr = (data % 10) + 48; // Convert digit to character
      data = data / 10;
      ptr++;
    }
    *ptr = '\0'; // Null-terminate the string
    str_ptr= s;   
}





