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

#ifndef TSPROUTE_H //Header file guard
#define TSPROUTE_H //Header file guard

#define INF INT_MAX //Set INF to the maximum integer value
#define VERTICES 8 //Set VERTICES to 8 which is the number of vertices, because there are 8 locations then define the number of vertices as well for the algorithm to work

using namespace std; //Use standard namespace

class TSPRoute { //Class for the TSPRoute

public: //Public specifier
    void createGraph(int garbageLocationGraph[][VERTICES], const vector<string>& currentLocations, const GarbageLocations& garbageLocations) { //Create the graph for the TSP algorithm
        for (int index = 0; index < VERTICES; index++) { //Iterate over the number of vertices which is the number of locations
            for (int index2 = 0; index2 < VERTICES; index2++) {
                garbageLocationGraph[index][index2] = garbageLocations.distanceMatrix.at(currentLocations[index]).at(currentLocations[index2]);
            }
        }
    }

    int minimumDistance(float distance[], bool shortestPathTree[]) {//Find the minimum distance
        float minimumValue = INF; //Set the minimum value to the INF which indicates the maximum integer value
        int minimumIndex; //Declare the minimum index

        for (int v = 0; v < VERTICES; v++) //Iterate over the number of vertices
            if (shortestPathTree[v] == false && distance[v] <= minimumValue){ //If the shortest path tree is false and the distance is less than or equal to the minimum value
                minimumValue = distance[v]; //Then assign the minimum value to the distance
                minimumIndex = v; //And the minimum index to the vertex
            }
        return minimumIndex;
    }

    void tspPath(int parentLocation[], int index, const vector<string>& currentLocations, ofstream& outFileTSP) { //Find the path for the TSP algorithm
        if (parentLocation[index] == -1) { //If the parent location is -1 it means that the location is the waste station
            outFileTSP << "Waste Station";
            cout << "Waste Station";
            return;
        }

        tspPath(parentLocation, parentLocation[index], currentLocations, outFileTSP); //Recursively call the function to find the path, this is so that the path is printed in the correct order

        if (currentLocations[parentLocation[index]] != currentLocations[index]) { //If the parent location is not equal to the current location
            outFileTSP << " -> " << currentLocations[index];
            cout << " -> " << currentLocations[index];
        }
    }

    void tspSolution(float distance[], int vertex, int parent[], const vector<string>& currentLocations, const GarbageLocations& garbageLocations, ofstream& outFileTSP) { //Find the solution for the TSP algorithm, this is the logic for the algorithm
        outFileTSP << "Travel Paths:" << endl;
        cout << "Travel Paths:" << endl;

        float totalDistance = 0;
        double totalTime = 0;
        double totalFuelConsumption = 0;
        double totalCost = 0;
        float driverWage = 0;
        int totalWasteCollected = 0;
        int wasteInKG = 0;
        vector<string> locationsWithin8Hours; 
        
        for (int index = 1; index < VERTICES; index++) { //Iterate over the number of vertices which is the number of locations
            if (garbageLocations.wasteLevels.at(currentLocations[index]) >= 60) { //If the waste level is greater than or equal to 60
                cout << "---------- " << currentLocations[index] << " ----------\n"; //Output the current location
                outFileTSP << "---------- " << currentLocations[index] << " ----------\n"; //Output the current location

                if (distance[index] <= 12) { //If the distance is less than or equal to 12
                    totalDistance += distance[index]; 
                    totalWasteCollected += garbageLocations.wasteLevels.at(currentLocations[index]);
                    outFileTSP << "Distance from waste station (km): " << distance[index];
                    cout << "Distance from waste station (km): " << distance[index];
                    outFileTSP << "\nPath: ";
                    cout << "\nPath: ";

                    tspPath(parent, index, currentLocations, outFileTSP); //Call the tspPath method to find the path

                    auto weather = garbageLocations.locationWeathers.at(currentLocations[index]); //Get the weather for the location

                    cout << "\nWeather: " << weather;
                    outFileTSP << "\nWeather: " << weather;

                    // if sunny .1 hr per km, cloudy .2 hr per km, rainy .3 hr per km
                    if (weather == "Sunny") {
                        totalTime += distance[index] * 0.1;
                        cout << "\nDuration per way (hours): " << distance[index] * 0.1 << endl;
                        outFileTSP << "\nDuration per way (hours): " << distance[index] * 0.1 << endl;
                    } else if (weather == "Cloudy") {
                        totalTime += distance[index] * 0.2;
                        cout << "\nDuration per way (hours): " << distance[index] * 0.2 << endl;
                        outFileTSP << "\nDuration per way (hours): " << distance[index] * 0.2 << endl;
                    } else if (weather == "Rainy") {
                        totalTime += distance[index] * 0.3;
                        cout << "\nDuration per way (hours): " << distance[index] * 0.3 << endl;
                        outFileTSP << "\nDuration per way (hours): " << distance[index] * 0.3 << endl;
                    } else if (weather == "Flooding") {
                        totalTime += distance[index] * 0.4;
                        cout << "\nDuration per way (hours): " << distance[index] * 0.4 << endl;
                        outFileTSP << "\nDuration per way (hours): " << distance[index] * 0.4 << endl;
                    }

                    totalCost += distance[index] * 2.5;
                    cout << "Cost per way (RM): " << distance[index] * 2.5 << endl;
                    outFileTSP << "Cost per way (RM): " << distance[index] * 2.5 << endl;

                    totalFuelConsumption += distance[index] * 2;
                    cout << "Fuel consumption per way (liters): " << distance[index] * 2 << endl;
                    outFileTSP << "Fuel consumption per way (liters): " << distance[index] * 2 << endl;

                    cout << endl;
                    outFileTSP << endl;

                    if (totalTime <= 8) { //If the total time is less than or equal to 8 hours
                        locationsWithin8Hours.push_back(currentLocations[index]); 
                    } else { //If the total time exceeds 8 hours
//                        outFileTSP << "**Total time exceeds 8 hours, refer to the locations below that can be visited within 8 hours**" << endl;
//                        cout << "**Total time exceeds 8 hours, refer to the locations below that can be visited within 8 hours**" << endl;
                        break;
                    }
                } else { //If the distance exceeds 12 km
                    cout << "Note: Location not visited due to distance exceeding 12km";
                    outFileTSP << "Note: Location not visited due to distance exceeding 12km";
                }
            }
        }

        totalTime = totalTime * 2;
        totalCost = totalCost * 2;
        totalFuelConsumption = totalFuelConsumption * 2;
        wasteInKG = (totalWasteCollected * 500)/100;

        if (totalTime > 8) { //If the total time exceeds 8 hours
            cout << "Time constraint: 12 hours";
            outFileTSP << "Time constraint: 8 hours";
            cout << "\nLocations available for visiting:" << endl;
            outFileTSP << "\nLocations available for visiting:" << endl;
            for (int i = 0; i < locationsWithin8Hours.size(); i++) {
                outFileTSP << locationsWithin8Hours[i] << endl;
                cout << locationsWithin8Hours[i] << endl;
            }
        }

        if(totalTime > 8) { //If the total time exceeds 8 hours
            driverWage = 20 * 8; 
            cout << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
            outFileTSP << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
        } else { //If the total time less than or equal to 8 hours
            driverWage = 20 * totalTime;  
            cout << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
            outFileTSP << "\nDriver Wage for all visiting locations (RM): " << driverWage << endl;
        }

        //Display the total distance, cost, time, fuel consumption and waste collected - all related information
        cout << "\nTotal Distance for Visited Locations (km): " << totalDistance << endl;
        outFileTSP << "\nTotal Distance for Visited Locations (km): " << totalDistance << endl;
        cout << "Total Cost (RM): " << totalCost << endl;
        outFileTSP << "Total Cost (RM): " << totalCost << endl;
        cout << "Total Duration (hrs): " << totalTime << endl;
        outFileTSP << "Total Duration (hrs): " << totalTime << endl;
        cout << "Total Fuel Consumption (liters): " << totalFuelConsumption << endl;
        outFileTSP << "Total Fuel Consumption (liters): " << totalFuelConsumption << endl;
        cout << "Total percentage of waste collected from available locations (%): " << totalWasteCollected << endl;
        outFileTSP << "Total percentage of waste collected from available locations (%): " << totalWasteCollected << endl;
        cout << "Total Waste Collected (kg): " << wasteInKG << endl;
        outFileTSP << "Total Waste Collected (kg): " << wasteInKG << endl;
    }

    void travellingSalesmanProblem(int garbageLocationGraph[][VERTICES], const vector<string>& currentLocations, const GarbageLocations& garbageLocations, ofstream& outFileTSP) { //Implement the travelling salesman problem algorithm
        float dist[VERTICES]; //Create an array to store the distance, the size is the number of locations
        bool shortestPathTree[VERTICES]; //Create an array to store the shortest path tree, the size is the number of locations
        int parent[VERTICES]; //Create an array to store the parent, the size is the number of locations

        for (int index = 0; index < VERTICES; index++) { //Iterate over all locations
            parent[0] = -1; //Set the source vertex to -1
            dist[index] = INF; //Then set the distance to INF
            shortestPathTree[index] = false; //Set the shortest path tree to false
        }

        dist[0] = 0; //Set source vertex distance to 0

        for (int index2 = 0; index2 < VERTICES - 1; index2++) { //Iterate over the number of vertices - 1 which is the number of locations - 1
            int closestVertex = minimumDistance(dist, shortestPathTree);
            shortestPathTree[closestVertex] = true;

            for (int index3 = 0; index3 < VERTICES; index3++) //Iterate over the number of vertices which is the number of locations
                if (garbageLocationGraph[closestVertex][index3] && dist[closestVertex] + garbageLocationGraph[closestVertex][index3] < dist[index3] && !shortestPathTree[index3]) {
                    parent[index3] = closestVertex;
                    dist[index3] = dist[closestVertex] + garbageLocationGraph[closestVertex][index3];
                }
        }

        tspSolution(dist, VERTICES, parent, currentLocations, garbageLocations, outFileTSP); //Call the tspSolution function
    }
};

#endif