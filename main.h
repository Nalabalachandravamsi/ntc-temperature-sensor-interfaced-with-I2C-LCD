#include "ADC.h"
#include "I2C.h"
void setup() {
    // ntc temperature ADC setup
    port_intialization();
    temp_sensor_intialization();
    result();
    reverse_number(adcResult);
    convert_to_string(answer);
    //  I2C communication setup
    I2C_start();
    I2C_send((DEVICE_ADDRESS << 1));
    LCD_command();
    command(0x80);
    I2C_write("Temperature is ");       
    command(0xC5);
    I2C_write(str_ptr);
    I2C_stop();
}

void loop() {
    // put your main code here, to run repeatedly:
}
