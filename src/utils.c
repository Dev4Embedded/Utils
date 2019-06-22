#include "math.h"
#include "utils.h"

#define UTILS_INT_MAX_VALUE  0x7FFFFFFF	//‭2147483647
#define UTILS_INT_MAX_DIGITS 10			//‭2.147.483.647

UTILS_ERROR UTILS_GetSizeOfAsciiString(char* string, uint32_t* size)
{
	if(string == NULL || size == NULL) return ERROR_NULL_POINTER;
	uint32_t t_size=0;
	while(string != NULL && *string > 0 && *string < 127)
	{
		t_size++;
		string++;
	}
	*size = t_size;
	return ERROR_SUCCESS;
}
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
UTILS_ERROR UTILS_AsciiString2Int(char* string, int32_t* integer)
{
	if(string == NULL)
		return ERROR_NULL_POINTER;

	uint32_t size;
	if(UTILS_GetSizeOfAsciiString(string,&size) != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}
	if(size == 1)
	{
		return UTILS_AsciiDigit2Byte(string[0],(uint8_t*)integer);
	}
	if(size > UTILS_INT_MAX_DIGITS + 1) //digits + and (possible) sign of negative
		return ERROR_CONVERSION_FAIL;

	uint8_t isNegative;
	uint32_t multipler;
	uint8_t noDigit;
	uint8_t i;
	if(string[0] == '-')
	{
		isNegative = 1;
		noDigit = size - 1;
		i = 1;
	}
	else
	{
		isNegative = 0;
		noDigit = size;
		i = 0;
	}
	multipler = pow(10,noDigit-1);

	int32_t value = 0;
	for(i; i<size; i++)
	{
		uint8_t digit;
		UTILS_ERROR error = UTILS_AsciiDigit2Byte(string[i],&digit);
		if(error == ERROR_SUCCESS)
		{
			value += multipler * digit;
			multipler /= 10;
		}
		else
			return error;
	}

	if(isNegative) value *= (-1);
	*integer = value;

	return ERROR_SUCCESS;
}
