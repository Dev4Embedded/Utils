#include "math.h"
#include "utils.h"

#define UTILS_INT_MAX_VALUE  0x7FFFFFFF	//‭2147483647
#define UTILS_INT_MAX_DIGITS 10			//‭2.147.483.647

/**
 * @brief 	Get size of ASCII sting
 *
 * Get the number of characters from the ASCII string.
 * The function will count until it encounters a character that is not an ASCII symbol.
 *
 * @param[in]	string:		pointer on string
 * @param[out]	size:		number of characters in string
 *
 * @return Utils error:	ERROR_NULL_POINTER - string or size are equal null
 *
 */
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

/**
 * @brief	Convert single ASCII character to digit
 *
 * Conversion is possible only for single byte characters which are digits:
 * 0, 1, 2..8 and 9. To convert ASCII strings, please use UTILS_AsciiString2Int() function
 *
 * @param[in] ascii:	ASCII character
 * @param[out] byte:	value of digit
 *
 * @return Utils error:	ERROR_NULL_POINTER	  - pointer on byte is NULL \n
 *  					ERROR_CONVERSION_FAIL - conversion is not possible. ASCII character is not a digit.
 *  					ERROR_SUCCESS	  	  - conversion executed without errors
 */
UTILS_ERROR UTILS_AsciiDigit2Byte(char ascii, uint8_t* byte)
{
	if(byte == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if(ascii >='0' && ascii<='9')
	{
		*byte = ascii - '0';
		return ERROR_SUCCESS;
	}

	return ERROR_CONVERSION_FAIL;
}

/**
 * @brief	Convert byte with range <0..9> to ASCII digit
 *
 * @param[in]  byte:	byte to convert
 * @param[out] ascii:	value of digit
 *
 * @return Utils error:	ERROR_NULL_POINTER	  - pointer on ascii is NULL \n
 *  					ERROR_CONVERSION_FAIL - conversion is not possible. Byte is out of range
 *  					ERROR_SUCCESS	 	  - conversion executed without errors
 */
UTILS_ERROR UTILS_Byte2AsciiDigit(uint8_t byte, char* ascii)
{
	if(ascii == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if(byte >=0 && byte <= 9)
	{
		*ascii = byte + '0';
		return ERROR_SUCCESS;
	}

	return ERROR_CONVERSION_FAIL;
}
/**
 * @brief Convert ASCII string to 32-bit integer value with sign
 *
 * ASCII string must contain only numbers, and the '-' (minus) character in the first position if
 * the value is negative. The maximum size of string can be 11 characters, because the min. value of
 * integer with sign is equal -‭2.147.483.648. NULL (0x00) character is condition of stop during
 * checking the number of digit in string.
 *
 * @param[in] 	string	chain of digits
 * @param[out]	integer	conversion result
 *
 * @return Utils error:	ERROR_NULL_POINTER	  - pointer on string or integer is NULL \n
 *  					ERROR_CONVERSION_FAIL - conversion is not possible. ASCII string is too long
 *  					ERROR_SUCCESS	 	  - conversion executed without errors
 *  					ERROR_FAIL			  - general error‬
 */
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
	while(i<size)
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
		i++;
	}

	if(isNegative) value *= (-1);
	*integer = value;

	return ERROR_SUCCESS;
}
