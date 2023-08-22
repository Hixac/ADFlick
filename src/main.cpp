#include <Media/Device.h>
#include <Media/DeviceEnumerator.h>
#include <AudioSource/WaveOut.h>

#include <iostream>

int main(void)
{
	INIT_LOG();

	Media::WaveOut("res/w.wav");

	return 0;
}