#include "InputCollector.h"
#include "validator/InputValidator.h"
#include <string>

namespace collection {
    std::pair<std::string, std::string> InputCollector::collectLoginDetails() {
        std::string username = validation::InputValidator::validateString("username");
        std::string password = validation::InputValidator::validateString("password");

        return std::make_pair(username, password);
    }
} // namespace collection
