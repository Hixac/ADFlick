#include <FileRead.h>

void ReadFile(std::vector<uint8_t>& bytes, const std::string& filepath, const size_t size, const size_t from)
{
	std::ifstream file(filepath, std::ios::binary);
	file.seekg(from, std::ios::beg);

	for (size_t i = 0; i < size; i++)
	{
		uint8_t data;
		file.read(reinterpret_cast<char*>(&data), 1);

		bytes.push_back(data);
	}
}

void WriteToFile(const std::vector<uint8_t>& bytes, const std::string& filepath)
{
	std::ofstream file(filepath, std::ios::binary);
	
	for (auto i = bytes.begin(); i != bytes.end(); i++)
	{
		file.write(reinterpret_cast<char*>(*i), 1);
	}
}