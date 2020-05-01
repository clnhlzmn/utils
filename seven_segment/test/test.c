#include <string.h>
#include <assert.h>
#include "seven_segment.h"

int main(void) {
    {
        char *str = "...";
        uint8_t buf[5];
        size_t n = seven_segment_encode(buf, 5, str);
        assert(n == 3);
        uint8_t expect[] = {0x80, 0x80, 0x80};
        assert(memcmp(buf, expect, 3) == 0);
    }
    {
        char *str = ".A.";
        uint8_t buf[5];
        size_t n = seven_segment_encode(buf, 5, str);
        assert(n == 2);
        uint8_t expect[] = {0x80, 0xF7};
        assert(memcmp(buf, expect, 2) == 0);
    }
    {
        char *str = "..A..";
        uint8_t buf[5];
        size_t n = seven_segment_encode(buf, 5, str);
        assert(n == 4);
        uint8_t expect[] = {0x80, 0x80, 0xF7, 0x80};
        assert(memcmp(buf, expect, 4) == 0);
    }
    {
        char *str = "  .";
        uint8_t buf[5];
        size_t n = seven_segment_encode(buf, 2, str);
        assert(n == 2);
        uint8_t expect[] = {0x00, 0x80};
        assert(memcmp(buf, expect, 2) == 0);
    }
}