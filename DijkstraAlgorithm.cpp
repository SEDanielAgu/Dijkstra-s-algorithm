//
// Created by Daniel Agu on 12/2/2020.
//

#include "DijkstraAlgorithm.h"
#include <limits.h>
#include <algorithm>
#include <unordered_map>

DijkstraAlgorithm::DijkstraAlgorithm(Graph *newGraph) {
    graph = newGraph;
}

void DijkstraAlgorithm::runAlgorithm(Vertex *newSource) {
    std::vector<Vertex *> unvisitedVertices = graph->getVertices(); //creates a list of unvisited vertices
    source = newSource;

    for (Vertex *vertex : unvisitedVertices) { //goes through list of unvisited vertices and sets all the distances to int_max in place of infinity
        distance[vertex] = INT_MAX;
    }
    distance[source] = 0;

    while (!unvisitedVertices.empty()) {
        auto smallestIterator = std::min_element(unvisitedVertices.begin(), unvisitedVertices.end(), // creates and iterator using a lambda function to point to the smallest vertex that has not been visited
                                           [this](auto vertexOne, auto vertexTwo) {
                                               return distance.at(vertexTwo) < distance.at(vertexTwo);
                                           });
        Vertex *smallestVertex = *smallestIterator;
        unvisitedVertices.erase(smallestIterator); //removes the smallest vertex because it has now been visited

        if (distance[smallestVertex] != INT_MAX) { //makes sure the smallest vertex is not unreachable
            std::vector<Vertex *> adjacents;
            smallestVertex->getAdjacentVertices(adjacents);//creates a vector of adjacent vertices

            for (Vertex *adjVertex: adjacents) {
                int edge = smallestVertex->getEdgeWeight(adjVertex);
                if (distance[smallestVertex] + edge < distance[adjVertex]) { //if there is a shorter path to the next vertex update the distance to the shorter path
                    distance[adjVertex] = distance[smallestVertex] + edge;
                    predecessor[adjVertex] = smallestVertex;
                }
            }
        }
    }

    std::vector<Vertex *> vertices = graph->getVertices();

    for (Vertex *vertex: vertices) {
        if (distance[vertex] != INT_MAX) { //makes sure the vertex is reachable
            std::string stringPath = "";
            Vertex *currentVertex = vertex;
            while (currentVertex != nullptr) { //cycles through until the source is reached
                stringPath += currentVertex->getName() + "-";
                currentVertex = predecessor[currentVertex]; //cycles through the predecessors of the shortest path
            }
            stringPath.erase(stringPath.end() - 1); //gets rid of hanging "-"
            std::reverse(stringPath.begin(), stringPath.end()); //the path started at the last vertex and goes to the source so the path needs to be reversed
            path[vertex] = stringPath;
        }
    }
}

int DijkstraAlgorithm::getShortestDistance(Vertex *newSource) {
    return distance[newSource];
}

std::string DijkstraAlgorithm::getPathTo(Vertex *newSource) {
    return path[newSource];
}
