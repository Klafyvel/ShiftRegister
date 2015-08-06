#include "shiftRegister.h"

ShiftRegister::ShiftRegister(uint8_t shcp, uint8_t stcp, uint8_t ds)
{
    this->shcp_port = getPORTPtrForDigital(shcp);
    this->shcp_bit = getBITForDigital(shcp);
    getDDRForDigital(shcp) |= 1 << this->shcp_bit;

    this->stcp_port = getPORTPtrForDigital(stcp);
    this->stcp_bit = getBITForDigital(stcp);
    getDDRForDigital(stcp) |= 1 << this->stcp_bit;

    this->ds_port = getPORTPtrForDigital(ds);
    this->ds_bit = getBITForDigital(ds);
    getDDRForDigital(ds) |= 1 << this->ds_bit;

    setBit(*this->shcp_port, this->shcp_bit, 0);
    setBit(*this->stcp_port, this->stcp_bit, 0);
}

void ShiftRegister::sendByte(uint8_t byte)
{
    for(int i=7; i>=0; i--)
    {
        ShiftRegister::sendBit(!!((1 << i) & byte));
        ShiftRegister::shift();
    }
} 
void ShiftRegister::sendBytes(uint8_t bytes[], uint8_t nb_bytes)
{
    for(int i=nb_bytes-1; i>=0; i--) {
        this->sendByte(bytes[i]);
    }

    ShiftRegister::storage();
}
void ShiftRegister::shift()
{
        setBit(*this->shcp_port, this->shcp_bit, 1);
        setBit(*this->shcp_port, this->shcp_bit, 0);
}
void ShiftRegister::storage()
{
    setBit(*this->stcp_port, this->stcp_bit, 1);
    setBit(*this->stcp_port, this->stcp_bit, 0);
}
void ShiftRegister::sendBit(bool bit)
{
    setBit(*this->ds_port, this->ds_bit, bit); 
}