#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "inttypes.h"

typedef enum
{
	ERROR_SUCCESS 			= 0x00,
	ERROR_NULL_POINTER		= 0x01,
	ERROR_CONVERSION_FAIL	= 0x02
}UTILS_ERROR;

/*
@brief Convert unsigned integer variable to byteArray of size four.
@note	The minimum size of byteArray must be bigger then 4
@param[IN] integer:		unsigned integer value
@param[OUT] byteArray:	pointer on array
@return Utils error:	ERROR_NULL_POINTER - byteArray is equal null \n
						ERROR_SUCCESS	   - conversion executed without errors
 */
UTILS_ERROR UTILS_Uint2ByteArray(uint32_t integer, uint8_t* byteArray);

/*
@brief Convert array of four bytes to unsigned integer
@note The minimum size of byteArray must be bigger then 4
@param[IN] byteArray:	pointer on array
@param[OUT] integer:	pointer on unsigned integer variable
@return Utils error:	ERROR_NULL_POINTER - byteArray or integer are equals null \n
						ERROR_SUCCESS	   - conversion executed without errors
 */
UTILS_ERROR UTILS_ByteArray2Uint(uint8_t* byteArray, uint32_t* integer);


#endif /* INC_UTILS_H_ */
