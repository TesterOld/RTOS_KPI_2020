#define BUF_SIZE 128
#define BUF_MASK (BUF_SIZE-1)

extern unsigned char rIN, rOUT;
extern unsigned int rBuffer [BUF_SIZE];

void buffer_add(unsigned int val);
unsigned int buffer_avg(void);
