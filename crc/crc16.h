/**
\file crc16.h
\brief functions for calculating 16 bit cyclic redundancy codes
\CRC-16/IBM/SDLC
 */

#ifndef CRC16_H
#define CRC16_H

#include <stddef.h>
#include <stdint.h>

/**
\brief initial crc value
*/
#define CRC16_INIT (0xffff)

/**
\brief finalize crc value
\param val an initialized crc value
\return a finalized crc value
*/
#define CRC16_FINALIZE(val) (val ^ 0xffff)

/**
\brief computes the crc for data and uses crc for the result
\param crc pointer to initialized crc value
\param data pointer to data over which to calculate crc
\param size number of bytes of data
\return 0 if successful
*/
int crc16(uint16_t *crc, const uint8_t *data, size_t size);

#endif /* CRC16_H_ */

