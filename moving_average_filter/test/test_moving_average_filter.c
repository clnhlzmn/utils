
#include "moving_average_filter.h"
#include <stdio.h>
#include <assert.h>

MOVING_AVERAGE_FILTER(test, float, 5);

struct maf_test my_maf;

int main(void) {
    //init filter
    maf_test_init(&my_maf);
    //fill window with value
    for (int i = 0; i < 5; ++i) {
        float filt = maf_test_input(&my_maf, 10.0);
        assert(maf_test_last_input(&my_maf) == 10.0);
        assert(filt == (10.0 * (i + 1)) / 5);
    }
    //fill window with different value
    for (int i = 0; i < 5; ++i) {
        float filt = maf_test_input(&my_maf, 0.0);
        assert(maf_test_last_output(&my_maf) == filt);
        assert(maf_test_last_input(&my_maf) == 0.0);
        assert(filt == (10.0 * (5 - i - 1)) / 5);
    }
    printf("tests passed\r\n");
    return 0;
}

