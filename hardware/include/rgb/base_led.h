#ifndef BASELED_H
#define BASELED_H

#include <Arduino.h>

class BaseLed {
    protected:
        uint32_t color;
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint32_t buildColor(uint8_t red, uint8_t green, uint8_t blue);
    public:
        BaseLed();
        virtual void setColor(uint8_t red, uint8_t green, uint8_t blue);
        uint32_t getColor();
        uint8_t getRed();
        uint8_t getGreen();
        uint8_t getBlue();
};

BaseLed::BaseLed(){
    this->red = 0,
    this->green = 0;
    this->blue = 0;
    this->color = this->buildColor(0, 0, 0);
}

uint32_t BaseLed::buildColor(uint8_t red, uint8_t green, uint8_t blue){
    return 0x00000000 | (uint32_t(red) << 16 | uint32_t(green) << 8 | uint32_t(blue));
}

uint32_t BaseLed::getColor(){
    return this->color;
}

uint8_t BaseLed::getRed(){
    return this->red;
}

uint8_t BaseLed::getGreen(){
    return this->green;
}

uint8_t BaseLed::getBlue(){
    return this->blue;
}

#endif