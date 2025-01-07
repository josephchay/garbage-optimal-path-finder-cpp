#include "Config.h"

namespace data {
    const int Config::VERSION = 1;
    const std::string Config::PARTICIPANTS_FILE_PATH = R"(../data/records/participants.txt)";
    const std::string Config::BEST_ROUTE_OUTPUT_FILE_PATH = R"(../data/records/BestROutput.txt)";
    const std::string Config::GREEDY_ROUTE_OUTPUT_FILE_PATH = R"(../data/records/GROutput.txt)";
    const std::string Config::NON_OPTIMIZED_ROUTE_OUTPUT_FILE_PATH = R"(../data/records/NOROutput.txt)";
    const std::string Config::OPTIMIZED_ROUTE_OUTPUT_FILE_PATH = R"(../data/records/OROutput.txt)";
    const std::string Config::TRAVELLING_SALESMAN_PROBLEM_OUTPUT_FILE_PATH = R"(../data/records/TSPOutput.txt)";
    const std::string Config::MAP_OUTPUT_FILE_PATH = R"(../data/records/MAPOutput.txt)";
}
