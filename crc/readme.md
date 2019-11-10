# crc

A library for calculating cyclic redundancy codes. I use crc16.h/c for detecting errors in board to board spi communications in noisy environments and for detecting corruption in eeprom memory caused by failure of the memory hardware or incomplete modifications. Unfortunately this method isn't 100%. There is a possibility of corruption not being detected, but depending on the size of the crc and the size of the data we can make the probability acceptably small.

## example

```c

#include <string.h>
#include "crc.h"

#define DATA_LEN (9)
uint8_t original_data[DATA_LEN] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main(void) {
    //prepare data that may be corrupted (reserve space for crc)
    uint8_t data_to_send[DATA_LEN + sizeof(uint16_t)];
    
    //calculate crc
    uint16_t crc = CRC16_INIT;
    crc16_update(&crc, original_data, DATA_LEN);
    crc = CRC16_FINALIZE(crc);
    
    //store crc with data
    memcpy(data_to_send, original_data, DATA_LEN);
    memcpy(data_to_send + DATA_LEN, &crc, sizeof(uint16_t));
    
    //transmit or save data with crc
    uint8_t received_data[DATA_LEN + sizeof(uint16_t)];
    memcpy(received_data, data_to_send, DATA_LEN + sizeof(uint16_t));
    
    //oops! the data was corrupted
    received_data[5] ^= 0xFF;
    
    //on the other side we re-calculate the crc and compare to the one sent with the data
    uint16_t crc2 = CRC16_INIT;
    crc16_update(&crc2, data_to_send, DATA_LEN);
    crc2 = CRC16_FINALIZE(crc2);
    
    uint16_t transmitted_crc;
    memcpy(&transmitted_crc, data_to_send + DATA_LEN, sizeof(uint16_t));
    
    if (transmitted_crc != crc2) {
        printf("data is corrupted!\n");
    } else {
        printf("data is ok or data is corrupted but crc is the same (unlikely)\n");
    }
}

```