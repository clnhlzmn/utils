#include "crc8.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

static uint8_t crc8_update(uint8_t crc, uint8_t data) {
    static const uint8_t crc_table[16] = {
        0x00, 0x9b, 0xad, 0x36, 0xc1, 0x5a, 0x6c, 0xf7,
        0x19, 0x82, 0xb4, 0x2f, 0xd8, 0x43, 0x75, 0xee
    };
    unsigned int tbl_idx;
    tbl_idx = (crc >> 4) ^ (data >> 4);
    crc = crc_table[tbl_idx & 0x0f] ^ (crc << 4);
    tbl_idx = (crc >> 4) ^ data;
    crc = crc_table[tbl_idx & 0x0f] ^ (crc << 4);
    return crc;
}

int crc8(uint8_t *crc, const uint8_t *data, size_t size) {
    if (!crc || !data) return -1;
    for (size_t i = 0; i < size; ++i) {
        *crc = crc8_update(*crc, data[i]);
    }
    return 0;
}
