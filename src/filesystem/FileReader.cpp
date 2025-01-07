#include "FileReader.h"
#include "src/utils/Structures.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>

namespace filesystem {
    FileReader::FileReader(const std::string& filePath, DataType datatype) {
        switch (datatype) {
            case DataType::PARTICIPANTS:
                parseParticipantFile(filePath);
                break;
            default:
                std::cerr << "Unsupported file type" << std::endl;
                break;
        }
    }

    const std::vector<authentication::Participant>& FileReader::getParticipants() const {
        return participants;
    }

    void FileReader::parseParticipantFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        while (getline(file, line)) {
            std::vector<std::string> tokens = utils::Structures::splitLine(line);

            try {
                int id = std::stoi(tokens[0]);
                std::string username = tokens[1];
                std::string password = tokens[2];
                std::string fullName = tokens[3];
                std::string discountCount = tokens[4];

                participants.emplace_back(id, username, password, fullName, discountCount);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << e.what() << std::endl;
            }
        }
    }

    void FileReader::trim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
} // namespace filesystem
