#include "CRC.h"

char calc_CRC(char buffer[],int count)
{
	char res=buffer[0];
	for(int i=1;i<count;i++)res=res^buffer[i];
	return res;
}

char check_CRC(char buffer[],int count)
{
	char res=buffer[0];
	for(int i=1;i<count-1;i++)res^=buffer[i];
	if(res==buffer[count-1])return 0xFF;
	return 0;
}
