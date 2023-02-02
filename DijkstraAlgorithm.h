//
// Created by Daniel Agu on 12/2/2020.
//

#ifndef DIJKSTRA_ALGORITHM_BASE_DIJKSTRAALGORITHM_H
#define DIJKSTRA_ALGORITHM_BASE_DIJKSTRAALGORITHM_H

#include "Vertex.h"
#include "Graph.h"
#include <limits.h>
#include <algorithm>
#include <unordered_map>

class DijkstraAlgorithm {
public:
    DijkstraAlgorithm(Graph *newGraph);

    void runAlgorithm(Vertex *newSource);

    int getShortestDistance(Vertex *newSource);
    std::string getPathTo(Vertex *newSource);

private:
    Graph *graph;
    Vertex *source;

    std::unordered_map<Vertex *, int> distance;
    std::unordered_map<Vertex *, std::string> path;
    std::unordered_map<Vertex *, Vertex *> predecessor;
};


#endif //DIJKSTRA_ALGORITHM_BASE_DIJKSTRAALGORITHM_H
