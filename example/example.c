#include <stdio.h>
#include <inttypes.h>

#include "utils.h"

int main()
{
	printf("Example application has started!\n");

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
};
