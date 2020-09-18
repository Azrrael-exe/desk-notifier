#ifndef BASICRGBLED_H
#define BASICRGBLED_H

#include <Arduino.h>
#include <rgb/base_led.h>

class BasicRGBLed : public BaseLed {
    private:
        uint8_t red_pin;
        uint8_t green_pin;
        uint8_t blue_pin;
    public:
        BasicRGBLed();
        BasicRGBLed(uint8_t red_pin, uint8_t gren_pin, uint8_t blue_pin);
        void init(void);
        void setColor(uint8_t red, uint8_t green, uint8_t blue);
};

BasicRGBLed::BasicRGBLed(){}

BasicRGBLed::BasicRGBLed(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin) {
    this->red_pin = red_pin;
    this->green_pin = green_pin;
    this->blue_pin = blue_pin;
}

void BasicRGBLed::init(void) {
    pinMode(red_pin, OUTPUT);
    pinMode(green_pin, OUTPUT);
    pinMode(blue_pin, OUTPUT);
}

void BasicRGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->color = this->buildColor(red, green, blue);
    analogWrite(this->red_pin, this->red);
    analogWrite(this->green_pin, this->green);
    analogWrite(this->blue_pin, this->blue);
}

#endif