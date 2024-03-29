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
 * @file utils.c
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

#include "math.h"
#include "utils.h"

#define UTILS_INT_MAX_VALUE              0x7FFFFFFF //‭2147483647
#define UTILS_INT_MAX_DIGITS             10	        //‭2.147.483.647
#define UTILS_HEX_MAX_DIGITS             8
#define UTILS_SIZE_OF_HEX_PREFIX         2
#define UTILS_HEX2BYTE(hex)        (hex >= '0' && hex <='9') ? \
                                   (hex - '0') : (hex >= 'a' && hex <= 'f') ? \
                                   (hex - 'a' + 10) : (hex - 'A' + 10)
#define UTILS_INT2HEX(integer)     (integer >= 0 && integer <= 9) ? \
                                   (integer + '0') : (integer + 'A' - 10)
#define UTILS_FLOAT_EXPONENT_BIAS       127
#define UTILS_FLOAT_MAX_ACCURACY        9
#define UTILS_FLOAT_SIGN_POSITION       31
#define UTILS_FLOAT_SIGN_MASK           0x80000000
#define UTILS_FLOAT_EXPONENT_POSITION   23
#define UTILS_FLOAT_EXPONENT_MASK       0x7F800000
#define UTILS_FLOAT_FRACTION_POSITION   0
#define UTILS_FLOAT_FRACTION_MASK       0x007FFFFF
#define UTILS_FLOAT_FRACTION_BITS       22

#define UTILS_FLOAT_GET_SIGN(fp)        (fp & UTILS_FLOAT_SIGN_MASK)\
                                        >> UTILS_FLOAT_SIGN_POSITION
#define UTILS_FLOAT_GET_EXPONENT(fp)    (fp & UTILS_FLOAT_EXPONENT_MASK)\
                                        >> UTILS_FLOAT_EXPONENT_POSITION
#define UTILS_FLOAT_GET_FRACTION(fp)    (fp & UTILS_FLOAT_FRACTION_MASK)\
                                        >> UTILS_FLOAT_FRACTION_POSITION
const char hexDigits[] =    {'0','1','2','3','4','5','6','7','8','9','A',
                             'B','C','D','E','F','a','b','c','d','e','f'};

union UTILS_ConversionUnion
{
	float fp;
	uint32_t integer;
}ConversionUnion;

static int isHexDigit(char* digit)

{
	if(digit == NULL) return 0;
	for(uint8_t digitCtr = 0; digitCtr < sizeof(hexDigits); digitCtr++)
	{
		if(*digit == hexDigits[digitCtr]) return 1;
	}
	return 0;
}
static uint32_t getNumberOfHexDigits(uint32_t hex)
{
	if(hex <= 0xF)          return 1;
	if(hex <= 0xFF)         return 2;
	if(hex <= 0xFFF)        return 3;
	if(hex <= 0xFFFF)       return 4;
	if(hex <= 0xFFFFF)      return 5;
	if(hex <= 0xFFFFFF)     return 6;
	if(hex <= 0xFFFFFFF)    return 7;
	if(hex <= 0xFFFFFFFF)   return 8;
	return 0;
}

static float calculateMantissa(uint32_t mantissa)
{
	float calMantissa = 1.0;
	uint8_t power = UTILS_FLOAT_FRACTION_BITS;
	uint32_t bitMask = (1<<power);
	if(mantissa&bitMask)
	{
		calMantissa = 1.0;
	}
	while(--power)
	{
		if(mantissa&bitMask)
		{
			calMantissa += pow(2,(UTILS_FLOAT_FRACTION_BITS-power)*(-1));
		}
		bitMask>>=1;
	}
	return calMantissa;
}

/**
* @brief    Convert unsigned integer variable to byte array of size of four.
* @note     The minimum size of byteArray must be bigger then 4
* @param[IN]    integer:      unsigned integer value
* @param[OUT]   byteArray:    pointer to array
* @return Utils error:
*    ERROR_NULL_POINTER    - byteArray is equal null
*    ERROR_SUCCESS         - conversion executed without errors
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
* @brief    Convert array of four bytes to unsigned integer
* @note     The minimum size of byteArray must be bigger then 4
* @param[IN]    byteArray:    pointer to array
* @param[OUT]   integer:      pointer to unsigned integer variable
* @return Utils error:
*     ERROR_NULL_POINTER    - byteArray or integer are equals null
*     ERROR_SUCCES          - conversion executed without errors
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
UTILS_ERROR UTILS_Float2Uint(float fp, uint32_t* integer)
{
	if(integer == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	ConversionUnion.fp = fp;
	*integer = ConversionUnion.integer;
	return ERROR_SUCCESS;
}

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
UTILS_ERROR UTILS_Uint2Float(uint32_t integer, float* fp)
{
	if(fp == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	ConversionUnion.integer = integer;
	*fp = ConversionUnion.fp;
	return ERROR_SUCCESS;
}

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
UTILS_ERROR UTILS_Hex2Uint(char* hex, uint32_t* integer)
{
	if(hex == NULL || integer == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	uint8_t digitCtr=0, digitOffset = 0;

	if (hex[0] == 'x' || hex[0] == 'X')
	{
		digitOffset = 1;
	}
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
	{
		digitOffset = 2;
	}
	char* ptr = &hex[digitOffset];
	while(ptr++ != NULL)
	{
		if(*ptr != 0)break;
		if(isHexDigit(ptr) == 0)
		{
			return ERROR_CONVERSION_FAIL;
		}
	}
	while(digitCtr+digitOffset < UTILS_HEX_MAX_DIGITS+digitOffset)
	{
		if(isHexDigit(&hex[digitCtr+digitOffset]) == 0)
		{
			break;
		}
		digitCtr++;
	}

	uint32_t range = 1;
	uint32_t value = 0;
	for(int i = digitCtr+digitOffset-1; i>=digitOffset; i--)
	{
		value += (UTILS_HEX2BYTE(hex[i])) * range;
		range *= 16;
	}
	*integer = value;
	return ERROR_SUCCESS;

}

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
UTILS_ERROR UTILS_Uint2Hex(uint32_t integer, char* hex, uint8_t length)
{
	if(hex == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	uint8_t hexLength = getNumberOfHexDigits(integer);
	if(hexLength + 2 > length)
	{
		return ERROR_CONVERSION_FAIL;
	}
	hex[0] = '0';
	hex[1] = 'x';

	const uint8_t charOffset = 2;
	uint32_t mask  = 0xF0000000;
	uint32_t shift = 28;
	uint32_t digitCtr = 0;
	uint8_t isConvStart = 0;
	for(int nibble = 0; nibble < 8 ; nibble++)
	{
		uint32_t hexPart = ((mask&integer)>>shift);
		if(hexPart != 0 || isConvStart)
		{
			isConvStart = 1;
			hex[charOffset+digitCtr] = UTILS_INT2HEX(hexPart);
			digitCtr++;
		}
		mask>>=4;
		shift-=4;
	}
	if(integer == 0)
	{
		hex[2] = '0';
		digitCtr++;
	}
	for(uint8_t rest = digitCtr+charOffset; rest<length; rest++)
	{
		hex[rest] = 0x00;
	}
	return ERROR_SUCCESS;
}

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
UTILS_ERROR UTILS_Float2Hex(float fp, char* hex, uint8_t length)
{
	if(hex == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if(length < UTILS_HEX_MAX_DIGITS + UTILS_SIZE_OF_HEX_PREFIX)
	{
		return ERROR_CONVERSION_FAIL;
	}
	UTILS_ERROR errorCode;
	uint32_t integer;

	errorCode = UTILS_Float2Uint(fp,&integer);
	if(errorCode != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}

	errorCode = UTILS_Uint2Hex(integer,hex,length);
	if(errorCode  != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}
	return errorCode;
}

/**
 * @brief    Convert float position variable to digits ASCII string
 *
 * Length of 'ascii' array should be adequate to size of floating point 'fp'.
 * This means that this function returns an error if the size of the integer
 * "fp" does not fit in the array. Otherwise, the "ascii" array will be filled
 * with decimal digits to the end or set the rest of the cell to 0.
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
UTILS_ERROR UTILS_Float2AsciiString(float fp, char* string, uint8_t length)
{
	if(string == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	uint8_t charOffset = 0;
	UTILS_ERROR error;
	uint32_t binForm;

	error = UTILS_Float2Uint(fp,&binForm);
	if(error != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}

	uint32_t signBin = UTILS_FLOAT_GET_SIGN(binForm);
	uint32_t expBin = UTILS_FLOAT_GET_EXPONENT(binForm);
	uint32_t manBin = UTILS_FLOAT_GET_FRACTION(binForm);

	int32_t exponent = pow(2,expBin - UTILS_FLOAT_EXPONENT_BIAS);
	float mantissa = calculateMantissa(manBin);
	uint32_t integer = exponent * mantissa;

	/*Calculate number of digits of integer part*/
	uint8_t intSize;
	error = UTILS_GetNumberOfDigit(integer,&intSize);
	if(error != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}
	if(intSize + charOffset >= length)
	{
		return ERROR_CONVERSION_FAIL;
	}
	if(signBin)
	{
		string[0]='-';
		charOffset++;
	}
	error = UTILS_Int2AsciiString(integer,&string[charOffset],length);
	if(error != ERROR_SUCCESS)
	{
		return ERROR_FAIL;
	}
	charOffset += intSize;
	if(charOffset < length)
	{
		if(charOffset == length - 1)
		{
			string[charOffset] = 0x00;
			return ERROR_SUCCESS;
		}
		string[charOffset++] = '.';
	}
	else
	{
		return ERROR_CONVERSION_FAIL;
	}

	uint32_t accurancy;
	if(charOffset + UTILS_FLOAT_MAX_ACCURACY < length)
	{
		accurancy = UTILS_FLOAT_MAX_ACCURACY;
	}
	else
	{
		accurancy = length - charOffset;
	}
	/* Calculate decimal digits*/
	if(fp<0.0)fp*=(-1);
	float decimals = (fp - integer)*pow(10,accurancy);
	uint32_t accurancyCpy = accurancy;
	uint32_t range = pow(10,accurancyCpy)/10;
	/* if zeros on the beginning*/
	while(decimals < range)
	{
		string[charOffset++] = '0';
		range = range / 10;
		if(charOffset == length - 1)
		{
			string[charOffset] = 0x00;
			return ERROR_SUCCESS;
		}
	}
	error = UTILS_Int2AsciiString((uint32_t)decimals,&string[charOffset],length);
	if(error != ERROR_SUCCESS)
	{
		return ERROR_FAIL;;
	}
	charOffset += accurancy;
	for(uint8_t fill = charOffset; fill < length; fill++)
	{
		string[fill++] = 0x00;
	}
	return ERROR_SUCCESS;
}
