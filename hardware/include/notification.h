#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <Arduino.h>

class Notification {
    private:
        uint8_t type;
        uint32_t color;
    public:
        Notification();
        Notification(uint8_t type, uint32_t color);
        uint8_t getType();
        uint32_t getColor();
        void getColorComponents(uint8_t &red, uint8_t &green, uint8_t &blue);
};

Notification::Notification(){}

Notification::Notification(uint8_t type, uint32_t color){
    this->type = type;
    this->color = color;
}

uint8_t Notification::getType(){
    return this->type;
}

uint32_t Notification::getColor(){
    return this->color;
}

void Notification::getColorComponents(uint8_t &red, uint8_t &green, uint8_t &blue) {
    red = uint8_t(this->color >> 16);
    green = uint8_t(this->color >> 8);
    blue = uint8_t(this->color);
}

#endif