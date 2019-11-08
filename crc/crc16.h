/*
 * crc_ccitt16.h
 *
 * Created: 11/21/2018 11:22:28 AM
 *  Author: Colin
 */ 


#ifndef CRC16_H
#define CRC16_H

#include <stddef.h>
#include <stdint.h>

/*
initialize crc value
*/
#define CRC16_INIT (0xffff)

/*
finalize crc value
*/
#define CRC16_FINALIZE(val) (val ^ 0xffff)

/*
computes the crc for data and uses crc for the result
returns 0 if successful
*/
int crc16(uint16_t *crc, const uint8_t *data, size_t size);

#endif /* CRC16_H_ */

