/*
 * crc_ccitt16.c
 *
 * Created: 11/21/2018 11:27:33 AM
 *  Author: Colin
 */ 

#include "crc16.h"

static uint16_t crc16_update(uint16_t crc, uint8_t data) {
    static const uint16_t crc_table[16] = {
        0x0000, 0x1081, 0x2102, 0x3183, 0x4204, 0x5285, 0x6306, 0x7387,
        0x8408, 0x9489, 0xa50a, 0xb58b, 0xc60c, 0xd68d, 0xe70e, 0xf78f
    };
    uint8_t tbl_idx;
    tbl_idx = crc ^ (data >> (0 * 4));
    crc = crc_table[tbl_idx & 0x0f] ^ (crc >> 4);
    tbl_idx = crc ^ (data >> (1 * 4));
    crc = crc_table[tbl_idx & 0x0f] ^ (crc >> 4);
    return crc & 0xffff;
}

int crc16(uint16_t *crc, const uint8_t *data, size_t size) {
    if (!crc || !data) return -1;
    for (size_t i = 0; i < size; ++i) {
        *crc = crc16_update(*crc, data[i]);
    }
    return 0;
}

