#pragma once
#include <string>
#include <vector>

namespace SE {
	class File {
	public:
		static bool Exists(const std::string& filepath);

		static std::string ReadAllText(const std::string& filepath);
		static std::vector<std::string> ReadAllLines(const std::string& filepath);
		static std::vector<char> ReadAllChars(const std::string& filepath);

		static void WriteAllText(const std::string& filepath, const std::string& text);
		static void WriteAllLines(const std::string& filepath, const std::vector<std::string>& lines);
		static void WriteAllChars(const std::string& filepath, const std::vector<char>& chars);

		static std::vector<std::string> GetFilesAtDirectory(const std::string& filepath);
	};
}