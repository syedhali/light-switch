#ifndef LIGHT_SWITCH_BLUETOOTH
#define LIGHT_SWITCH_BLUETOOTH

#include <Arduino.h>
#include <BLEPeripheral.h>
#include <SPI.h>
#include "constants.hpp"

namespace light_switch {

using namespace constants::bluetooth;

class Bluetooth {
    enum Value { OFF = 0,
                 ON = 1 };

private:
    /**
     * The bluetooth peripheral instance
     */
    BLEPeripheral mBLEPeripheral = BLEPeripheral( REQ, RDY, RST );

    /**
     * The bluetooth service
     */
    BLEService mBLEService = BLEService( service::UUID );

    /**
     * The bluetooth characteristic describing the switch
     */
    BLECharCharacteristic mSwitchCharacteristic = BLECharCharacteristic( switch_characteristic::UUID, BLERead | BLEWrite );

    /**
     * The bluetooth descriptor describing the switch
     */
    BLEDescriptor mSwitchDescriptor = BLEDescriptor( switch_descriptor::UUID, "Switch" );

    /**
     * The bluetooth characteristic describing the state
     */
    BLECharCharacteristic mStateCharacteristic = BLECharCharacteristic( state_characteristic::UUID, BLENotify );

    /**
     * The bluetooth descriptor describing the state
     */
    BLEDescriptor mStateDescriptor = BLEDescriptor( state_descriptor::UUID, "State" );

public:
    Bluetooth() {
        mBLEPeripheral.setLocalName( "Light Switch" );
        mBLEPeripheral.setDeviceName( "Smart Light Switch" );
        mBLEPeripheral.setAdvertisedServiceUuid( mBLEService.uuid() );

        mBLEPeripheral.addAttribute( mBLEService );
        mBLEPeripheral.addAttribute( mSwitchCharacteristic );
        mBLEPeripheral.addAttribute( mSwitchDescriptor );
        mBLEPeripheral.addAttribute( mStateCharacteristic );
        mBLEPeripheral.addAttribute( mStateDescriptor );
    }

    void begin() {
        Serial.println( "Bluetooth beginning meow" );
        mBLEPeripheral.begin();
        Serial.println( "Bluetooth done beginning meow" );
    }

    void poll() {
        mBLEPeripheral.poll();
    }

    void setValue( Value value ) {
        mStateCharacteristic.setValue( (char)value );
        mSwitchCharacteristic.setValue( (char)value );
    }
};
}

#endif /* end of include guard: LIGHT_SWITCH_BLUETOOTH */
