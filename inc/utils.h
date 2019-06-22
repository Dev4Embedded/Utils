#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "inttypes.h"


typedef enum
{
	ERROR_SUCCESS 			= 0x00,
	ERROR_NULL_POINTER		= 0x01,
	ERROR_CONVERSION_FAIL	= 0x02,
	ERROR_FAIL				= 0x03
}UTILS_ERROR;

UTILS_ERROR UTILS_AsciiDigit2Byte(char ascii, uint8_t* byte);

UTILS_ERROR UTILS_Byte2AsciiDigit(uint8_t byte, char* ascii);

UTILS_ERROR UTILS_AsciiString2Int(char* string, int32_t* integer);

#endif /* INC_UTILS_H_ */
