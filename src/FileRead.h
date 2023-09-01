#include <fstream>
#include <string>
#include <vector>

void ReadFile(std::vector<uint8_t>& bytes, const std::string& filepath, const size_t size, const size_t from = 0);
void WriteToFile(const std::vector<uint8_t>& bytes, const std::string& filepath);