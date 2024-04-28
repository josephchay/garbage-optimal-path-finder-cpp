#include <iostream> //Input and Output operations
#include <string> //String operations
#include <vector> //Dynamic array structure operations
#include <stdio.h> //Standard Input/Output operations
#include <stdlib.h> //Standard Library operations
#include <ctime> //To get date and time
#include <cmath> //Math related functions
#include <map> //Store map opearations for key value pairs
#include <limits> //Uses constants that represent the limits of data types
#include <algorithm> //Provides a collection of functions for working with containers 
#include <tuple> //Allows the use of fixed-size collection of elements 
#include <climits> //So INF and INT MAX can be used
#include <fstream> //File operations
#include "GarbageLocations.h" //GarbageLocations header file
#include "NonOptimizedRoute.h" //NonOptimizedRoute header file
#include "GreedyRoute.h" //GreedyRoute header file
#include "OptimizedRoute.h" //OptimizedRoute header file
#include "TSPRoute.h" //TSPRoute header file
#include "Locations.h" //Locations header file
#include "wasteLevel.h" //WasteLevel header file
#include "MapMatrix.h" //DistanceMap header file

using namespace std; //Use standard namespace

int main() { //Main function
    ofstream outFile1("NORoutput.txt"); //Output file for Non-Optimized Route
    ofstream outFile2("GRoutput.txt"); //Output file for Greedy Route
    ofstream outFile3("ORoutput.txt"); //Output file for Optimized Route
    ofstream outFile4("TSPoutput.txt"); //Output file for TSP Route
    ofstream outFile5("MAPoutput.txt"); //Output file for Map
    
    NonOptimizedRoute nonOptimizedRoute; //Creating object for NonOptimizedRoute, instance of the class
    GreedyRoute greedyRoute; //Creating object for GreedyRoute, instance of the class
    OptimizedRoute optimizedRoute; //Creating object for OptimizedRoute, instance of the class
    TSPRoute tspRoute; //Creating object for TSPRoute, instance of the class
    Locations location; //Creating object for Locations, instance of the class
    MapMatrix distancemap; //Creating object for DistanceMap, instance of the class
    wasteLevel wastelevel; //Creating object for WasteLevel, instance of the class
    GarbageLocations garbageLocations; //Creating object for GarbageLocations, instance of the class

    bool loop = true; //Boolean variable loop is true
    bool choice2 = false; //Boolean variable choice2 is false
    bool loopagain = true; //Boolean variable loopagain is true

    cout << "=======================================\n";
    cout << "Welcome to the Waste Management System\n";
    cout << "=======================================\n";

    while (loop == true) { //While loop is true so the loop will intially run first then depending on the condition it will stop
        choice2 = false; //Choice2 is false
        vector<string> locations; //Vector of strings for locations

        cout << "\nSelect a choice from the menu: \n";
        cout << "1. Print Locations Map & Distance Matrix" << endl;
        cout << "2. Print Waste Levels" << endl;
        cout << "3. Calculate and Display Regular Non-Optimized Route" << endl;
        cout << "4. Calculate and Display Floyd Warshall Optimized Route" << endl;
        cout << "5. Calculate and Display Dijkstra Greedy Route" << endl;
        cout << "6. Calculate and Display Travelling Salesman Problem Route" << endl;
        cout << "7. Regenerate Waste Levels" << endl;
        cout << "8. Exit\n" << endl;

        int choice;
        cout << "Choice: ";
        cin >> choice; //User input for choice

        switch (choice) {
            case 1: {
                choice2 = true;
                cout << "\nLocations Map Graph: \n";
                distancemap.printMap(outFile5); //Call the printMap method from the DistanceMap class
                distancemap.printMapInformation(outFile5); //Call the printMapInformation method from the DistanceMap class
                cout << "\n";
                break;
            }
            case 2: {
                wastelevel.wasteLevels(garbageLocations); //Generate an initial waste level for each location
                break;
            }
            case 3: {
                choice2 = true;
                outFile1 << "---------------------------------------------------\n";
                outFile1 << "Non-Optimized Route - Fixed Shortest Path Algorithm\n";
                outFile1 << "---------------------------------------------------\n";

                cout << "---------------------------------------------------\n";
                cout << "Non-Optimized Route - Fixed Shortest Path Algorithm\n";
                cout << "---------------------------------------------------\n";

                outFile1 << "\nDetails of Non-Optimized Route" << endl;
                outFile1 << "1. Waste at location must be >= 40% to be visited." << endl;
                outFile1 << "2. Distance from Waste Station to location must be <= 30km" << endl;
                outFile1 << "3. Duration taken for all visiting locations must be within 12 hours." << endl;

                cout << "\nDetails of Non-Optimized Route" << endl;
                cout << "1. Waste at location must be >= 40% to be visited." << endl;
                cout << "2. Distance from Waste Station to location must be <= 30km" << endl;
                cout << "3. Duration taken for all visiting locations must be within 12 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFile1); //Call the wasteLevels method from the WasteLevel class

                vector<string> shortestPath = nonOptimizedRoute.calculateShortestPath(locations); //Call the calculateShortestPath method from the NonOptimizedRoute class
                nonOptimizedRoute.noSolution(garbageLocations, locations, shortestPath, outFile1); //Call the noSolution method from the NonOptimizedRoute class
                cout << "\n";
                break;
            }
            case 4: {
                choice2 = true;
                outFile3 << "--------------------------------------------\n";
                outFile3 << "Optimized Route - Floyd Warshall Algorithm\n";
                outFile3 << "--------------------------------------------\n";

                cout << "--------------------------------------------\n";
                cout << "Optimized Route - Floyd Warshall Algorithm\n";
                cout << "--------------------------------------------\n";

                outFile3 << "\nDetails of Optimized Route" << endl;
                outFile3 << "1. Waste at location must be >= 50% to be visited." << endl;
                outFile3 << "2. Distance from Waste Station to location must be <= 11km" << endl;
                outFile3 << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                cout << "\nDetails of Optimized Route" << endl;
                cout << "1. Waste at location must be >= 50% to be visited." << endl;
                cout << "2. Distance from Waste STation to location must be <= 11km" << endl;
                cout << "3. Duration taken for all visiting locations must be within 8 hours." << endl;
                
                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFile3); //Call the wasteLevels method from the WasteLevel class

                optimizedRoute.floydWarshall(locations, garbageLocations, outFile3); //Call the floydWarshall method from the OptimizedRoute class
                cout << "\n";
                break;
            }
            case 5: {
                choice2 = true;
                outFile2 << "----------------------------------\n";
                outFile2 << "Greedy Route - Dijkstra Algorithm\n";
                outFile2 << "----------------------------------\n";

                cout << "----------------------------------\n";
                cout << "Greedy Route - Dijkstra Algorithm\n";
                cout << "----------------------------------\n";

                outFile2 << "\nDetails of Greedy Route" << endl;
                outFile2 << "1. Waste at location must be >= 30% to be visited." << endl;
                outFile2 << "2. No distance restriction for the location to be visited" << endl;
                outFile2 << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                cout << "\nDetails of Greedy Route" << endl;
                cout << "1. Waste at location must be >= 30% to be visited." << endl;
                cout << "2. No distance restriction for the location to be visited" << endl;
                cout << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFile2); //Call the wasteLevels method from the WasteLevel class

                int graph[VERTICES][VERTICES]; //Graph with VERTICES vertices and VERTICES edges
                greedyRoute.createGraph(garbageLocations, graph, locations); //Call the createGraph method from the GreedyRoute class
                greedyRoute.dijkstraAlgorithm(graph, 0, locations, garbageLocations, outFile2); //Call the dijkstraAlgorithm method from the GreedyRoute class
                cout << "\n";
                break;
            }
            case 6: {
                choice2 = true;
                outFile4 << "---------------------------------------------------\n";
                outFile4 << "TSP Route - Travelling Salesman Problem Algorithm Using Greedy\n";
                outFile4 << "---------------------------------------------------\n";

                cout << "---------------------------------------------------\n";
                cout << "TSP Route - Travelling Salesman Problem Algorithm Using Greedy\n";
                cout << "---------------------------------------------------\n";

                outFile4 << "\nDetails of TSP Route" << endl;
                outFile4 << "1. Waste at location must be >= 60% to be visited." << endl;
                outFile4 << "2. Distance from Waste Station to location must be <= 12km" << endl;
                outFile4 << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                cout << "\nDetails of TSP Route" << endl;
                cout << "1. Waste at location must be >= 60% to be visited." << endl;
                cout << "2. Distance from Waste Station to location must be <= 12km" << endl;
                cout << "3. Duration taken for all visiting locations must be within 8 hours." << endl;

                location.initializeLocations(locations); //Call the initializeLocations method from the Locations class
                wastelevel.wasteLevels(garbageLocations, outFile4); //Call the wasteLevels method from the WasteLevel class

                int graph[VERTICES][VERTICES]; //Graph with VERTICES vertices and VERTICES edges
                tspRoute.createGraph(graph, locations, garbageLocations); //Call the createGraph method from the TspRoute class
                tspRoute.travellingSalesmanProblem(graph, locations, garbageLocations, outFile4); //Call the travellingSalesmanProblem method from the TspRoute class
                cout << "\n";
                break;
            }
            case 7: {
                choice2 = false;
                garbageLocations.regenerateWasteLevels();
                cout << "Waste levels have been regenerated.\n";
                break;
            }
            case 8: {
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

        if (choice2 == true) { //If the user has selected an algorithm or function then ask the user if they want to run another algorithm or perform other functions
            loopagain = true; 
            while(loopagain == true) {
                cout << "Do you want to continue with another algorithm or other functionalities? (y/n): ";
                char run;
                cin >> run;

                if (run == 'n' || run == 'N') {
                    cout << "\n============================================\n";
                    cout << "Thanks for using the Waste Management System!\n";
                    cout << "=============================================\n";
                    loop = false;
                    loopagain = false;
                } else if (run == 'y' || run == 'Y') {
                    loop = true;
                    loopagain = false;
                } else {
                    cout << "Invalid choice. Please select again." << endl;
                    loop = false;
                    loopagain = true;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }
            }
        }
    }

    return 0;
}