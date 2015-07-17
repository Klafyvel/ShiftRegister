#include "shiftRegister.h"

const uint8_t SHCP = 6;
const uint8_t STCP = 5;
const uint8_t DS = 3;

ShiftRegister sr(SHCP,STCP,DS);

int val;
uint8_t tab[] = {0};
void setup() {
    sr.sendBytes(tab, 1);
    delay(500);
}

void loop() {
    tab[0] = 0xFFFF;
    sr.sendBytes(tab, 1);
}