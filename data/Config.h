#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace data {
    class Config {
    public:
        static const int VERSION; /** The version of the blockchain */
        static const std::string PARTICIPANTS_FILE_PATH; /** The path to the participants file */
        static const std::string BEST_ROUTE_OUTPUT_FILE_PATH; /** The path to the best route output file */
        static const std::string GREEDY_ROUTE_OUTPUT_FILE_PATH; /** The path to the greedy route output file */
        static const std::string NON_OPTIMIZED_ROUTE_OUTPUT_FILE_PATH; /** The path to the non-optimized route output file */
        static const std::string OPTIMIZED_ROUTE_OUTPUT_FILE_PATH; /** The path to the optimized route output file */
        static const std::string TRAVELLING_SALESMAN_PROBLEM_OUTPUT_FILE_PATH; /** The path to the travelling salesman problem output file */
        static const std::string MAP_OUTPUT_FILE_PATH; /** The path to the map output file */
    };
} // namespace blockchain

#endif // CONFIG_H
