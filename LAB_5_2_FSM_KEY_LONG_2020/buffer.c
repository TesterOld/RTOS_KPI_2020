#include "buffer.h"
unsigned char rIN=0;
unsigned char rOUT=0;
unsigned int rBuffer [BUF_SIZE];

void buffer_add(unsigned int val)
{
	rBuffer[rIN++] = val;
	// Sense in mask value. Value is 0111111 (VALUE!!)
	// If next rang (razriad) then to 0
    rIN &= BUF_MASK;// Set to 0. Ring Buffer 
}

unsigned int buffer_avg(void)
{
	long long summ=0;
	for(int i=0;i<BUF_SIZE;i++)summ+=rBuffer[i];
	summ=summ/BUF_SIZE;
	return summ;
}
