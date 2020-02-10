#include "crc32.h"

static const uint32_t crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

int crc32(uint32_t *crc, const uint8_t *data, size_t size) {
    if (!crc || !data) return -1;
    unsigned int tbl_idx;
    while (size--) {
        tbl_idx = *crc ^ *data;
        *crc = crc_table[tbl_idx & 0x0f] ^ (*crc >> 4);
        tbl_idx = *crc ^ (*data >> 4);
        *crc = crc_table[tbl_idx & 0x0f] ^ (*crc >> 4);
        data++;
    }
    return 0;
}
