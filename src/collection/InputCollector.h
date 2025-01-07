#pragma once

#include <utility>
#include <string>

namespace collection {
    class InputCollector {
    public:
        /**
         * @brief Collects username and password details from the user.
         *
         * @return
         */
        static std::pair<std::string, std::string> collectLoginDetails();
    };
}
