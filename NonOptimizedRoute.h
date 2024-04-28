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
#include "GarbageLocations.h" //Include the GarbageLocations header file
#include "wasteLevel.h" //Include the wasteLevel header file

#ifndef NON_OPTIMIZED_ROUTE_H //Header file guard
#define NON_OPTIMIZED_ROUTE_H //Header file guard

using namespace std; //Use standard namespace

class NonOptimizedRoute { //Class for the NonOptimizedRoute

public: //public specifier
    void noSolution(GarbageLocations& garbageLocations, const vector<string>& currentLocations, const vector<string>& shortestPathLocations, ofstream& outFileNOR) { //Non-Optimized solution for the route
        cout << "Travel Paths:" << endl;
        outFileNOR << "Travel Paths:" << endl;

        int totalDistance = 0; //Initiailizing the totalDistance variable to 0
        int totalWasteCollected = 0; //Initiailizing the totalWasteCollected variable to 0
        double totalTime = 0;
        double totalFuelConsumption = 0;
        double totalCost = 0;
        float driverWage = 0; //Initiailizing the float totalCost, totalTime, totalFuelConsumption and driverWage variables to 0
        int wasteInKG = 0; //Initiailizing the wasteInKG variable to 0

        vector<string> locationsWithin12Hours; //Creating a vector of strings called locationsWithin12Hours

        for (int index = 1; index < currentLocations.size(); index++) { //For loop to iterate through the currentLocations vector, this is all the locations in the distance matrix
            if (garbageLocations.wasteLevels[currentLocations[index]] >= 40) { //Check if the waste level is greater than or equal to 40
                int pathDistanceFromWasteStation = 0; //Initiailizing the pathDistanceFromWasteStation variable to 0
                cout << "---------- " << currentLocations[index] << " ----------\n"; //Output the current location
                outFileNOR << "---------- " << currentLocations[index] << " ----------\n"; //Output the current location

                for (int index2 = 1; index2 < shortestPathLocations.size(); index2++) { //Loop the shortestPathLocations vector
                    if (shortestPathLocations[index2] == currentLocations[index]) {
                        for (int index3 = 1; index3 <= index2; index3++) {
                            int findIndex = index3 - 1;
                            pathDistanceFromWasteStation += garbageLocations.distanceMatrix[shortestPathLocations[findIndex]][shortestPathLocations[index3]];
                        }
                        if (pathDistanceFromWasteStation <= 30) { //Check if the distance from the waste station to target location is less than or equal to 30
                            totalDistance += pathDistanceFromWasteStation;
                            totalWasteCollected += garbageLocations.wasteLevels[currentLocations[index]]; //Find the total waste collected
                            cout << "Distance from waste station (km): ";
                            outFileNOR << "Distance from waste station (km): ";
                            cout << pathDistanceFromWasteStation;
                            outFileNOR << pathDistanceFromWasteStation;

                            cout << "\nPath: ";
                            outFileNOR << "\nPath: ";

                            for (int index4 = 0; index4 <= index2; index4++) { //Loop through the second index to display the path
                                cout << shortestPathLocations[index4];
                                outFileNOR << shortestPathLocations[index4];
                                if (index4 != index2) {
                                    cout << " -> ";
                                    outFileNOR << " -> ";
                                }
                            }

                            auto weather = garbageLocations.locationWeathers[currentLocations[index]];

                            cout << "\nWeather: " << weather;
                            outFileNOR << "\nWeather: " << weather;

                            // if sunny .1 hr per km, cloudy .2 hr per km, rainy .3 hr per km
                            if (weather == "Sunny") {
                                totalTime += pathDistanceFromWasteStation * 0.1;
                                cout << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.1 << endl;
                                outFileNOR << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.1 << endl;
                            } else if (weather == "Cloudy") {
                                totalTime += pathDistanceFromWasteStation * 0.2;
                                cout << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.2 << endl;
                                outFileNOR << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.2 << endl;
                            } else if (weather == "Rainy") {
                                totalTime += pathDistanceFromWasteStation * 0.3;
                                cout << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.3 << endl;
                                outFileNOR << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.3 << endl;
                            } else if (weather == "Flooding") {
                                totalTime += pathDistanceFromWasteStation * 0.4;
                                cout << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.4 << endl;
                                outFileNOR << "\nDuration per way (hours): " << pathDistanceFromWasteStation * 0.4 << endl;
                            }

                            totalCost += (pathDistanceFromWasteStation * 2.5);
                            cout << "Cost per way (RM): " << pathDistanceFromWasteStation * 2.5 << endl;
                            outFileNOR << "Cost per way (RM): " << pathDistanceFromWasteStation * 2.5 << endl;

                            totalFuelConsumption += (pathDistanceFromWasteStation * 2);
                            cout << "Fuel consumption per way (liters): " << 2 * pathDistanceFromWasteStation << endl;
                            outFileNOR << "Fuel consumption per way (liters): " << 2 * pathDistanceFromWasteStation << endl;

                            cout << endl;
                            outFileNOR << endl;
                        } else { //If not then display the output below
                            cout << "Note: Location not visited due to distance exceeding 30km\n";
                            outFileNOR << "Note: Location not visited due to distance exceeding 30km\n";
                        }
                        break;
                    }
                }

                wasteInKG = (totalWasteCollected * 500) / 100; //Convert the waste collected from percentage to KG

                cout << endl;
                outFileNOR << endl;

                totalCost = totalCost * 2;
                totalFuelConsumption = totalFuelConsumption * 2;

                if (totalTime <= 12) {
                    locationsWithin12Hours.push_back(currentLocations[index]);
                } else {
//                    cout << "\n**Total time exceeds 12 hours, refer to the locations below that can be visited within 12 hours**" << endl;
//                    outFileNOR << "\n**Total time exceeds 12 hours, refer to the locations below that can be visited within 12 hours**" << endl;
                    break;
                }
            }
        }

        totalTime = totalTime * 2;

        if (totalTime > 12) { //There is a time limit of 12 hours, if exceeded then display the output below
            cout << "Time constraint: 12 hours";
            outFileNOR << "Time constraint: 12 hours";
            cout << "\nLocations available for visiting:" << endl;
            outFileNOR << "\nLocations available for visiting:" << endl;
            for (int i = 0; i < locationsWithin12Hours.size(); i++) {
                cout << i << ". " << locationsWithin12Hours[i] << endl;
                outFileNOR << i << ". " << locationsWithin12Hours[i] << endl;
            }
        }
        
        if (totalTime > 12) {
            driverWage = 20 * 12;  // Driver wage for visited locations
            cout << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
            outFileNOR << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
        } else {
            driverWage = 20 * totalTime;  // Driver wage for visited locations
            cout << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
            outFileNOR << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
        }

        //Display the total distance, cost, time, fuel consumption and waste collected - all related information
        cout << "\nTotal Distance for Visited Locations (km): " << totalDistance << endl;
        outFileNOR << "\nTotal Distance for Visited Locations (km): " << totalDistance << endl;
        cout << "Total Cost (RM): " << totalCost << endl;
        outFileNOR << "Total Cost (RM): " << totalCost << endl;
        cout << "Total Duration (hrs): " << totalTime << endl;
        outFileNOR << "Total Duration (hrs): " << totalTime << endl;
        cout << "Total Fuel Consumption (liters): " << totalFuelConsumption << endl;
        outFileNOR << "Total Fuel Consumption (liters): " << totalFuelConsumption << endl;
        cout << "Total percentage of waste collected from available locations (%): " << totalWasteCollected << endl;
        outFileNOR << "Total percentage of waste collected from available locations (%): " << totalWasteCollected << endl;
        cout << "Total Waste Collected (kg): " << wasteInKG << endl;
        outFileNOR << "Total Waste Collected (kg): " << wasteInKG << endl;
    }

    vector<string> calculateShortestPath(const vector<string>& currentLocations) { //Method that pre-defines the shortest path using the graph and distance matrix
        vector<string> shortestPathLocations; //Create the shortestPathLocations vector
        shortestPathLocations.push_back("Waste Station"); //Push the waste station into the vector
        shortestPathLocations.push_back("Location 1"); //Push the locations 1 into the vector
        shortestPathLocations.push_back("Location 3"); //Push the locations 3 into the vector
        shortestPathLocations.push_back("Location 2"); //Push the locations 2 into the vector
        shortestPathLocations.push_back("Location 4"); //Push the locations 4 into the vector
        shortestPathLocations.push_back("Location 3"); //Push the locations 3 into the vector
        shortestPathLocations.push_back("Location 6"); //Push the locations 6 into the vector
        shortestPathLocations.push_back("Location 5"); //Push the locations 5 into the vector
        shortestPathLocations.push_back("Location 6"); //Push the locations 6 into the vector
        shortestPathLocations.push_back("Location 7"); //Push the locations 7 into the vector

        return shortestPathLocations; //Return the shortestPathLocations vector
    }
};

#endif