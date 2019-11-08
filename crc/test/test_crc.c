#include <assert.h>
#include "../crc16.h"

unsigned char data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main(void) {
    uint16_t crc16_val = CRC16_INIT;
    assert(!crc16(&crc16_val, data, 9));
    crc16_val = CRC16_FINALIZE(crc16_val);
    assert(crc16_val == 0xfd7d);
}