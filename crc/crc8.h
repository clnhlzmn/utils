/**
\file crc8.h
\brief functions for calculating 8 bit cyclic redundancy codes
\CRC-8/CDMA2000
 */

#ifndef CRC8_H
#define CRC8_H

#include <stdlib.h>
#include <stdint.h>

/**
 * \brief initial crc value
 */
#define CRC8_INIT 0xff

/**
\brief computes the crc for data and uses crc for the result
\param crc pointer to initialized crc value
\param data pointer to data over which to calculate crc
\param size number of bytes of data
\return 0 if successful
 */
int crc8(uint8_t *crc, const uint8_t *data, size_t size);

#endif      /* CRC8_H */
