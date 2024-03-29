/**
 * @license
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * @copyrights Copyrights 2019 Stanislaw Pietrzak. All rights reserved.
 * @file utils.h
 * @author Stanislaw Pietrzak
 * @email integralzerox@gmail.com
 * @date 25 July 2019
 * @brief Collection of useful functions
 *
 * The file contains a collection of useful functions when
 * programming poor memory platforms just like embedded, or for some reason
 * you do not want to use standard C libraries.
 *
 * @see https://github.com/Dev4Embedded/
 */
#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "inttypes.h"

typedef enum
{
	ERROR_SUCCESS           = 0x00,
	ERROR_NULL_POINTER      = 0x01,
	ERROR_CONVERSION_FAIL   = 0x02,
	ERROR_FAIL              = 0x03,
}UTILS_ERROR;

/**
* @brief    Convert unsigned integer variable to byte array of size of four.
* @note     The minimum size of byteArray must be bigger then 4
* @param[IN]    integer:      unsigned integer value
* @param[OUT]   byteArray:    pointer to array
* @return Utils error:
*    ERROR_NULL_POINTER    - byteArray is equal null
*    ERROR_SUCCESS         - conversion executed without errors
*/
UTILS_ERROR UTILS_Uint2ByteArray(uint32_t integer, uint8_t* byteArray);

/**
* @brief    Convert array of four bytes to unsigned integer
* @note     The minimum size of byteArray must be bigger then 4
* @param[IN]    byteArray:    pointer to array
* @param[OUT]   integer:      pointer to unsigned integer variable
* @return Utils error:
*     ERROR_NULL_POINTER    - byteArray or integer are equals null
*     ERROR_SUCCES          - conversion executed without errors
*/
UTILS_ERROR UTILS_ByteArray2Uint(uint8_t* byteArray, uint32_t* integer);

/**
 * @brief    Get size of ASCII sting
 *
 * Get the number of characters from the ASCII string.
 * The function will count until it encounters a character
 * that is not an ASCII symbol.
 *
 * @param[in]    string:    pointer to string
 * @param[out]   size:      number of characters in string
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER    - string or size are equal null
 */
UTILS_ERROR UTILS_GetSizeOfAsciiString(char* string, uint32_t* size);

/**
 * @brief    Get number of digits in integer value
 *
 * @param[in]    number:    an integer value to calculate the number of digits
 * @param[out]   digits:    number of digits
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER    - digits pointer is equal null
 *     ERROR_SUCCESS         - function executed without errors
 *     ERROR_FAIL            - general error
 */
UTILS_ERROR UTILS_GetNumberOfDigit(int32_t number,uint8_t* digits);

/**
 * @brief    Convert single ASCII character to digit
 *
 * Conversion is possible only for single byte characters which are digits:
 * 0, 1, 2..8 and 9. To convert ASCII strings, please use
 * UTILS_AsciiString2Int() function.
 *
 * @param[in]    ascii:    ASCII character
 * @param[out]   byte:     value of digit
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to byte is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 ASCII character is not a digit.
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_AsciiDigit2Byte(char ascii, uint8_t* byte);

/**
 * @brief    Convert byte with range <0..9> to ASCII digit
 *
 * @param[in]    byte:     byte to convert
 * @param[out]   ascii:    value of digit
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to ascii is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 Byte is out of range
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_Byte2AsciiDigit(uint8_t byte, char* ascii);

/**
 * @brief    Convert ASCII string to 32-bit integer value with sign
 *
 * The ASCII string must contain only numbers, and the '-' (minus) character
 * in the first position if the value is negative. The maximum size of string
 * can be 11 characters, because the min. value of integer with sign is equal
 * -‭2.147.483.648. NULL (0x00) character is condition of stop during checking
 * the number of digit in string.
 *
 * @param[in]    string:     chain of digits
 * @param[out]   integer:    conversion result
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to string or integer is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 ASCII string is too long
 *     ERROR_SUCCESS             - conversion executed without errors
 *     ERROR_FAIL                - general error‬
 */
UTILS_ERROR UTILS_AsciiString2Int(char* string, int32_t* integer);

/**
 * @brief    Convert integer value to ASCII character string
 *
 * The 'string' must have allocated memory for a number with a minimum 'length'
 * equal to the number of digits in the 'integer' value plus the character sign
 * (if a value of 'integer' is negative). If the size of number is unknown
 * that is safe to use UTILS_INT_MAX_DIGITS to allocate 'string' array.
 * All empty bytes will be set as NULL.
 *
 * @param[in]    integer:    integer value to be converted to ASCII string
 * @param[out]   string:     ASCII string of integer value
 * @param[in]    length:     length of string (before conversion)
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to string is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 Length of string is too small.
 *     ERROR_SUCCESS             - conversion executed without errors
 *     ERROR_FAIL                - general error
 */
UTILS_ERROR UTILS_Int2AsciiString(int32_t integer, char* string, uint8_t length);

/**
 * @brief    Get the physical byting form of the floating point variable
 *
 * @param[in]    fp:         floating point variable
 * @param[out]   integer:    physical format of float stored in memory
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to integer is NULL
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_Float2Uint(float fp, uint32_t* integer);

/**
 * @brief    Transform binary form to floating precision
 *
 * @param[in]    integer:    binary format
 * @param[out]   fp:         floating precision value
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to floating precision
 *                                  variable is NULL
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_Uint2Float(uint32_t integer, float* fp);

/**
 * @brief    Convert hexadecimal string to unsigned integer
 *
 * Hexadecimal string can has "0x" and "x" on the beginning. However, all string
 * must consist only hex characters just like: 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
 * and also: a,b,c,d,e,f.
 *
 * @param[in]    hex:        hexadecimal string
 * @param[out]   integer:    conversion result
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to hex is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 In hex string is not allowed character
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_Hex2Uint(char* hex, uint32_t* integer);

/**
 * @brief    Convert integer to hexadecimal string
 *
 * The ASCII 'hex' string should have a length appropriate to
 * the value of the integer variable. If value of integer is not known,
 * for safety, allocate size of 'hex' as possible maximum value 8 digits
 * + 2('0x') hexadecimal characters.
 *
 * @param[in]    integer:    integer value to be converted to hexadecimal string
 * @param[out]   hex:        hexadecimal string
 * @param[in]    length:     length of hex string (before conversion)
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to hex is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 length of hex is too short.
 *     ERROR_SUCCESS             - conversion executed without errors
 *
 */
UTILS_ERROR UTILS_Uint2Hex(uint32_t integer, char* hex, uint8_t length);

/**
 * @brief    Convert float position variable to hexadecimal ASCII string
 *
 * The minimum of 'hex' string must be 10 (Number of max. digit in hex format
 * plus '0x' prefix) or greater.
 *
 * @param[in]    fp:        floating point value
 * @param[out]   hex:       pointer to hexadecimal string
 * @param[in]    length:    length of string (before conversion)
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to hex is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 Length of hex is too short
 *     ERROR_FAIL                - general error
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_Float2Hex(float fp, char* hex, uint8_t length);

/**
 * @brief    Convert float position variable to digits ASCII string
 *
 * Length of 'ascii' array should be adequate to size of floating point 'fp'.
 * This means that this function returns an error if the size of the integer
 * "fp" does not fit in the array. Otherwise, the "ascii" array will be filled
 *  with decimal digits to the end or set the rest of the cell to 0.
 *
 * @param[in]    fp:        floating point value
 * @param[out]   ascii:     pointer to ascii array
 * @param[in]    length:    length of string (before conversion)
 *
 * @return Utils error:
 *     ERROR_NULL_POINTER        - pointer to string is NULL
 *     ERROR_CONVERSION_FAIL     - conversion is not possible.
 *                                 length of ascii is too short
 *     ERROR_FAIL                - general error
 *     ERROR_SUCCESS             - conversion executed without errors
 */
UTILS_ERROR UTILS_Float2AsciiString(float fp, char* ascii, uint8_t length);

#endif /* INC_UTILS_H_ */
