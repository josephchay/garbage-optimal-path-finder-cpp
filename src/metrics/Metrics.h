#pragma once

#include <vector>
#include <iostream>
#include <limits>

namespace metrics {
// Define a structure to hold the metrics for each scenario
    struct Metrics {
        std::string name; // Name of the route
        std::string info; // Detailed route information
        float driverWage;
        float totalDistance;
        double totalCost;
        double totalTime;
        double totalFuelConsumption;
        int totalWasteCollected;
        int wasteInKG;

        std::string compare(const Metrics& other) const {
            std::stringstream ss;
            ss << name << " vs. " << other.name << ":\n";
            ss << "- Distance Saved (km): " << (other.totalDistance - totalDistance) << "\n";
            ss << "- Cost Saved (RM): " << (other.totalCost - totalCost) << "\n";
            ss << "- Time Saved (hours): " << (other.totalTime - totalTime) << "\n";
            ss << "- Fuel Savings (litres): " << (other.totalFuelConsumption - totalFuelConsumption) << "\n";
            ss << "- Waste Collection Advantage (kg): " << (other.totalWasteCollected - totalWasteCollected) << "\n";
            return ss.str();
        }
    };

    // Function to compare multiple sets of metrics and determine the best scenario
    int findBestScenario(const std::vector<Metrics>& scenarios) {
        // Define weights for each metric
        const float weightDistance = -1.0;  // Negative because lower is better
        const float weightCost = -1.0;      // Negative because lower is better
        const float weightTime = -1.0;      // Negative because lower is better
        const float weightFuel = -1.0;      // Negative because lower is better
        const float weightWaste = 1.0;      // Positive because higher is better
        const float weightWasteKG = 1.0;    // Positive because higher is better

        std::vector<double> scores(scenarios.size(), 0.0);
        double maxScore = std::numeric_limits<double>::lowest();
        int bestIndex = -1;

        // Compute score for each scenario
        for (size_t i = 0; i < scenarios.size(); ++i) {
            double score = scenarios[i].totalDistance * weightDistance +
                           scenarios[i].totalCost * weightCost +
                           scenarios[i].totalTime * weightTime +
                           scenarios[i].totalFuelConsumption * weightFuel +
                           scenarios[i].totalWasteCollected * weightWaste +
                           scenarios[i].wasteInKG * weightWasteKG;
            scores[i] = score;

            // Track the best scenario
            if (score > maxScore) {
                maxScore = score;
                bestIndex = static_cast<int>(i);
            }
        }

        return bestIndex;
    }
}
