
#include <assert.h>
#include <stdio.h>
#include "../majority.h"

int main(void) {
    assert(majority_3(0, 0, 0) == 0);
    assert(majority_3(1, 0, 0) == 0);
    assert(majority_3(1, 1, 0) == 1);
    assert(majority_3(1, 1, 1) == 1);
    assert(majority_3(0, 1, 1) == 1);
    assert(majority_3(0, 0, 1) == 0);
    
    assert(majority_3(0b11101010,
                      0b01110011, 
                      0b00101010) == 0x6a);
    
    assert(majority_5(0, 0, 0, 0, 0) == 0);
    assert(majority_5(1, 0, 0, 0, 0) == 0);
    assert(majority_5(1, 1, 0, 0, 0) == 0);
    assert(majority_5(1, 1, 1, 0, 0) == 1);
    assert(majority_5(1, 1, 1, 1, 0) == 1);
    assert(majority_5(1, 1, 1, 1, 1) == 1);
    assert(majority_5(0, 1, 1, 1, 1) == 1);
    assert(majority_5(0, 0, 1, 1, 1) == 1);
    assert(majority_5(0, 0, 0, 1, 1) == 0);
    assert(majority_5(0, 0, 0, 0, 1) == 0);
    
    assert(majority_5(0b11111010,
                      0b01110011, 
                      0b00111010, 
                      0b00010011, 
                      0b00001010) == 0x3a);
    
    printf("tests passed\r\n");
    return 0;
}