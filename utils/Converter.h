#pragma once

#include <string>
#include <stdexcept>

namespace utils {
    class Converter {
    public:
        static std::string indexToLetter(int index) {
            return std::string(1, 'A' + index); // Converts 0 to 'A', 1 to 'B', etc.
        }

        // Converts "Location 1", "Location 2", etc., to "Location A", "Location B", etc.
        static std::string convertLocationName(const std::string& locationName) {
            size_t pos = locationName.find(' ');
            if (pos == std::string::npos) {
                throw std::invalid_argument("Invalid location format");
            }
            std::string numberPart = locationName.substr(pos + 1);
            int locationIndex = 0;

            // Convert the number part to an integer
            try {
                locationIndex = std::stoi(numberPart) - 1; // Convert 1-based index to 0-based for letter conversion
            } catch (const std::exception& e) {
                throw std::invalid_argument("Invalid location number");
            }

            // Generate the new location name using the letter
            return "Location " + indexToLetter(locationIndex);
        }
    };
}
