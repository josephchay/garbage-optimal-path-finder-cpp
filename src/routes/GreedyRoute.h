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
#include "src/maps/GarbageLocations.h" //Include the GarbageLocations header file

#ifndef GREEDY_ROUTE_H //Header file guard
#define GREEDY_ROUTE_H //Header file guard

#define INF INT_MAX //Set INF to the maximum integer value
#define VERTICES 8 //Set VERTICES to 8 which is the number of vertices, because there are 8 locations then define the number of vertices as well for the algorithm to work

using namespace std; //Use standard namespace

class GreedyRoute { //Class for the Greedy Route algorithm

public: //Public specifier
    void createGraph(const GarbageLocations& garbageLocations, int garbageLocationGraph[][VERTICES], const vector<string>& currentLocations) { //Create the graph for the Greedy Route algorithm
        for (int index = 0; index < VERTICES; index++) { //Iterate over the number of vertices/ locations
            for (int index2 = 0; index2 < VERTICES; index2++) { //Then iterate over the number of vertices/ locations again, this is to set the distance between the locations
                garbageLocationGraph[index][index2] = garbageLocations.distanceMatrix.at(currentLocations[index]).at(currentLocations[index2]); //Distance between the locations is initialised here
            }
        }
    }

    void createPath(int parentLocation[], int index, vector<string> currentLocations, ofstream& outFileGR, stringstream& buffer) { //Create the path for the algorithm, initialise the path using the locations
        if (parentLocation[index] == -1) { //If the parent location is equal to -1, then it is the source/ waste station
            outFileGR << "Waste Station";
            buffer << "Waste Station";
        }

        if (parentLocation[index] != 0) { //If the parent location is not equal to 0, then it is not the source/ waste station, opposite to the first condition
            createPath(parentLocation, parentLocation[index], currentLocations, outFileGR, buffer);
        }

        if (currentLocations[parentLocation[index]] == "Waste Station") { //So if the parent lcoation is source/ waste station, then start by printing the path from "Waste Station -> "
            outFileGR << "Waste Station -> " << currentLocations[index];
            buffer << "Waste Station -> " << currentLocations[index];
        } else if (parentLocation[index] != 0) { //If parent location is NOT the source/ waste station, then print the path from " -> ", this way it prints the path consistently
            outFileGR << " -> " << currentLocations[index];
            buffer << " -> " << currentLocations[index];
        } else { //
            outFileGR << currentLocations[index]; //Print the current location
            buffer << currentLocations[index]; //Print the current location
        }
    }

    metrics::Metrics daSolution(float distance[], int vertex, int parentLocation[], vector<string> currentLocations, const GarbageLocations& garbageLocations, ofstream& outFileGR, bool searchForBest) { //Dijkstra Algorithm solution method
        stringstream buffer;

        double totalTime = 0;
        double totalFuelConsumption = 0;
        double totalCost = 0;
        float driverWage, totalDistance = 0; //Initialise the float variables for the total cost, total time, total fuel consumption, driver wage and total distance to 0
        int totalWasteCollected = 0; //Initialise the integer total waste collected to 0
        int wasteInKG = 0; //Initialise the integer waste in KG to 0

        outFileGR << "Travel Paths:" << endl;
        buffer << "Travel Paths:" << endl;

        vector<string> locationsWithin8Hours;  //Create the vector to store locations that can be visited under 8 hours

        for (int index = 1; index < VERTICES; index++) { //Iterate over the number of vertices/ locations
            if (distance[index] < INF && garbageLocations.wasteLevels.at(currentLocations[index]) >= 30) { //If the distance is less than the defined INf and the waste level is greater than or equal to 30 then perform the following operations
                buffer << "---------- " << currentLocations[index] << " ----------\n"; //Output the current location
                outFileGR << "---------- " << currentLocations[index] << " ----------\n"; //Output the current location

                totalWasteCollected += garbageLocations.wasteLevels.at(currentLocations[index]);
                totalDistance += distance[index];  

                outFileGR << "Distance from waste station (km): " << distance[index];
                buffer << "Distance from waste station (km): " << distance[index];

                outFileGR << "\nPath: ";
                buffer << "\nPath: ";
                
                createPath(parentLocation, index, currentLocations, outFileGR, buffer);

                auto weather = garbageLocations.locationWeathers.at(currentLocations[index]);

                buffer << "\nWeather: " << weather;
                outFileGR << "\nWeather: " << weather;

                // if sunny .1 hr per km, cloudy .2 hr per km, rainy .3 hr per km
                if (weather == "Sunny") {
                    totalTime += distance[index] * 0.1;
                    buffer << "\nDuration per way (hours): " << distance[index] * 0.1 << endl;
                    outFileGR << "\nDuration per way (hours): " << distance[index] * 0.1 << endl;
                } else if (weather == "Cloudy") {
                    totalTime += distance[index] * 0.2;
                    buffer << "\nDuration per way (hours): " << distance[index] * 0.2 << endl;
                    outFileGR << "\nDuration per way (hours): " << distance[index] * 0.2 << endl;
                } else if (weather == "Rainy") {
                    totalTime += distance[index] * 0.3;
                    buffer << "\nDuration per way (hours): " << distance[index] * 0.3 << endl;
                    outFileGR << "\nDuration per way (hours): " << distance[index] * 0.3 << endl;
                } else if (weather == "Flooding") {
                    totalTime += distance[index] * 0.4;
                    buffer << "\nDuration per way (hours): " << distance[index] * 0.4 << endl;
                    outFileGR << "\nDuration per way (hours): " << distance[index] * 0.4 << endl;
                }

                totalCost += distance[index] * 2.5;
                buffer << "Cost per way (RM): " << distance[index] * 2.5 << endl;
                outFileGR << "Cost per way (RM): " << distance[index] * 2.5 << endl;

                totalFuelConsumption += 2 * distance[index];
                buffer << "Fuel consumption per way (liters): " << distance[index] * 2 << endl;
                outFileGR << "Fuel consumption per way (liters): " << distance[index] * 2 << endl;

                buffer << endl;
                outFileGR << endl;

                if (totalTime <= 8) { //Check if the total time is less than or equal to 8 hours
                    locationsWithin8Hours.push_back(currentLocations[index]);
                } else {
//                    outFileGR << "\n**Total time exceeds 8 hours, refer to the locations below that can be visited within 8 hours**" << endl;
//                    buffer << "\n**Total time exceeds 8 hours, refer to the locations below that can be visited within 8 hours**" << endl;
                    break;
                }

                wasteInKG = (totalWasteCollected * 500)/100;
            }
        }

        totalTime = totalTime * 2;

        if (totalTime > 8) { //If the total time is greater than 8 hours, then perform the following operations
            buffer << "Time constraint: 8 hours";
            outFileGR << "Time constraint: 8 hours";
            buffer << "\nLocations available for visiting:" << endl;

            for (int i = 0; i < locationsWithin8Hours.size(); i++) { //Loop within the locations that can be visited within 8 hours
                outFileGR << locationsWithin8Hours[i] << endl;
                buffer << locationsWithin8Hours[i] << endl;
            }
        }

        totalCost = totalCost * 2;
        totalFuelConsumption = 2 * totalFuelConsumption;

        //Display the total distance, cost, time, fuel consumption and waste collected - all related information
        buffer << "\nTotal Distance for Visited Locations (km): " << totalDistance << endl;
        outFileGR << "\nTotal Distance for Visited Locations (km): " << totalDistance << endl;
        buffer << "Total Cost (RM): " << totalCost << endl;
        outFileGR << "Total Cost (RM): " << totalCost << endl;
        buffer << "Total Duration (hrs): " << totalTime << endl;
        outFileGR << "Total Duration (hrs): " << totalTime << endl;
        buffer << "Total Fuel Consumption (liters): " << totalFuelConsumption << endl;
        outFileGR << "Total Fuel Consumption (liters): " << totalFuelConsumption << endl;
        buffer << "Total percentage of waste collected from available locations (%): " << totalWasteCollected << endl;
        outFileGR << "Total percentage of waste collected from available locations (%): " << totalWasteCollected << endl;
        buffer << "Total Waste Collected (kg): " << wasteInKG << endl;
        outFileGR << "Total Waste Collected (kg): " << wasteInKG << endl;

        if (totalTime > 8) { //If the total time is exceeds 8 hours
            driverWage = 20 * 8;
            buffer << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
            outFileGR << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
        } else { //If the total time is less than or equal to 8 hours
            driverWage = 20 * totalTime;
            buffer << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
            outFileGR << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
        }

        metrics::Metrics results;
        results.name = "Greedy Route";
        results.totalDistance = totalDistance;
        results.driverWage = driverWage;
        results.totalTime = totalTime;
        results.totalFuelConsumption = totalFuelConsumption;
        results.totalCost = totalCost;
        results.totalWasteCollected = totalWasteCollected;
        results.wasteInKG = wasteInKG;
        results.info = buffer.str();

        return results;
    }

    int minimumDistance(float distance[], bool shortestPathTree[]) { //Method to find the minimum distance, this method is used to find the minimum distance from the source to the destination so that the shortest path can be found through the Dijkstra Algorithm
        float minimumValue = INF; //First assign the minimumValue to the defined INF
        int minimumIndex; //Initialise the minimumIndex to 0

        for (int vertex = 0; vertex < VERTICES; vertex++) { //Iterate over the number of vertices which is the number of locations present
            if (distance[vertex] <= minimumValue && shortestPathTree[vertex] == false){ //If the distance at the location is less than INF and the shortest path tree at the location is false then perform the following operations
                minimumValue = distance[vertex];
                minimumIndex = vertex;
            }
        }

        return minimumIndex;
    }

    metrics::Metrics dijkstraAlgorithm(int garbageLocationGraph[VERTICES][VERTICES], int source, const vector<string>& currentLocations, const GarbageLocations& garbageLocations, ofstream& outFileGR, bool searchForBest) { //This is the Dijkstra Algorithm method which contains the algorithm logic
        float distance[VERTICES]; //First initialise the distance array with the number of locations
        bool shortestPathTree[VERTICES]; //Then initialise the shortestPathTree array with the number of locations
        int parentLocation[VERTICES]; //Then initialise the parentLocation array with the number of locations this is to store the parent location of the current location

        for (int index = 0; index < VERTICES; index++) { //Iterate over the number of locations
            parentLocation[source] = -1;
            distance[index] = INF;
            shortestPathTree[index] = false;
        }

        distance[source] = 0; //Assign the source distance as 0

        for (int count = 0; count < VERTICES - 1; count++) { //Iterate over the number of locations - 1
            int closestVertex = minimumDistance(distance, shortestPathTree);
            shortestPathTree[closestVertex] = true;

            for (int vertex = 0; vertex < VERTICES; vertex++) { //Iterate over the number of locations
                int temporaryVertex = distance[closestVertex] + garbageLocationGraph[closestVertex][vertex];
                if (garbageLocationGraph[closestVertex][vertex] && temporaryVertex < distance[vertex] && !shortestPathTree[vertex]) {
                    parentLocation[vertex] = closestVertex;
                    distance[vertex] = distance[closestVertex] + garbageLocationGraph[closestVertex][vertex];
                }
            }
        }

        auto results = daSolution(distance, VERTICES, parentLocation, currentLocations, garbageLocations, outFileGR, searchForBest); //Call the daSolution method to find the solution

        if (!searchForBest) {
            cout << results.info;
        }

        return results;
    }
};

#endif