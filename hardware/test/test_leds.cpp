#include <Arduino.h>
#include <unity.h>

#include <rgb/simple.h>

#define TEST_RED 0x64
#define TEST_GREEN 0xAB
#define TEST_BLUE 0xFF
#define TEST_COLOR 0x0054ABFF


void test_colors(BasicRGBLed &led) {
    TEST_ASSERT_EQUAL_UINT8(TEST_RED, led.getRed());
    TEST_ASSERT_EQUAL_UINT8(TEST_GREEN, led.getGreen());
    TEST_ASSERT_EQUAL_UINT8(TEST_BLUE, led.getBlue());
    TEST_ASSERT_EQUAL_UINT32(TEST_COLOR, led.getColor());
}

void setup() {
    UNITY_BEGIN();
}

int main() {
    BasicRGBLed led = BasicRGBLed();
    led.setColor(TEST_RED, TEST_GREEN, TEST_BLUE);
    test_colors(led);
    delay(1000);
    UNITY_END();
    return 0;
}
