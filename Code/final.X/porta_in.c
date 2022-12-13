#include <xc.h>
#include <inttypes.h>
#include "porta_in.h"
void porta_in_init() {
    TRISA = 0x03;
    ANSELA = 0;
    CNPUA = 0x03;
}
uint8_t porta_in_read() {
    uint8_t val;
    val = PORTA & 0x03;
    return val;
}
