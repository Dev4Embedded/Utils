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

/**
* @brief	Convert unsigned integer variable to byte array of size of four.
* @note		The minimum size of byteArray must be bigger then 4
* @param[IN]	integer:		unsigned integer value
* @param[OUT] 	byteArray:		pointer on array
* @return Utils error:
* 		ERROR_NULL_POINTER	- byteArray is equal null
* 		ERROR_SUCCESS		- conversion executed without errors
*/
UTILS_ERROR UTILS_Uint2ByteArray(uint32_t integer, uint8_t* byteArray);

/**
* @brief	Convert array of four bytes to unsigned integer
* @note		The minimum size of byteArray must be bigger then 4
* @param[IN] 	byteArray:		pointer on array
* @param[OUT] 	integer:		pointer on unsigned integer variable
* @return Utils error:
* 		ERROR_NULL_POINTER	- byteArray or integer are equals null
* 		ERROR_SUCCESS		- conversion executed without errors
*/
UTILS_ERROR UTILS_ByteArray2Uint(uint8_t* byteArray, uint32_t* integer);

/**
 * @brief 	Get size of ASCII sting
 *
 * Get the number of characters from the ASCII string.
 * The function will count until it encounters a character that is not an ASCII symbol.
 *
 * @param[in]	string:			pointer on string
 * @param[out]	size:			number of characters in string
 *
 * @return Utils error:
 * 		ERROR_NULL_POINTER	- string or size are equal null
 *
 */
UTILS_ERROR UTILS_GetSizeOfAsciiString(char* string, uint32_t* size);

/**
 * @brief	Get number of digits in integer value
 *
 * @param[in]	number:			an integer value to calculate the number of digits
 * @param[out]	digits:			number of digits
 *
 * @return Utils error:
 * 		ERROR_NULL_POINTER	- digits pointer is equal null
 * 		ERROR_SUCCESS		- function executed without errors
 * 		ERROR_FAIL			- general error
 */
UTILS_ERROR UTILS_GetNumberOfDigit(int32_t number,uint8_t* digits);

/**
 * @brief	Convert single ASCII character to digit
 *
 * Conversion is possible only for single byte characters which are digits:
 * 0, 1, 2..8 and 9. To convert ASCII strings, please use UTILS_AsciiString2Int() function
 *
 * @param[in] ascii:	ASCII character
 * @param[out] byte:	value of digit
 *
 * @return Utils error:
 * 		ERROR_NULL_POINTER		- pointer on byte is NULL
 *  	ERROR_CONVERSION_FAIL	- conversion is not possible. ASCII character is not a digit.
 *  	ERROR_SUCCESS			- conversion executed without errors
 */
UTILS_ERROR UTILS_AsciiDigit2Byte(char ascii, uint8_t* byte);

/**
 * @brief	Convert byte with range <0..9> to ASCII digit
 *
 * @param[in]  byte:	byte to convert
 * @param[out] ascii:	value of digit
 *
 * @return Utils error:
 * 		ERROR_NULL_POINTER		- pointer on ascii is NULL
 * 		ERROR_CONVERSION_FAIL	- conversion is not possible. Byte is out of range
 * 		ERROR_SUCCESS	 		- conversion executed without errors
 */
UTILS_ERROR UTILS_Byte2AsciiDigit(uint8_t byte, char* ascii);

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
 * @return Utils error:
 * 		ERROR_NULL_POINTER		- pointer on string or integer is NULL
 * 		ERROR_CONVERSION_FAIL	- conversion is not possible. ASCII string is too long
 * 		ERROR_SUCCESS			- conversion executed without errors
 * 		ERROR_FAIL				- general error‬
 */
UTILS_ERROR UTILS_AsciiString2Int(char* string, int32_t* integer);

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
 * @return Utils error:
 * 		ERROR_NULL_POINTER		- pointer on string is NULL
 * 		ERROR_CONVERSION_FAIL	- conversion is not possible. Length of string is too small.
 * 		ERROR_SUCCESS			- conversion executed without errors
 * 		ERROR_FAIL				- general error
 */
UTILS_ERROR UTILS_Int2AsciiString(int32_t integer, char* string, uint8_t length);

#endif /* INC_UTILS_H_ */
