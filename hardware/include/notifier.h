#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <Arduino.h>
#include <notification.h>

#define BUFF_SIZE 16

template <class LedClass>
class Notifier {
    private:
        void executeLeds(LedClass &led, uint8_t red, uint8_t green, uint8_t blue);
        Notification buffer[BUFF_SIZE];
        uint16_t available;
        uint8_t exec_index;
        unsigned long exec_timer;
        unsigned long exec_interval;
        LedClass led;
    public:
        Notifier(const LedClass led, long interval):led{led}{
            this->exec_timer = 0;
            this->exec_index = 0;
            this->available = 0xFFFF;
            this->exec_interval = interval;
        }
        void execute();
        bool addNotification(Notification notification);
        void cleanNotification(uint8_t source);
};

template <class LedClass>
void Notifier<LedClass>::executeLeds(LedClass &led, uint8_t red, uint8_t green, uint8_t blue){
    led.setColor(red, green, blue);
}

template <class LedClass>
void Notifier<LedClass>::execute(){
    if(millis() - this->exec_timer >= this->exec_interval) {
        if(!bitRead(this->available, this->exec_index)){
            this->exec_timer = millis();
            uint8_t red, green, blue;
            this->buffer[this->exec_index].getColorComponents(red, green, blue);
            this->executeLeds(this->led, red, green, blue);
        }
        if(this->available == 0xFFFF){
            this->executeLeds(this->led, 0, 0, 0);
        }
        exec_index += 1;
        if(exec_index > BUFF_SIZE-1){
            exec_index = 0;
        }
    }
}

template <class LedClass>
bool Notifier<LedClass>::addNotification(Notification notification){
    for(int i=BUFF_SIZE-1; i>=0; i--){
        if(bitRead(this->available, i)){
            this->buffer[i] = notification;
            bitWrite(this->available, i, 0);
            return true;
        }
    } 
    return false;
}

template <class LedClass>
void Notifier<LedClass>::cleanNotification(uint8_t source) {
    for(int i = 0; i<BUFF_SIZE; i++){
        if(buffer[i].getType() == source){
            bitWrite(this->available, i, 1);
            return;
        }
    }
}

#endif
