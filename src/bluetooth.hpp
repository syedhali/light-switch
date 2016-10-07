#ifndef LIGHT_SWITCH_BLUETOOTH
#define LIGHT_SWITCH_BLUETOOTH

#include <Arduino.h>
#include <BLEPeripheral.h>
#include <SPI.h>
#include "constants.hpp"

namespace light_switch {

using namespace constants::bluetooth;

enum class Value : char {
    OFF = 0,
    ON = 1
};

typedef void ( *ValueChangeHandler )( Value value );

class Bluetooth {
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

    /**
     * The bluetooth value change handler
     */
    ValueChangeHandler mValueChangeHandler;

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

    ~Bluetooth() {
        if ( mBLEPeripheral.connected() ) {
            mBLEPeripheral.disconnect();
        }
    };

    void begin() {
        mBLEPeripheral.begin();
    }

    void handleSwitchCharacteristicWritten( BLECentral &central, BLECharacteristic &characteristic ) {
        if ( mValueChangeHandler ) {
            char value = mSwitchCharacteristic.value();
            mStateCharacteristic.setValue( value );
            mValueChangeHandler( value == 0 ? Value::OFF : Value::ON );
        }
    }

    BLECharacteristic getSwitchCharacteristic() {
        return mSwitchCharacteristic;
    }

    void poll() {
        mBLEPeripheral.poll();
    }

    void setValueChangedHandler( BLECharacteristicEventHandler characteristicHandler, ValueChangeHandler changeHandler ) {
        mSwitchCharacteristic.setEventHandler( BLEWritten, characteristicHandler );
        mValueChangeHandler = changeHandler;
    }

    void setValue( Value value ) {
        mStateCharacteristic.setValue( static_cast<char>( value ) );
        mSwitchCharacteristic.setValue( static_cast<char>( value ) );
    }

    void setValueWithState( uint8_t state ) {
        Value value = state == LOW ? Value::OFF : Value::ON;
        setValue( value );
    }
};
}

#endif /* end of include guard: LIGHT_SWITCH_BLUETOOTH */
