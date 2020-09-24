#include <stdio.h>
#include <assert.h>
#include "../crc16.h"
#include "../crc8.h"

unsigned char data[] = "123456789";

int main(void) {
    uint16_t crc16_val = CRC16_INIT;
    assert(!crc16(&crc16_val, data, 9));
    crc16_val = CRC16_FINALIZE(crc16_val);
    assert(crc16_val == 0x906e);

    uint8_t crc8_val = CRC8_INIT;
    assert(!crc8(&crc8_val, data, 9));
    assert(crc8_val == 0xda);

    printf("tests passed\r\n");
    return 0;
}