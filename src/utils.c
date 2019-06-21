#include "utils.h"

#define UTILS_INT_MAX_VALUE  0x7FFFFFFF	//‭2147483647
#define UTILS_INT_MAX_DIGITS 10			//‭2.147.483.647‬

UTILS_ERROR UTILS_AsciiDigit2Byte(char ascii, uint8_t* byte)
{
	if(ascii >='0' && ascii<='9')
	{
		*byte = ascii - '0';
		return ERROR_SUCCESS;
	}

	return ERROR_CONVERSION_FAIL;
}
UTILS_ERROR UTILS_Byte2AsciiDigit(uint8_t byte, char* ascii)
{
	if(byte >=0 && byte <= 9)
	{
		*ascii = byte + '0';
		return ERROR_SUCCESS;
	}

	return ERROR_CONVERSION_FAIL;
}
UTILS_ERROR UTILS_AsciiString2Int(char* string, uint8_t size, uint32_t* integer)
{
	if(string == NULL)
		return ERROR_NULL_POINTER;
	if(size > UTILS_INT_MAX_DIGITS + 1) //digits + and (possible) sign of negative
		return ERROR_CONVERSION_FAIL;


	return ERROR_SUCCESS;
}
