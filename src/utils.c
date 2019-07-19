#include "math.h"
#include "utils.h"

#define UTILS_INT_MAX_VALUE  0x7FFFFFFF	//‭2147483647
#define UTILS_INT_MAX_DIGITS 10			//‭2.147.483.647

/**
* @brief	Convert unsigned integer variable to byteArray of size of four.
* @note		The minimum size of byteArray must be bigger then 4
* @param[IN]	integer:		unsigned integer value
* @param[OUT] 	byteArray:	pointer on array
* @return Utils error:	ERROR_NULL_POINTER - byteArray is equal null \n
*						ERROR_SUCCESS	   - conversion executed without errors
*/
UTILS_ERROR UTILS_Uint2ByteArray(uint32_t integer, uint8_t* byteArray)
{
	if(byteArray == NULL) return ERROR_NULL_POINTER;

	for(int8_t byte = 3; byte >= 0; byte--)
	{
		byteArray[byte] = integer >> (byte * 8);
	}

	return ERROR_SUCCESS;
}

/**
* @brief	Convert array of four bytes to unsigned integer
* @note		The minimum size of byteArray must be bigger then 4
* @param[IN] 	byteArray:	pointer on array
* @param[OUT] 	integer:	pointer on unsigned integer variable
* @return Utils error:	ERROR_NULL_POINTER - byteArray or integer are equals null \n
						ERROR_SUCCESS	   - conversion executed without errors
*/
UTILS_ERROR UTILS_ByteArray2Uint(uint8_t* byteArray, uint32_t* integer)
{
	if(byteArray == NULL || integer == NULL) return ERROR_NULL_POINTER;

	*integer = 0;

	for(int8_t byte = 3; byte >= 0; byte--)
	{
		*integer <<= 8;
		*integer |= byteArray[byte];
	}

	return ERROR_SUCCESS;
}

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
 * @brief	Get number of digits in integer value
 *
 * @param[in]	number:		an integer value to calculate the number of digits
 * @param[out]	digits:		number of digits
 *
 * @return Utils error:	ERROR_NULL_POINTER - digits pointer is equal null
 * 						ERROR_SUCCESS	   - function executed without errors
 *  					ERROR_FAIL		   - general error
 */
UTILS_ERROR UTILS_GetNumberOfDigit(int32_t number,uint8_t* digits)
{
	if(digits == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if(number == 0)
	{
		*digits = 1;
		return ERROR_SUCCESS;
	}
	uint32_t divider = 1;
	number = abs(number);
	for(uint8_t digit = 1; digit <= UTILS_INT_MAX_DIGITS; digit++)
	{
		if(number / divider <= 0)
		{
			*digits = digit-1;
			return ERROR_SUCCESS;
		}
		divider *= 10;
	}
	return ERROR_FAIL;
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

/**
 * @brief Convert integer value to ASCII character string
 *
 * The 'string' must have allocated memory for a number with a minimum 'length'
 * equal to the number of digits in the 'integer' value plus the character sign
 * (if a value of 'integer' is negative). If the size of number is unknown
 * that is safe to use UTILS_INT_MAX_DIGITS to allocate 'string' array.
 * All empty bytes will be set as NULL.
 *
 * @param[in]	integer:	integer value to be converted to ASCII string
 * @param[out]	string:		ASCII string of integer value
 * @param[in]	length:		length of string (before conversion)
 *
 */
UTILS_ERROR UTILS_Int2AsciiString(int32_t integer, char* string, uint8_t length)
{
	if(string == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	uint8_t numberOfdigits;
	if(UTILS_GetNumberOfDigit(integer,&numberOfdigits) != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}
	if(numberOfdigits > length)
	{
		return ERROR_CONVERSION_FAIL;
	}

	uint32_t divider = pow(10,numberOfdigits-1);
	uint8_t charCounter;
	if(integer<0)
	{
		string[0] = '-';
		charCounter=1;
		integer = abs(integer);
		numberOfdigits++;
	}
	else
	{
		charCounter =0;
	}

 	while(charCounter<numberOfdigits)
	{
		uint8_t digit =  (integer / divider) % 10;
		char asciiDigit;
		if(UTILS_Byte2AsciiDigit(digit,&asciiDigit) == ERROR_SUCCESS)
		{
			string[charCounter] = asciiDigit;
			divider/=10;
		}
		else
		{
			return ERROR_FAIL;
		}
		charCounter++;
	}
	if(charCounter < length)
	{
		for(uint8_t fill = charCounter;fill<length; fill++){
			string[fill] = 0x00;
		}
	}
	return ERROR_SUCCESS;
}
