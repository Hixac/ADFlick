#include <Media/Device.h>

#include <iostream>

int main(void)
{
	INIT_LOG();

	Media::Device device(0);
	LOG_INFO(device.GetDeviceName());
	
	return 0;
}