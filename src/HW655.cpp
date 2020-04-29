#include <string>
#include <Arduino.h>

class HW655
{
    private:
        uint32_t iteration_counter;
        HardwareSerial *uart = nullptr;  
        bool is_on = false;
    public:
        const std::string device_uuid;
        const uint32_t poll_rate;
        const uint8_t uart_number;

    HW655(const std::string device_uuid, const uint32_t poll_rate, const uint8_t uart_number):
        device_uuid(device_uuid), poll_rate(poll_rate), uart_number(uart_number)
    {          
        iteration_counter = poll_rate;

        switch(uart_number) 
        {
            case 0:
                uart = &Serial;
                break;
            case 1 :
                uart = &Serial1; 
                break;
            case 2 :
                uart = &Serial2;
                break;    
        }
        if (uart_number == 1)
            uart->begin(9600, SERIAL_8N1, 5, 18);
        else
            uart->begin(9600, SERIAL_8N1);    
    }

    bool decrease_counter()
    {
        iteration_counter--;

        if (iteration_counter == 0) 
        {
            iteration_counter = poll_rate;
            return true;
        }
        return false;
    }

    void turn_on() 
    {
        uart->flush();
        uart->write("\xa0\x01\x01\xa2");
        is_on = true;
    }

    void turn_off() 
    {
        uart->flush();
        uart->write("\xa0\x01");
        uart->write(0x00);
        uart->write(0xa1);
        is_on = false;
    }

    bool get_status()
    {
        return is_on;
    }
};