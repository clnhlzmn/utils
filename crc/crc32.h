/**
\file crc32.h
\brief functions for calculating 32 bit cyclic redundancy codes
*/

#ifndef CRC32_H
#define CRC32_H

#include <stdlib.h>
#include <stdint.h>

/**
\brief initial crc value
*/
#define CRC32_INIT (0xffffffff)

/**
\brief finalize crc value
\param val an initialized crc value
\return a finalized crc value
*/
#define CRC32_FINALIZE(val) (val ^ 0xffffffff)

/**
\brief computes the crc for data and uses crc for the result
\param crc pointer to initialized crc value
\param data pointer to data over which to calculate crc
\param size number of bytes of data
\return 0 if successful
 */
int crc32(uint32_t *crc, const uint8_t *data, size_t size);

#endif      /* CRC32_H */
