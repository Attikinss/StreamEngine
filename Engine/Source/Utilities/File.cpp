#include "File.h"

#include <fstream>
#include <sstream>

namespace SE {
    bool File::Exists(const std::string& filepath) {
        return std::ifstream(filepath.c_str()).good();
    }

    std::string File::ReadAllText(const std::string& filepath) {
        // Open file with cursor at end of file
        std::ifstream fileStream(filepath, std::ios::binary);

        if (!fileStream.is_open()) {
            // TODO: Notify user
            return std::string();
        }

        // Read entire file to buffer
        std::stringstream buffer;
        buffer << fileStream.rdbuf();

        return buffer.str();
    }

    std::vector<std::string> File::ReadAllLines(const std::string& filepath) {
        // Open file with cursor at end of file
        std::ifstream fileStream(filepath, std::ios::binary);

        if (!fileStream.is_open()) {
            // TODO: Notify user
            return std::vector<std::string>();
        }

        std::vector<std::string> lines;
        std::string currentLine;

        // Add all file lines
        while (std::getline(fileStream, currentLine)) {
            lines.push_back(currentLine);
        }

        return lines;
    }

    std::vector<char> File::ReadAllChars(const std::string& filepath) {
        // Open file with cursor at end of file
        std::ifstream fileStream(filepath, std::ios::ate | std::ios::binary);

        if (!fileStream.is_open()) {
            // TODO: Notify user
            return std::vector<char>();
        }

        // Get total char count of file
        size_t fileSize = static_cast<size_t>(fileStream.tellg());
        std::vector<char> buffer(fileSize);

        // Return to start of file
        fileStream.seekg(0);

        // Read entire file to char buffer then close
        fileStream.read(buffer.data(), fileSize);
        fileStream.close();

        return buffer;
    }

    void File::WriteAllText(const std::string& filepath, const std::string& text) {
        std::ofstream file(filepath.c_str());

        if (file.is_open()) {
            file << text;
            file.close();
        }

        // TODO: Notify user that the file doesn't exist
    }

    void File::WriteAllLines(const std::string& filepath, const std::vector<std::string>& lines) {
        std::ofstream file(filepath.c_str());

        if (file.is_open()) {
            for (uint32_t i = 0; i < lines.size(); i++) {
                file << lines[i] << std::endl;
            }

            file.close();
        }

        // TODO: Notify user that the file doesn't exist
    }

    void File::WriteAllChars(const std::string& filepath, const std::vector<char>& chars) {
        std::ofstream file(filepath.c_str());

        if (file.is_open()) {
            file.write(&chars[0], chars.size());
            file.close();
        }

        // TODO: Notify user that the file doesn't exist
    }
}