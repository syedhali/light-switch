#ifndef LIGHT_SWITCH_CONSTANTS
#define LIGHT_SWITCH_CONSTANTS

#include <Arduino.h>

namespace light_switch {
namespace constants {

/**
 * Represents the delay interval
 */
const unsigned long DEBOUNCE_DELAY_INTERVAL = 10;

namespace bluetooth {
/**
 * BLE REQ parameter
 */
unsigned char REQ = 10;

/**
 * BLE RDY parameter
 */
unsigned char RDY = 2;

/**
* BLE RST parameter
 */
unsigned char RST = 9;

namespace service {
/**
 * The UUID representing the BLE Service
 */
const char *UUID = "FF10";
}

namespace state_characteristic {
/**
 * The UUID representing the BLE State characteristic
 */
const char *UUID = "FF12";
}

namespace state_descriptor {
/**
 * The UUID representing the BLE State descriptor
 */
const char *UUID = "2902";
}

namespace switch_characteristic {
/**
 * The UUID representing the BLE Switch characteristic
 */
const char *UUID = "FF11";
}

namespace switch_descriptor {
/**
 * The UUID representing the BLE Switch descriptor
 */
const char *UUID = "2901";
}
}

namespace pins {
/**
 * Represents the input button pint we're using to detect whether the LED
 * should be on.
 */
const uint8_t BUTTON_PIN = 4;

/**
 * Represents the output LED port we're going to make blink!
 */
const uint8_t LED_PIN = 3;
}

namespace serial {
/**
 * The baud rate of the serial monitor. Currently set to 9600.
 */
const unsigned long SERIAL_BAUD_RATE = 9600;
}
}
}

#endif
