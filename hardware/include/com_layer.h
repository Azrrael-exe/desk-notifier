#ifndef COM_LAYER_H
#define COM_LAYER_H

#include <Arduino.h>
#include <notification.h>

// Sample ADD: 7E051C0A00006475
// Sample Remove: 7E022C0AC9
// Sample ADD: 7E051C0B64006410
// Sample Remove: 7E022C0BC8

#define ADD 0x1C
#define REMOVE 0x2C
#define MAX_BUFFER 64

class ComLayer {
    private:
        uint8_t header;
        uint8_t command;
        uint8_t len;
        uint8_t buffer[MAX_BUFFER];
    public:
        ComLayer(uint8_t header);
        bool available(Stream &uart);
        uint8_t getCommand();
        uint8_t getLength();
        void getPayload(uint8_t *payload);
};

ComLayer::ComLayer(uint8_t header) {
    this->header = header;
};

bool ComLayer::available(Stream &uart){
    if(uart.available() >= 3){
        if(uart.read() == this->header){
            uint8_t len = uart.read();
            uint8_t command = uart.read();
            if(len >= BUFF_SIZE) {
                return false;
            }
            uint8_t input_buffer[len];
            uart.readBytes(input_buffer, len);
            uint8_t recived_chk = input_buffer[len-1];
            uint8_t calculated_chk = command;
            for(int i=0; i<len-1; i++){
                calculated_chk+=input_buffer[i];
            }
            if(uint8_t(0xFF-calculated_chk) == recived_chk){
                this->len = len-1;
                this->command = command;
                for(int i=0; i<len; i++){
                    this->buffer[i] = input_buffer[i];   
                }
                return true;
            }
        }
    }
    return false;
}

uint8_t ComLayer::getLength(){
    return this->len;
}

uint8_t ComLayer::getCommand(){
    return this->command;
}

void ComLayer::getPayload(uint8_t *payload){
    for(int i = 0; i<this->len; i++){
        *payload++= buffer[i];
    }
}

#endif