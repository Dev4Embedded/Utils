#include "utils.h"

/*
@brief Convert unsigned integer variable to byteArray of size of four.
@note	The minimum size of byteArray must be bigger then 4
@param[IN] integer:		unsigned integer value
@param[OUT] byteArray:	pointer on array
@return Utils error:	ERROR_NULL_POINTER - byteArray is equal null \n
						ERROR_SUCCESS	   - conversion executed without errors
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
/*
@brief Convert array of four bytes to unsigned integer
@note The minimum size of byteArray must be bigger then 4
@param[IN] byteArray:	pointer on array
@param[OUT] integer:	pointer on unsigned integer variable
@return Utils error:	ERROR_NULL_POINTER - byteArray or integer are equals null \n
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
