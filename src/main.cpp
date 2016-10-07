#include <Arduino.h>
#include "bluetooth.hpp"
#include "constants.hpp"
#include "utils.hpp"

using namespace light_switch;
using namespace light_switch::constants;
using namespace light_switch::constants::pins;
using namespace light_switch::constants::serial;
using namespace light_switch::utils;

// Instance Variables

Bluetooth mBluetooth;

/**
 * Current state of the button pin
 */
uint8_t mCurrentState = LOW;

/**
 * Debounce state of the button pin (occurs after a delay after the current
 * state)
 */
uint8_t mDebouncedState = LOW;

/**
 * The current state of the push button
 */
uint8_t mSwitchState = LOW;

/**
 * The current state of the output LED
 */
uint8_t mLedState = LOW;

//
// Application
//

/**
 * Main initalizer method
 */
void setup() {
    Serial.begin( SERIAL_BAUD_RATE );

    //
    // Setup the pin modes for input and output
    //
    pinMode( LED_PIN, OUTPUT );
    pinMode( BUTTON_PIN, INPUT );

    //
    // Begin the bluetooth
    //
    mBluetooth = Bluetooth();
    mBluetooth.begin();

    //
    // Setup the serial monitor
    //
    Serial.println( "Smart Light Switch" );
}

/**
 * Main loop method (application body)
 */
void loop() {
    mBluetooth.poll();

    //
    // Read the current state values (use software debouncing to check state
    // after 10ms delay for better accuracy)
    //
    mCurrentState = digitalRead( BUTTON_PIN );
    delay( DEBOUNCE_DELAY_INTERVAL );
    mDebouncedState = digitalRead( BUTTON_PIN );

    //
    // Only process when the current state and the debounced state are the
    // same (indicating there was an actual state change)
    //
    if ( mCurrentState == mDebouncedState ) {
        //
        // Only change if the current state is different than the switch state
        //
        if ( mCurrentState != mSwitchState ) {
            if ( mCurrentState == LOW ) {
                //
                // Button was released
                //
            } else {
                //
                // Button was pressed down
                //
                mLedState = mLedState == LOW ? HIGH : LOW;
                digitalWrite( LED_PIN, mLedState );

                //
                // Log out new LED state
                //
                Serial.println( String( "LED State changed: " ) +
                                StringFromState( mLedState ) );
            }
            mSwitchState = mCurrentState;
        }
    }
}
