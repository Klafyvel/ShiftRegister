#include "shiftRegister.h"

ShiftRegister::ShiftRegister(uint8_t shcp, uint8_t stcp, uint8_t ds)
{
    if(shcp >= 0 && shcp <= 7)
    {
        this->shcp_port = &PORTD;
        this->shcp_bit = shcp;
        DDRD |= 1<<this->shcp_bit;
    }
    else if (shcp >= 8 && shcp <= 13)
    {
        this->shcp_port = &PORTB;
        this->shcp_bit = shcp - 8;
        DDRB |= 1<<this->shcp_bit;
    }

    if(stcp >= 0 && stcp <= 7)
    {
        this->stcp_port = &PORTD;
        this->stcp_bit = stcp;
        DDRD |= 1<<this->stcp_bit;
    }
    else if (stcp >= 8 && stcp <= 13)
    {
        this->stcp_port = &PORTB;
        this->stcp_bit = stcp - 8;
        DDRB |= 1<<this->stcp_bit;
    }

    if(ds >= 0 && ds <= 7)
    {
        this->ds_port = &PORTD;
        this->ds_bit = ds;
        DDRD |= 1<<this->ds_bit;
    }
    else if (ds >= 8 && ds <= 13)
    {
        this->ds_port = &PORTB;
        this->ds_bit = ds - 8;
        DDRB |= 1<<this->ds_bit;
    }
    setBit(*this->shcp_port, this->shcp_bit, 0);
    setBit(*this->stcp_port, this->stcp_bit, 0);
}

void ShiftRegister::sendByte(uint8_t byte)
{
    for(int i=0; i<8; i++)
    {
        setBit(*this->ds_port, this->ds_bit, !!((1 << i) & byte)); 
        ShiftRegister::shift();
    }
} 
void ShiftRegister::sendBytes(uint8_t bytes[], uint8_t nb_bytes)
{
    for(int i=0; i<nb_bytes; i++)
        this->sendByte(bytes[i]);
    
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