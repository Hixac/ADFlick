#include <Media/Device.h>
#include <Media/DeviceEnumerator.h>

#include <iostream>

int main(void)
{
	INIT_LOG();

	LOG_INFO("Hello world!");

	Media::DeviceEnumerator::Instance().RegisterCallback();

	Media::Device device;
	LOG_INFO(device.GetDeviceName());
	device.Activate();

	while (true) 
	{
		std::cin.get();
	}

	return 0;
}