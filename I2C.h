#define DEVICE_ADDRESS 0x27
#define CONTROL_REGISTER 0xBC
#define DATA_REGISTER 0xBB
#define START 0xA4
#define CLEAR_INTERRUPT 0x84
#define STOP 0x94
// I2C communication
void delay1();
void I2C_start();
void I2C_send(volatile unsigned char);
void I2C_stop();
void command(volatile unsigned char);
void LCD_command();
void outdata(volatile unsigned char);
void I2C_write(volatile char *);






void delay1(char num) {
    volatile long i;
    while (num) {
        for (i = 0; i < 80000; i++);
        num--;
    }
}
void I2C_start() {
    volatile char *twcr = (volatile char *)CONTROL_REGISTER;
    *twcr = START;
    while (!(*twcr & 0x80)); // waiting for interrupt bit to set, i.e., making it to 0
}
void delay1() {
    volatile long i;
    for (i = 0; i < 1000; i++);
}
void I2C_send(volatile unsigned char num) {
    volatile char *twdr = (volatile char *)DATA_REGISTER;
    volatile char *twcr = (volatile char *)CONTROL_REGISTER;
    *twdr = num;
    *twcr = CLEAR_INTERRUPT;
    while (!(*twcr & 0x80)); // waiting for interrupt bit to set, i.e., making it to 0
}
void I2C_stop() {
    volatile char *twcr = (volatile char *)CONTROL_REGISTER;
    *twcr = STOP;
}
void command(volatile unsigned char data) {
    volatile char data1;
    data1 = (data & 0xF0);
    I2C_send(data1 | 0x0C);   // enable on, RS off
    delay1();
    I2C_send(data1 | 0x08);   // enable off, RS off
    delay1();
    data1 = ((data << 4) & 0xF0);
    I2C_send(data1 | 0x0C);   // enable on, RS off
    delay1();
    I2C_send(data1 | 0x08);   // enable off, RS off
    delay1();
}
void LCD_command() {
    command(0x02);
    command(0x01);
    command(0x28);
    command(0x0C);
    command(0x06);
}
void I2C_write(volatile char *ptr) {
    while (*ptr) {
        outdata(*ptr);
        ptr++;
    }
}
void outdata(volatile unsigned char data) {
    volatile char data1;
    data1 = (data & 0xF0);
    I2C_send(data1 | 0x0D);   // enable on, RS on
    delay1();
    I2C_send(data1 | 0x09);   // enable off, RS on
    delay1();
    data1 = ((data << 4) & 0xF0);
    I2C_send(data1 | 0x0D);   // enable on, RS on
    delay1();
    I2C_send(data1 | 0x09);   // enable off, RS on
    delay1();
}
