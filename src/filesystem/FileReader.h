#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <set>
#include <vector>
#include <regex>
#include "../authentication/Participant.h"

namespace filesystem {
    enum class DataType {
        PARTICIPANTS,
    };

    class FileReader {
    public:
        explicit FileReader(const std::string& filePath, DataType datatype);

        void parseParticipantFile(const std::string& filePath);
        [[nodiscard]] const std::vector<authentication::Participant>& getParticipants() const;

    private:
        std::vector<std::string> orderedOptions;
        std::vector<authentication::Participant> participants;

        std::map<std::string, std::vector<std::string>> idToDataMap;
        static void trim(std::string& s);
    };
} // namespace filesystem

#endif // FILEREADER_H
