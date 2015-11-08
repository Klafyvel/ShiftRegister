#ifndef H_SHIFTREGISTER
#define H_SHIFTREGISTER

#include "Arduino.h"

/* ShiftRegister class
 * Works on Arduino Uno
 *
 * shcp -> shift clock (pin 11 on 74HC595)
 * stcp -> storage clock (pin 12 on 74HC595)
 * ds   -> data send (pin 14 on 74HC595)
 */

#define setBit(byte, bit, state) byte = (byte & ~(1 << bit)) | (state << bit)

#define mapPin(pin, left, right) (pin<8?left:right)

#define getPORTPtrForDigital(pin) mapPin(pin, &PORTD, &PORTB)
#define getDDRPtrForDigital(pin) mapPin(pin, &DDRD, &DDRB)
#define getPINPtrForDigital(pin) mapPin(pin, &PIND, &PINB)

#define getPORTForDigital(pin) mapPin(pin, PORTD, PORTB)
#define getDDRForDigital(pin) mapPin(pin, DDRD, DDRB)
#define getPINForDigital(pin) mapPin(pin, PIND, PINB)

#define getBITForDigital(pin) mapPin(pin, pin, pin-8)

class ShiftRegister
{
public:
    ShiftRegister(uint8_t shcp, uint8_t stcp, uint8_t ds);
    void sendByte(uint8_t byte);
    void sendBytes(uint8_t bytes[], uint8_t nb_bytes);
    void shift();
    void storage();
    void sendBit(bool bit);
protected:
    volatile uint8_t* shcp_port;
    volatile uint8_t* stcp_port;
    volatile uint8_t* ds_port;
    uint8_t shcp_bit;
    uint8_t stcp_bit;
    uint8_t ds_bit;
};

#include "shiftRegister.cpp"

#endif