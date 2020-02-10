#include <stdio.h>
#include <assert.h>
#include "../crc16.h"
#include "../crc32.h"

unsigned char data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main(void) {
    uint16_t crc16_val = CRC16_INIT;
    assert(!crc16(&crc16_val, data, 9));
    crc16_val = CRC16_FINALIZE(crc16_val);
    assert(crc16_val == 0xfd7d);
    
    uint32_t crc32_val = CRC32_INIT;
    assert(!crc32(&crc32_val, data, 9));
    crc32_val = CRC32_FINALIZE(crc32_val);
    printf("%x\r\n", crc32_val);
    assert(crc32_val == 0xcbf43926);
    printf("tests passed\r\n");
    return 0;
}