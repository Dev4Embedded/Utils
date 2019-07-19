#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#include "utils.h"

int main()
{
	srand((int)time(NULL));
	printf("Example application has started!\n");
	printf("[TEST] Conversion unsigned integer to byte array \n");
	UTILS_ERROR retval;
	uint32_t doubleWord = rand();
	uint8_t byteArray[4];

	retval = UTILS_Uint2ByteArray(doubleWord,byteArray);

	if(retval)
	{
		printf("UTILS_Uint2ByteArray() return error code: %x", retval);
	}

	printf("Integer value: 0x%x Byte array is consist of: ",doubleWord);
	for(int i=3;i>=0;i--){

		if(byteArray[i]!=0) printf("0x%2x ", byteArray[i]);
	}
	printf("\n");
	printf("[TEST] Conversion byte array to unsiged integer \n");
	doubleWord = 0;
	retval = UTILS_ByteArray2Uint(byteArray,&doubleWord);
	
	if(retval)
	{
		printf("UTILS_ByteArray2Uint() return error code: %x", retval);
	}
	
	printf("Unsigned integer is equal: 0x%x \n", doubleWord);
	
	printf("[TEST] Conversion digit in ASCII format to integer \n");

	char ascii[] = {'0','1','2','3','4','5','6','7','8','9','a','G','!'};
	uint8_t bytes[sizeof(ascii)];

	for(int i=0;i<sizeof(ascii);i++)
	{
		if(UTILS_AsciiDigit2Byte(ascii[i],&bytes[i]) == ERROR_SUCCESS){
			printf("Convert operation success form ASCII:'%c' to INTEGER:%u \n",ascii[i],bytes[i]);
		}
		else
		{
			printf("Cannot convert '%c' character!\n", ascii[i]);
		}
	}

	printf("[TEST] Conversion single digit to digit in ASCII format");

	for(int i=0;i<sizeof(ascii);i++)
	{
		if(UTILS_Byte2AsciiDigit(bytes[i],&ascii[i]) == ERROR_SUCCESS){
			printf("Convert operation success form INTEGER:%u to ASCII:'%c' \n",bytes[i],ascii[i]);
		}
		else
		{
			printf("Cannot convert value %u to ASCII!\n", bytes[i]);
		}
	}

	printf("[TEST] Conversion string to integer and integer conversion to string \n");

	UTILS_ERROR error;
	uint8_t digits;
	char str[11];
	int32_t number;

	for (int i = 0; i < 10; i++) {
		number = rand();
		if (i % 2)
			number *= -1;

		error = UTILS_GetNumberOfDigit(number, &digits);
		printf("Number %i consist of %u numbers.\n", number, digits);
		error = UTILS_Int2AsciiString(number, str, sizeof(str));
		printf("Number %i after conversion to string \"%s\"\n", number, str);

		error = UTILS_AsciiString2Int(str, &number);
		switch (error) {
		case ERROR_SUCCESS:
			printf("Integer value in ASCII string \"%s\" converted to integer: %i \n",str, number);
			break;
		case ERROR_NULL_POINTER:
		case ERROR_CONVERSION_FAIL:
		default:
			printf("Conversion failure!\n");
			break;
		}
	}
}
