#ifndef LIGHT_SWITCH_UTILS
#define LIGHT_SWITCH_UTILS

#include <Arduino.h>

namespace light_switch {
namespace utils {
/**
 * Converts a int representing a pin state value into a human readable
 * string.
 * @param  state A uint8_t representing the pin state
 * @return A String representing the state, either "ON" if the state is HIGH
 * or "OFF" is the state is LOW
 */
String StringFromState( uint8_t state ) {
    return state == LOW ? "OFF" : "ON";
}
}
}

#endif
