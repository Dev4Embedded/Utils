#include <stdio.h>
#include <inttypes.h>

#include "utils.h"

int main()
{
	printf("Example application has started!\n");

	UTILS_ERROR retval;
	uint32_t doubleWord = 0xAABBCCDD;
	uint8_t byteArray[4];

	retval = UTILS_Uint2ByteArray(doubleWord,byteArray);

	if(retval)
	{
		printf("UTILS_Uint2ByteArray() return error code: %x", retval);
		return -1;
	}

	printf("Byte array is consist of: ");
	for(int i=3;i>=0;i--) printf("0x%2x ", byteArray[i]);

	doubleWord = 0;
	retval = UTILS_ByteArray2Uint(byteArray,&doubleWord);
	if(retval)
	{
		printf("UTILS_ByteArray2Uint() return error code: %x", retval);
		return -1;
	}
	printf("Unsigned integer is equal: 0x%8x", doubleWord);

}
