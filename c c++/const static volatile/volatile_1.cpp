volatile unsigned int *output = (unsigned int *)0xff800000U;    //定义一个IO端口；
void init(void)
{
	*output = 0x55;
    *output = 0x66;
    *output = 0x88;
}