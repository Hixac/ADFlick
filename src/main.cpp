#include <Media/Device.h>
#include <Media/DeviceEnumerator.h>
#include <AudioSource/WaveOut.h>

#include <boost/filesystem.hpp>

int main(void)
{
	INIT_LOG();

	std::string path = boost::filesystem::absolute("res\\w.wav").string();
	Media::WaveOut audio(path);

	return 0;
}