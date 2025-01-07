#include <iostream> //Input and Output operations
#include <string> //String operations
#include <vector> //Dynamic array structure operations
#include <limits> //Uses constants that represent the limits of data types
#include <tuple> //Allows the use of fixed-size collection of elements
#include <fstream> //File operations
#include <memory>
#include "src/maps/GarbageLocations.h" //GarbageLocations header file
#include "src/routes/NonOptimizedRoute.h" //NonOptimizedRoute header file
#include "src/routes/GreedyRoute.h" //GreedyRoute header file
#include "src/routes/OptimizedRoute.h" //OptimizedRoute header file
#include "src/routes/TSPRoute.h" //TSPRoute header file
#include "src/maps/Locations.h" //Locations header file
#include "src/maps/wasteLevel.h" //WasteLevel header file
#include "src/maps/MapMatrix.h" //DistanceMap header file
#include "src/authentication/Login.h"
#include "src/collection/InputCollector.h"
#include "src/filesystem/FileReader.h"
#include "data/Config.h"
#include "src/metrics/Metrics.h"
#include "src/filesystem/FileWriter.h"

using namespace std; //Use standard namespace

int main() { //Main function
    ofstream outFileNO(data::Config::NON_OPTIMIZED_ROUTE_OUTPUT_FILE_PATH); //Output file for Non-Optimized Route
    ofstream outFileGR(data::Config::GREEDY_ROUTE_OUTPUT_FILE_PATH); //Output file for Greedy Route
    ofstream outFileOR(data::Config::OPTIMIZED_ROUTE_OUTPUT_FILE_PATH); //Output file for Optimized Route
    ofstream outFileTSP(data::Config::TRAVELLING_SALESMAN_PROBLEM_OUTPUT_FILE_PATH); //Output file for TSP Route
    ofstream outFileMAP(data::Config::MAP_OUTPUT_FILE_PATH); //Output file for Map
    ofstream outFileBestR(data::Config::BEST_ROUTE_OUTPUT_FILE_PATH); //Output file for Best Route

    std::vector<authentication::Participant> participants;
    std::unique_ptr<authentication::Participant> currentParticipant;

    /**
     * @brief The list of participants in the blockchain network.
     */
    filesystem::FileReader fileReaderParticipant(data::Config::PARTICIPANTS_FILE_PATH, filesystem::DataType::PARTICIPANTS);
    participants = fileReaderParticipant.getParticipants();

    cout << "=======================================\n";
    cout << "Welcome to the Waste Management System\n";
    cout << "=======================================\n\n";

    authentication::Login login;
    bool isAuthenticated = false;
    std::string username, password;

    while (!isAuthenticated) {
        std::tie(username, password) = collection::InputCollector::collectLoginDetails();

        for (const auto &participant: participants) {
            if (login.authenticate(username, password, participant)) {
                isAuthenticated = true;
                currentParticipant = std::make_unique<authentication::Participant>(participant);
                break; // Exit the for loop
            }
        }

        if (!isAuthenticated) {
            std::cout << "Invalid username or password. Please try again." << std::endl << std::endl;
        } else {
            break; // Exit the while loop since authentication was successful
        }
    }

    // Proceed with the authenticated currentParticipant.
    std::cout << "Welcome back, " << currentParticipant->getFullName() << "!" << std::endl << std::endl;

    NonOptimizedRoute nonOptimizedRoute; //Creating object for NonOptimizedRoute, instance of the class
    GreedyRoute greedyRoute; //Creating object for GreedyRoute, instance of the class
    OptimizedRoute optimizedRoute; //Creating object for OptimizedRoute, instance of the class
    TSPRoute tspRoute; //Creating object for TSPRoute, instance of the class
    Locations location; //Creating object for Locations, instance of the class
    MapMatrix distancemap; //Creating object for DistanceMap, instance of the class
    wasteLevel wastelevel; //Creating object for WasteLevel, instance of the class
    GarbageLocations garbageLocations; //Creating object for GarbageLocations, instance of the class

    filesystem::FileWriter writer(data::Config::PARTICIPANTS_FILE_PATH, participants);

    bool loop = true; //Boolean variable loop is true
    bool choice2 = false; //Boolean variable choice2 is false
    bool askForTravel = false; //Boolean variable askForTravel is true
    bool askAnotherAlgo = true; //Boolean variable askAnotherAlgo is true
    bool travelBestRoute = false; //Boolean variable travelBestRoute is false

    while (loop == true) { //While loop is true so the loop will intially run first then depending on the condition it will stop
        choice2 = false; //Choice2 is false
        vector<string> locations; //Vector of strings for locations

        cout << "\nSelect a choice from the menu: \n";
        cout << "1. Print Locations Map & Distance Matrix" << endl;
        cout << "2. Print Waste Levels" << endl;
        cout << "3. Print Weather Conditions" << endl;
        cout << "4. Calculate and Display Regular Non-Optimized Route" << endl;
        cout << "5. Calculate and Display Floyd Warshall Optimized Route" << endl;
        cout << "6. Calculate and Display Dijkstra Greedy Route" << endl;
        cout << "7. Calculate and Display Travelling Salesman Problem Route" << endl;
        cout << "8. Regenerate Waste Levels" << endl;
        cout << "9. Calculate and Display Post-selection Best Route" << endl;
        cout << "10. Exit\n" << endl;

        int choice;
        cout << "Choice: ";
        cin >> choice; //User input for choice

        switch (choice) {
            case 1: {
                choice2 = true;
                cout << "\nLocations Map Graph: \n";
                distancemap.printMap(outFileMAP); //Call the printMap method from the DistanceMap class
                distancemap.printMapInformation(outFileMAP); //Call the printMapInformation method from the DistanceMap class
                cout << "\n";
                break;
            }
            case 2: {
                wastelevel.wasteLevels(garbageLocations); // see the waste levels
                break;
            }
            case 3: {
                locationWeather.locationWeathers(garbageLocations); // see the weather conditions
                break;
            }
            case 4: {
                choice2 = true;
                outFileNO << "---------------------------------------------------\n";
                outFileNO << "Non-Optimized Route - Fixed Shortest Path Algorithm\n";
                outFileNO << "---------------------------------------------------\n";

                cout << "---------------------------------------------------\n";
                cout << "Non-Optimized Route - Fixed Shortest Path Algorithm\n";
                cout << "---------------------------------------------------\n";

                outFileNO << "\nDetails of Non-Optimized Route" << endl;
                outFileNO << "1. Waste at location must be >= 40% to be visited." << endl;
                outFileNO << "2. Distance from Waste Station to location must be <= 30km" << endl;
                outFileNO << "3. Duration taken for all visiting locations must be within 12 hours." << endl;

                cout << "\nDetails of Non-Optimized Route" << endl;
                cout << "1. Waste at location must be >= 40% to be visited." << endl;
                cout << "2. Distance from Waste Station to location must be <= 30km" << endl;
                cout << "3. Duration taken for all visiting locations must be within 12 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFileNO); //Call the wasteLevels method from the WasteLevel class

                vector<string> shortestPath = nonOptimizedRoute.calculateShortestPath(locations); //Call the calculateShortestPath method from the NonOptimizedRoute class
                auto results = nonOptimizedRoute.noSolution(garbageLocations, locations, shortestPath, outFileNO, false); //Call the noSolution method from the NonOptimizedRoute class
                cout << "\n";
                break;
            }
            case 5: {
                choice2 = true;
                outFileOR << "--------------------------------------------\n";
                outFileOR << "Optimized Route - Floyd Warshall Algorithm\n";
                outFileOR << "--------------------------------------------\n";

                cout << "--------------------------------------------\n";
                cout << "Optimized Route - Floyd Warshall Algorithm\n";
                cout << "--------------------------------------------\n";

                outFileOR << "\nDetails of Optimized Route" << endl;
                outFileOR << "1. Waste at location must be >= 50% to be visited." << endl;
                outFileOR << "2. Distance from Waste Station to location must be <= 11km" << endl;
                outFileOR << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                cout << "\nDetails of Optimized Route" << endl;
                cout << "1. Waste at location must be >= 50% to be visited." << endl;
                cout << "2. Distance from Waste STation to location must be <= 11km" << endl;
                cout << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFileOR); //Call the wasteLevels method from the WasteLevel class

                auto results = optimizedRoute.floydWarshall(locations, garbageLocations, outFileOR, false); //Call the floydWarshall method from the OptimizedRoute class
                cout << "\n";
                break;
            }
            case 6: {
                choice2 = true;
                outFileGR << "----------------------------------\n";
                outFileGR << "Greedy Route - Dijkstra Algorithm\n";
                outFileGR << "----------------------------------\n";

                cout << "----------------------------------\n";
                cout << "Greedy Route - Dijkstra Algorithm\n";
                cout << "----------------------------------\n";

                outFileGR << "\nDetails of Greedy Route" << endl;
                outFileGR << "1. Waste at location must be >= 30% to be visited." << endl;
                outFileGR << "2. No distance restriction for the location to be visited" << endl;
                outFileGR << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                cout << "\nDetails of Greedy Route" << endl;
                cout << "1. Waste at location must be >= 30% to be visited." << endl;
                cout << "2. No distance restriction for the location to be visited" << endl;
                cout << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFileGR); //Call the wasteLevels method from the WasteLevel class

                int graph[VERTICES][VERTICES]; //Graph with VERTICES vertices and VERTICES edges
                greedyRoute.createGraph(garbageLocations, graph, locations); //Call the createGraph method from the GreedyRoute class
                auto results = greedyRoute.dijkstraAlgorithm(graph, 0, locations, garbageLocations, outFileGR, false); //Call the dijkstraAlgorithm method from the GreedyRoute class
                cout << "\n";
                break;
            }
            case 7: {
                choice2 = true;
                outFileTSP << "---------------------------------------------------\n";
                outFileTSP << "TSP Route - Travelling Salesman Problem Algorithm Using Greedy\n";
                outFileTSP << "---------------------------------------------------\n";

                cout << "---------------------------------------------------\n";
                cout << "TSP Route - Travelling Salesman Problem Algorithm Using Greedy\n";
                cout << "---------------------------------------------------\n";

                outFileTSP << "\nDetails of TSP Route" << endl;
                outFileTSP << "1. Waste at location must be >= 60% to be visited." << endl;
                outFileTSP << "2. Distance from Waste Station to location must be <= 12km" << endl;
                outFileTSP << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                cout << "\nDetails of TSP Route" << endl;
                cout << "1. Waste at location must be >= 60% to be visited." << endl;
                cout << "2. Distance from Waste Station to location must be <= 12km" << endl;
                cout << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFileTSP); //Call the wasteLevels method from the WasteLevel class

                int graph[VERTICES][VERTICES]; //Graph with VERTICES vertices and VERTICES edges
                tspRoute.createGraph(graph, locations, garbageLocations); //Call the createGraph method from the TspRoute class
                auto results = tspRoute.travellingSalesmanProblem(graph, locations, garbageLocations, outFileTSP, false); //Call the travellingSalesmanProblem method from the TspRoute class
                cout << "\n";
                break;
            }
            case 8: {
                choice2 = false;
                garbageLocations.regenerateWasteLevels();
                cout << "Waste levels have been regenerated.\n";
                break;
            }
            case 9: {
                choice2 = true;
                travelBestRoute = true;

                vector<metrics::Metrics> allRoutesMetrics;

                // Initialize and gather data for locations and waste levels
                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFileBestR); //Call the wasteLevels method from the WasteLevel class

                vector<string> shortestPath = nonOptimizedRoute.calculateShortestPath(locations); //Call the calculateShortestPath method from the NonOptimizedRoute class
                auto metricsNonOptimized = nonOptimizedRoute.noSolution(garbageLocations, locations, shortestPath, outFileBestR,
                                                                        true); //Call the noSolution method from the NonOptimizedRoute class

                auto metricsOptimized = optimizedRoute.floydWarshall(locations, garbageLocations, outFileBestR, true);

                int graphGreedy[VERTICES][VERTICES]; //Graph with VERTICES vertices and VERTICES edges
                greedyRoute.createGraph(garbageLocations, graphGreedy, locations); //Call the createGraph method from the GreedyRoute class
                auto metricsGreedy = greedyRoute.dijkstraAlgorithm(graphGreedy, 0, locations, garbageLocations, outFileBestR,
                                                                   true);

                int graphTsp[VERTICES][VERTICES]; //Graph with VERTICES vertices and VERTICES edges
                tspRoute.createGraph(graphTsp, locations, garbageLocations); //Call the createGraph method from the TspRoute class
                auto metricsTSP = tspRoute.travellingSalesmanProblem(graphTsp, locations, garbageLocations, outFileBestR,
                                                                     true);

                // Add to the vector for comparison
                allRoutesMetrics.push_back(metricsNonOptimized);
                allRoutesMetrics.push_back(metricsOptimized);
                allRoutesMetrics.push_back(metricsGreedy);
                allRoutesMetrics.push_back(metricsTSP);

                // Determine the best route
                int bestIndex = findBestScenario(allRoutesMetrics);

                // Output the best route's details
                metrics::Metrics& bestMetrics = allRoutesMetrics[bestIndex];

                writer.updateParticipantDiscount(currentParticipant->getId(), std::to_string(std::stoi(
                        currentParticipant->getDiscountPoints()) + 1));
                writer.saveToFile();  // Save all changes back to the file

                cout << "Analyzing the best route algorithm..." << endl;
                cout << "Best Route Determined: " << bestMetrics.name << endl;
                cout << bestMetrics.info << endl;

                if (std::stoi(currentParticipant->getDiscountPoints()) >= 3) {
                    bestMetrics.driverWage -= bestMetrics.driverWage * 0.1;
                    writer.updateParticipantDiscount(currentParticipant->getId(), std::to_string(std::stoi(
                            currentParticipant->getDiscountPoints()) - 3));
                    writer.saveToFile();  // Save all changes back to the file
                    cout << "New Driver Wage for visiting all locations (RM): " << bestMetrics.driverWage << " after deducting 10%" << endl << endl;
                }

                std::cout << "Here's a detailed comparison with other routes:\n";

                for (int i = 0; i < allRoutesMetrics.size(); ++i) {
                    if (i != bestIndex) {
                        std::cout << bestMetrics.compare(allRoutesMetrics[i]) << "\n";
                    }
                }
                break;
            }
            case 10: {
                choice2 = false;
                cout << "\n============================================\n";
                cout << "Thanks for using the Waste Management System!\n";
                cout << "=============================================\n";
                return 0;
            }
            default: { //If the user enters an invalid choice then clear the input buffer and ask the user to enter a valid choice
                cout << "Invalid choice! Please select again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        if (choice2) {
            askForTravel = true;

            while (askForTravel) {
                cout << "Do you want to travel this path? (y/n): ";
                char travel;
                cin >> travel;

                if (travel == 'y' || travel == 'Y' || travel == 'n' || travel == 'N') {
                    if (travelBestRoute && (travel == 'y' || travel == 'Y')) {
                        cout << "Congratulations! You have got 1 discount point for selecting the best route." << endl;
                        cout << "Your current Discount Points: " << std::stoi(currentParticipant->getDiscountPoints()) + 1 << "\n\n";
                    }

                    askForTravel = false;
                    askAnotherAlgo = true;

                    while (askAnotherAlgo) { //While loop for asking the user if they want to continue with another algorithm or other functionalities
                        cout << "Do you want to continue with another algorithm or other functionalities? (y/n): ";
                        char run;
                        cin >> run;

                        if (run == 'n' || run == 'N') {
                            cout << "\n============================================\n";
                            cout << "Thanks for using the Waste Management System!\n";
                            cout << "=============================================\n";
                            loop = false;
                            askAnotherAlgo = false;
                        } else if (run == 'y' || run == 'Y') {
                            loop = true;
                            askAnotherAlgo = false;
                        } else {
                            cout << "Invalid choice. Please select again." << endl;
                            loop = false;
                            askAnotherAlgo = true;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                } else {
                    cout << "Invalid input. Please enter 'y' or 'n'.\n";
                }
            }
        }
    }

    return 0;
}