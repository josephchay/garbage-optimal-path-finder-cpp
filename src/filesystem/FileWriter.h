#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "src/authentication/Participant.h"

namespace filesystem {
    class FileWriter {
    private:
        std::string filePath;
        std::vector<authentication::Participant>& participants;

    public:
        FileWriter(const std::string& filePath, std::vector<authentication::Participant>& participants)
                : filePath(filePath), participants(participants) {}

        void updateParticipantDiscount(int id, const std::string& newDiscountCount) {
            auto it = std::find_if(participants.begin(), participants.end(), [&](const authentication::Participant& participant) {
                return participant.getId() == id;
            });

            if (it != participants.end()) {
                it->setDiscountCount(const_cast<string &>(newDiscountCount));
            } else {
                std::cerr << "Participant not found with ID: " << id << std::endl;
            }
        }

        void saveToFile() {
            std::ofstream outFile(filePath, std::ofstream::trunc);  // Open file in truncate mode to overwrite
            if (!outFile.is_open()) {
                throw std::runtime_error("Failed to open file for writing: " + filePath);
            }

            for (const auto& participant : participants) {
                outFile << participant.getId() << ","
                        << participant.getUsername() << ","
                        << participant.getPassword() << ","
                        << participant.getFullName() << ","
                        << participant.getDiscountPoints() << "\n";
            }

            outFile.close();
            std::cout << "All changes saved successfully to file." << std::endl;
        }
    };
}
